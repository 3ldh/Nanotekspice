//
// Created by sauvau_m on 2/6/17.
//

#ifndef CPP_NANOTEKSPICE_CLOCK_HPP
#define CPP_NANOTEKSPICE_CLOCK_HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class Clock : public ASpecialComponent {
    public:
        virtual ~Clock();
        Clock(std::string const &name);
        void Dump(void) const;
        void inverse();
    };
}

#endif //CPP_NANOTEKSPICE_CLOCK_HPP
