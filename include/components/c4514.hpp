//
// Created by sauvau_m on 3/2/17.
//

#ifndef CPP_NANOTEKSPICE_C4514_HPP
#define CPP_NANOTEKSPICE_C4514_HPP

#include "AComponent.hpp"

namespace nts {
    class c4514 : public AComponent {
        std::map<int, Tristate> value;
        std::map<int, int> linkSToPin;
    public:
        virtual ~c4514();
        c4514(const std::string &name);
        Tristate output(size_t pin_num_this);
        void Dump(void) const;
    };
}


#endif //CPP_NANOTEKSPICE_C4514_HPP
