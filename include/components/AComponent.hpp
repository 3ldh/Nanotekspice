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
        int numberOfPin;
    protected:
        IComponent **pin;
        std::map<size_t, std::function<Tristate(size_t)> > pinComputeFunction;
        std::map<size_t, std::pair<size_t, size_t> > mapPinOutputs;
        std::map<size_t, size_t> link;
        virtual Tristate computeInput(size_t pin_num_this) const;
        virtual Tristate computeOutput(size_t pin_num_this) const = 0;
        virtual Tristate computeVDD(size_t pin_num_this) const;
        virtual Tristate computeVSS(size_t pin_num_this) const;
        void Dump(std::string const& str) const;

    public:
        virtual ~AComponent();
        AComponent(int numberOfPin);
        void SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target);
        Tristate Compute(size_t pin_num_this);
    };
}

#endif //CPP_NANOTEKSPICE_ACCMPONENT_HPP
