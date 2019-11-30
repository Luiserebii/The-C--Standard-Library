#include "lib/mint/mint.h"
#include "../vector/vector.h"

#include <iostream>
#include <string>

using namespace lsb;

void initialize(Mint& m);

int main() {

    Mint m;
    m.title("vector");

    initialize(m);
    addingElements(m);

    return m.end();

}

void initialize(Mint& m) {
    m.minititle("Initialize");
    vector<int> v;
    m.equal(v.size(), 0UL, "Empty vector has size 0");
}

void addingElements(Mint& m) {
    m.minititle("Adding elements");
    vector<int> v;
    int el1 = 10;
    m.push_back(el1);
    m.equal(v.size(), 1UL, "Vector has size 1 after one push_back()");

}
