//
// Created by sauvau_m on 2/6/17.
//

#ifndef CPP_NANOTEKSPICE_FALSE_HPP
#define CPP_NANOTEKSPICE_FALSE_HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class False : public ASpecialComponent {
    public:
        virtual ~False();
        False(std::string const &name);
        void Dump(void) const;
    };
}

#endif //CPP_NANOTEKSPICE_FALSE_HPP
