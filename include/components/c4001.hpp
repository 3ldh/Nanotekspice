//
// Created by sauvau_m on 2/9/17.
//

#ifndef CPP_NANOTEKSPICE_C4001_HPP
#define CPP_NANOTEKSPICE_C4001_HPP

#include "AComponent.hpp"

namespace nts {
    class c4001 : public AComponent{
        Tristate computeOutput(size_t pin_num_this) const;

    public:
        virtual ~c4001();
        void Dump(void) const;
        c4001(std::string const &name);
    };
}


#endif //CPP_NANOTEKSPICE_C4001_HPP
