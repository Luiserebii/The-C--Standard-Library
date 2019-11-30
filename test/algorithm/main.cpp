#include "../lib/mint/mint.h"
#include "../../algorithm/algorithm.h"

#include <iostream>
//#include <algorithm>
#include <vector>

using lsb::equal;
using lsb::find;
using lsb::copy;

using std::vector;

void equal(Mint& m);

int main() {

    Mint m;
    m.title("<algorithm>");

    equal(m);

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
