//
// Created by sauvau_m on 2/6/17.
//

#ifndef CPP_NANOTEKSPICE_OUTPUT_HPP
#define CPP_NANOTEKSPICE_OUTPUT_HPP

#include "ASpecialComponent.hpp"

namespace nts {
    class Output : public ASpecialComponent {
    public:
        virtual ~Output();
        Output();
        Tristate Compute(size_t pin_num_this);

        void Dump(void) const override;
    };
}


#endif //CPP_NANOTEKSPICE_OUTPUT_HPP
