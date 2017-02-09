//
// Created by sauvau_m on 2/7/17.
//

#ifndef CPP_NANOTEKSPICE_C4008__HPP
#define CPP_NANOTEKSPICE_C4008__HPP

#include "AComponent.hpp"

namespace nts {
    class c4008 : public AComponent {

        Tristate computeOuputOrCarryOut(size_t pin_num_this, bool computeCarry) const;
        Tristate computeCarryOut(size_t pin_num_this) const;
        Tristate computeInput(size_t pin_num_this) const;
        Tristate computeOutput(size_t pin_num_this) const;

    public:
        virtual ~c4008();
        c4008();
        void Dump(void) const;
    };
}


#endif //CPP_NANOTEKSPICE_C4008_HPP
