//
// Created by sauvau_m on 2/6/17.
//

#ifndef CPP_NANOTEKSPICE_CLOCK_HPP
#define CPP_NANOTEKSPICE_CLOCK_HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class Clock : public ASpecialComponent {
        Tristate prevValue;
        Tristate lowToHigh;
    public:
        virtual ~Clock();
        Clock(std::string const &name);
        void Dump(void) const;
        void inverse();
        Tristate isLowToHigh() const;
        void setValue(nts::Tristate value);
        };
}

#endif //CPP_NANOTEKSPICE_CLOCK_HPP
