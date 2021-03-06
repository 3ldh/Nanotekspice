//
// Created by sauvau_m on 2/9/17.
//

#ifndef CPP_NANOTEKSPICE_C4081_HPP
#define CPP_NANOTEKSPICE_C4081_HPP

#include "AComponent.hpp"

namespace nts {
    class c4081 : public AComponent {
        Tristate output(size_t pin_num_this);

    public:
        virtual ~c4081();
        c4081(std::string const &name);
        void Dump(void) const;
    };
}

#endif //CPP_NANOTEKSPICE_C4081_HPP
