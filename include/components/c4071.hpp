//
// Created by sauvau_m on 2/14/17.
//

#ifndef CPP_NANOTEKSPICE_C4071_H
#define CPP_NANOTEKSPICE_C4071_H

#include "AComponent.hpp"

namespace nts {
    class c4071 : public AComponent{
        Tristate computeOutput(size_t pin_num_this) const override;
    public:
        c4071(std::string const &name);
        virtual ~c4071();
        void Dump(void) const;
    };
}


#endif //CPP_NANOTEKSPICE_C4071_H
