#include <iostream>
#include <vector>

#include "helper_defs.hpp"

namespace debug {
void print_vector(vv vect) {
    for (ll v : vect) {
        std::cout << v << ' ';
    }
    std::cout << '\n';
}
}  // namespace debug
