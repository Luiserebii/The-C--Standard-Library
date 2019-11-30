#include "../lib/mint/mint.h"
#include "../../algorithm/algorithm.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using lsb::equal;
using lsb::copy;

using std::vector;
using std::back_inserter;

void equal(Mint& m);
void find(Mint& m);
void copy(Mint& m);
void search(Mint& m);

int main() {

    Mint m;
    m.title("<algorithm>");

    equal(m);
    find(m);
    copy(m);
    search(m);

    return m.end();
}

void equal(Mint& m) {
    m.minititle("equal(b, e, b2)");
    vector<int> v1, v2, v3;
    v1.push_back(1), v2.push_back(1), v3.push_back(1);
    v1.push_back(2), v2.push_back(2), v3.push_back(2);
    v1.push_back(4), v2.push_back(4), v3.push_back(3);
    v1.push_back(9), v2.push_back(9), v3.push_back(9);
    v1.push_back(16), v2.push_back(16);

    //Use standard lib
    bool stdres = std::equal(v1.begin(), v1.end(), v2.begin());
    bool lsbres = equal(v1.begin(), v1.end(), v2.begin());

    m.equal(stdres, lsbres, "equal() returns true for equal vectors");
    
    //Test for inequality
    stdres = std::equal(v1.begin(), v1.end(), v3.begin());
    lsbres = equal(v1.begin(), v1.end(), v3.begin());

    m.equal(stdres, lsbres, "equal() returns false for unequal vectors");

}

void find(Mint& m) {
    m.minititle("find(b, e, t)");
    vector<int> v;
    v.push_back(1);
    v.push_back(2);    
    v.push_back(4);    
    v.push_back(9);
    v.push_back(16);    
    
    int testVal = 9;
    int ptrpos = 3;
    vector<int>::iterator stdres = std::find(v.begin(), v.end(), testVal);
    vector<int>::iterator lsbres = lsb::find(v.begin(), v.end(), testVal);

    m.assert(lsbres == v.begin() + ptrpos, "find() returns the correct iterator for a value that exists");
    m.assert(stdres == lsbres, "find() mirrors standard library functionality");
    
    //Test for val which does not exist
    testVal = 100;
    stdres = std::find(v.begin(), v.end(), testVal);
    lsbres = lsb::find(v.begin(), v.end(), testVal);

    m.assert(lsbres == v.end(), "find() returns the correct iterator (last past one) for a value that does not exist");
    m.assert(stdres == lsbres, "find() mirrors standard library functionality");

}

void copy(Mint& m) {
    m.minititle("copy(b, e, d)");
    vector<int> v1, v2, v3;
    v1.push_back(1);
    v1.push_back(2);    
    v1.push_back(4);    
    v1.push_back(9);
    v1.push_back(16);    

    std::copy(v1.begin(), v1.end(), back_inserter(v2));
    lsb::copy(v1.begin(), v1.end(), back_inserter(v3));

    m.assert(std::equal(v1.begin(), v1.end(), v3.begin()), "copy() copies all values successfully");
    m.assert(std::equal(v2.begin(), v2.end(), v3.begin()), "copy() mirrors standard library functionality");
}

void search(Mint& m) {
    m.minititle("search(b, e, b2, e2)");
    vector<int> v1, v2, v3;
    v1.push_back(1);
    v1.push_back(2), v2.push_back(2), v3.push_back(2);
    v1.push_back(4), v2.push_back(4), v3.push_back(9);
    v1.push_back(9);
    v1.push_back(16);

    int ptrpos = 1;
    vector<int>::iterator stdres = std::search(v1.begin(), v1.end(), v2.begin(), v2.end());
    std::cout << "fuck" << std::endl;
    vector<int>::iterator lsbres = lsb::search(v1.begin(), v1.end(), v2.begin(), v2.end());
    std::cout << "o shit" << std::endl;
    m.assert(lsbres == v1.begin() + ptrpos, "search() returns the correct iterator for a range that exists");
    m.assert(stdres == lsbres, "search() mirrors standard library functionality");

    stdres = std::search(v1.begin(), v1.end(), v3.begin(), v3.end());
    lsbres = lsb::search(v1.begin(), v1.end(), v3.begin(), v3.end());
    
    m.assert(lsbres == v1.end(), "search() returns the last iterator for a range that doesn't exist");
    m.assert(stdres == lsbres, "search() mirrors standard library functionality");
}
