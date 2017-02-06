//
// Created by sauvau_m on 2/6/17.
//

#ifndef CPP_NANOTEKSPICE_TRUE__HPP
#define CPP_NANOTEKSPICE_TRUE__HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class True : public ASpecialComponent {
    public:
        virtual ~True();
        True();
        void Dump(void) const;
    };
}

#endif //CPP_NANOTEKSPICE_TRUE__HPP
