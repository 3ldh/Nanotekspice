//
// Created by sauvau_m on 2/7/17.
//

#ifndef CPP_NANOTEKSPICE_C4008__HPP
#define CPP_NANOTEKSPICE_C4008__HPP

#include "AComponent.hpp"

namespace nts {
    class c4008 : public AComponent {

        Tristate outputOrCarryOut(size_t pin_num_this, bool computeCarry) const;
        Tristate carryOut(size_t pin_num_this) const;
        Tristate output(size_t pin_num_this);

    public:
        virtual ~c4008();
        c4008(std::string const &name);
        void Dump(void) const;
    };
}


#endif //CPP_NANOTEKSPICE_C4008_HPP
