//#include <gtest.h>
#include "tbitfield.h"
int main(int argc, char **argv) {
    TBitField bf(5);
    std::cout << "Input:\t";
    std::cin >> bf;
    std::cout <<"Output:\t" << bf;
}
