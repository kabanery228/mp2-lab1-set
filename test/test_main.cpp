//#include <gtest.h>
#include "tbitfield.h"
#include "tset.h"

int resheto_size = 100;

int main(int argc, char **argv) {
    //TBitField bf(5);
    //std::cout << "BitField\n";
    //std::cout << "Input:\t";
    //std::cin >> bf;
    //std::cout <<"Output:\t" << bf<<std::endl;
    std::cout << "Resheto\n";
    TSet resh(resheto_size);
    resh.InsElem(0);
    resh.InsElem(1);
    for (int i = 2; i < resheto_size;i++) {
        if (!resh.IsMember(i))
            for (int j = i * 2;j < resheto_size;j += i) resh.InsElem(j);
    }
    std::cout << ~resh;
}
