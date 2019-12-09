/**
 * Mint is a minimal header-only C++ test runner.
 *
 * @author Luiserebii <luis@serebii.io>
 * @license MIT
 *
 */

#ifndef GUARD_LUISEREBII_MINT_H
#define GUARD_LUISEREBII_MINT_H

#include <iostream>
#include <sstream>
#include <string>

class Mint {

  public:
    //Substitute for scoped enums - meant to be compatible pre-C++11
    struct Status {
        enum Enum { SUCCESS, FAIL };
    };

    //Constructors
    Mint();
    Mint(std::ostream& os);

    //Getters/setters
    std::ostream* getOut() { return out; }
    Status::Enum getStatus() const { return status; }
    std::string getTab() const { return tab; }

    void setOut(std::ostream* os) { out = os; }
    void setTab(std::string t) { tab = t; }

    //Test titling functions
    void title(const std::string& title, int borderNum = 2);
    void minititle(const std::string& minititle, int borderNum = 2);

    //Assert functions
    void assert(bool b, const std::string& title, const std::string& fail = "");
    template <class T>
    void equal(const T& val, const T& exp, const std::string& title);
    void throws(void f(), const std::string& title, const std::string& fail = "");

    //Other
    std::ostream& print(const std::string& s);
    int end();

  private:
    std::ostream* out;
    Status::Enum status;
    std::string tab;
    int testsPassing;
    int testsFailing;

    std::ostream& writeTestPass(const std::string& title);
    std::ostream& writeTestFail(const std::string& title, const std::string& fail = "");
};

Mint::Mint() : out(&std::cout), status(Status::SUCCESS), tab(std::string(2, ' ')), testsPassing(0), testsFailing(0) {}

Mint::Mint(std::ostream& os)
    : out(&os), status(Status::SUCCESS), tab(std::string(2, ' ')), testsPassing(0), testsFailing(0) {}

void Mint::title(const std::string& title, int borderNum) {
    //Create border
    int size = title.length() + (borderNum * 2);
    std::string border(size, '=');
    std::string pad(borderNum, ' ');
    //Print
    *out << border << std::endl << pad << title << std::endl << border << std::endl;
}

void Mint::minititle(const std::string& minititle, int borderNum) {
    //Create border
    int size = minititle.length() + (borderNum * 2);
    std::string border(size, '-');
    std::string pad(borderNum, ' ');
    //Print
    *out << std::endl << pad << minititle << std::endl << border << std::endl;
}

void Mint::assert(bool b, const std::string& title, const std::string& fail) {
    if(!b) {
        fail != "" ? writeTestFail(title, "FAIL: " + fail) : writeTestFail(title);
        status = Status::FAIL;
        ++testsFailing;
    } else {
        writeTestPass(title);
        ++testsPassing;
    }
}

template <class T>
void Mint::equal(const T& val, const T& exp, const std::string& title) {
    if(val != exp) {
        //Construct fail string
        std::stringstream ss;
        ss << "FAIL: Expected \"" << exp << "\", found: \"" << val << "\"";

        writeTestFail(title, ss.str());
        status = Status::FAIL;
        ++testsFailing;
    } else {
        writeTestPass(title);
        ++testsPassing;
    }
}

void Mint::throws(void f(), const std::string& title, const std::string& fail) {
    try {
        f();
    } catch(...) {
        writeTestPass(title);
        ++testsPassing;
        return;
    }
    fail != "" ? writeTestFail(title, "FAIL: " + fail + " (function did not throw)") : writeTestFail(title);
    ++testsFailing;
}

int Mint::end() {
    if(status == Status::SUCCESS) {
        *out << std::endl
             << "SUCCESS! All tests (" << testsPassing << ") passing with no tests failing. Returned with exit code \""
             << status << "\"." << std::endl;
    } else if(status == Status::FAIL) {
        *out << std::endl
             << "FAIL! " << testsFailing << " tests failing with " << testsPassing
             << " tests passing. Returned with exit code \"" << status << "\"." << std::endl;
    }
    //Return status as exit code
    return status;
}

std::ostream& Mint::print(const std::string& s) {
    return *out << s << std::endl;
}

//✓, ✔
std::ostream& Mint::writeTestPass(const std::string& title) {
    return *out << tab << "✓ " << title << std::endl;
}

//✗, ✘
std::ostream& Mint::writeTestFail(const std::string& title, const std::string& fail) {
    *out << tab << "✗ " << title << std::endl;
    return fail != "" ? *out << tab << tab << fail << std::endl : *out;
}

#endif
