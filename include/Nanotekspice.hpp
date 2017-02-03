//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_NANOTEKSPICE_HPP
#define CPP_NANOTEKSPICE_NANOTEKSPICE_HPP

#include "Exception.hpp"
#include "Circuit.hpp"

namespace nts {
    class Nanotekspice {
        nts::Circuit *circuit;

    public:
        virtual ~Nanotekspice();
        Nanotekspice(std::string const &filename, int ac, char const * const * const av);

    };
}

#endif //CPP_NANOTEKSPICE_NANOTEKSPICE_HPP
