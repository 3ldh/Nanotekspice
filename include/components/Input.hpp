//
// Created by sauvau_m on 2/5/17.
//

#ifndef CPP_NANOTEKSPICE_INPUT_HPP
#define CPP_NANOTEKSPICE_INPUT_HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class Input : public nts::ASpecialComponent {
    public:
        virtual ~Input();
        Input(Tristate value);
        void Dump(void) const;
        void setValue(Tristate value);
    };
}

#endif //CPP_NANOTEKSPICE_INPUT_HPP
