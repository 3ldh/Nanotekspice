//
// Created by sauvau_m on 2/9/17.
//

#ifndef CPP_NANOTEKSPICE_ACCMPONENT_HPP
#define CPP_NANOTEKSPICE_ACCMPONENT_HPP

#include <functional>
#include <map>
#include "IComponent.hpp"

namespace nts {
    class AComponent : public IComponent {
        std::string name;
        int numberOfPin;
    protected:
        std::map<size_t, IComponent *> pin;
        std::map<size_t, std::function<Tristate(size_t)> > pinComputeFunction;
        std::map<size_t, std::pair<size_t, size_t> > mapPinOutputs;
        std::map<size_t, size_t> link;
        virtual Tristate input(size_t pin_num_this) const;
        virtual Tristate output(size_t pin_num_this) = 0;
        virtual Tristate vdd(size_t pin_num_this) const;
        virtual Tristate vss(size_t pin_num_this) const;
        void Dump(std::string const& str) const;
        Tristate tristate_and(Tristate a, Tristate b) const;
        Tristate tristate_nand(Tristate a, Tristate b) const;
        Tristate tristate_or(Tristate a, Tristate b) const;
        Tristate tristate_xor(Tristate a, Tristate b) const;
        Tristate tristate_nor(Tristate a, Tristate b) const;

    public:
        virtual ~AComponent();
        AComponent(std::string const &name, int numberOfPin);
        void SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target);
        Tristate Compute(size_t pin_num_this);
    };
}

#endif //CPP_NANOTEKSPICE_ACCMPONENT_HPP
