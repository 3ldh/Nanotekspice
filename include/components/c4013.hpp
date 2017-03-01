//
// Created by sauvau_m on 2/27/17.
//

#ifndef CPP_NANOTEKSPICE_C4013_HPP
#define CPP_NANOTEKSPICE_C4013_HPP

#include "AComponent.hpp"

namespace nts {
    class c4013 : public AComponent {
        Tristate q1;
        Tristate q2;

        void whenDoesntCare(IComponent *reset, IComponent *set);
        Tristate flipFlop(size_t pin_num_this, IComponent *clock, IComponent *reset,
                          IComponent *data, IComponent *set);
        Tristate output(size_t pin_num_this);
    public:
        virtual ~c4013();
        c4013(const std::string &name);
        void Dump(void) const;
    };
}

#endif //CPP_NANOTEKSPICE_C4013_HPP
