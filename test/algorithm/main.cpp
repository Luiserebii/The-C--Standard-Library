#include "../lib/mint/mint.h"
#include "../../algorithm/algorithm.h"

#include <iostream>
#include <algorithm>
#include <vector>

using lsb::equal;
using lsb::copy;

using std::vector;

void equal(Mint& m);
void find(Mint& m);

int main() {

    Mint m;
    m.title("<algorithm>");

    equal(m);
    find(m);

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
    int ptrpos = 4;
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
