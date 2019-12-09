/**
 * <algorithm> of the C++ STL.
 *
 * Copyright (C) 2019 Luiserebii
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LUISEREBII_ALGORITHM_H
#define LUISEREBII_ALGORITHM_H

#include <stdexcept>

namespace lsb {

template <class In> bool equal(In begin, In end, In begin2) {
  while (*begin != *end) {
    if (*begin != *begin2) {
      return false;
    }
    ++begin, ++begin2;
  }
  return true;
}

template <class In, class T> In find(In begin, In end, T val) {
  while (begin != end && *begin != val) {
    ++begin;
  }
  return begin;
}

template <class In, class Out> Out copy(In begin, In end, Out dest) {
  while (begin != end) {
    *dest++ = *begin++;
  }
  return dest;
}

template <class In> In search(In begin, In end, In begin2, In end2) {
  while (begin != end) {
    // If b == begin2, step into a loop to check each val, until b2 == e2
    if (*begin == *begin2) {
      In b2 = begin2;
      for (In b = begin; b2 != end2; ++b, ++b2) {
        if (*b != *b2) {
          break;
        }
        // If at any point, we hit b == end, we know we went too far, so just
        // return b
        if (b == end) {
          return b;
        }
      }
      // If we hit the end, we found it~
      if (b2 == end2) {
        return begin;
      }
    }
    ++begin;
  }
  return begin;
}
}

#endif
