//
// Created by sauvau_m on 2/14/17.
//

#ifndef CPP_NANOTEKSPICE_C4040_HPP
#define CPP_NANOTEKSPICE_C4040_HPP

#include "AComponent.hpp"

namespace nts {
    class c4040 : public AComponent {
    protected:
        Tristate output(size_t pin_num_this);
    public:
        c4040(const std::string &name);
        virtual ~c4040();
        void Dump(void) const;
    };
}

#endif //CPP_NANOTEKSPICE_C4040_HPP
