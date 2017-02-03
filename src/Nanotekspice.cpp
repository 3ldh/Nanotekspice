//
// Created by sauvau_m on 2/2/17.
//

#include <iostream>
#include "Nanotekspice.hpp"

nts::Nanotekspice::~Nanotekspice() {

}

nts::Nanotekspice::Nanotekspice(std::string const &filename, int ac, char const *const *const av) {

    std::vector<std::pair<std::string const&, std::string const&> > inputValue;

    for (int i = 0; i < ac ; ++i) {
        std::string arg(av[i]);
        size_t found = arg.find_first_of("=");
        if (found != std::string::npos) {
            std::string value = arg.substr(found + 1, arg.size());
            if (value != "0" && value != "1")
                throw nts::SyntaxError("Input value must be equal to 0 or 1");
            inputValue.push_back(std::make_pair(arg.substr(0, found), value));
        }
    }

    try {
        circuit = new nts::Circuit(filename, inputValue);
    } catch (nts::NtsError const &err) {
        throw err;
    }
}

