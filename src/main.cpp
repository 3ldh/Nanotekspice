#include <iostream>
#include <Nanotekspice.hpp>
#include "ComponentFactory.hpp"


int main(int ac, char const * const * const argv) {
    nts::Nanotekspice *nano;

    if (ac < 2) {
        std::cout << "Usage : ./Nanotekspice [filename.nts] [[input=value] [...]]" << std::endl;
        return (1);
    }
    try {
        nano = new nts::Nanotekspice(argv[1], ac, argv);
        delete(nano);
    }
    catch (nts::NtsError const &err) {
        std::cerr << err.what() << std::endl;
    }
    return (0);
}