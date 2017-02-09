//
// Created by sauvau_m on 2/9/17.
//

#ifndef CPP_NANOTEKSPICE_C4081_HPP
#define CPP_NANOTEKSPICE_C4081_HPP

#include "AComponent.hpp"

namespace nts {
    class c4081 : public AComponent {
        Tristate computeInput(size_t pin_num_this) const;
        Tristate computeOutput(size_t pin_num_this) const;

    public:
        Tristate Compute(size_t pin_num_this) override;
        void SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) override;

        void Dump(void) const override;
    };
}

#endif //CPP_NANOTEKSPICE_C4081_HPP
