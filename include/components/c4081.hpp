//
// Created by sauvau_m on 2/9/17.
//

#ifndef CPP_NANOTEKSPICE_C4081_HPP
#define CPP_NANOTEKSPICE_C4081_HPP

#include "AComponent.hpp"

namespace nts {
    class c4081 : public AComponent {
        Tristate computeOutput(size_t pin_num_this) const;

    public:
        virtual ~c4081();
        c4081();
        void Dump(void) const override;
    };
}

#endif //CPP_NANOTEKSPICE_C4081_HPP
