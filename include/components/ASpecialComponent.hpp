//
// Created by sauvau_m on 2/5/17.
//

#ifndef CPP_NANOTEKSPICE_TRUE_HPP
#define CPP_NANOTEKSPICE_TRUE_HPP

#include <IComponent.hpp>
#include <string>

namespace nts {
    class ASpecialComponent : public IComponent {
    protected:
        std::string name;
        Tristate value;
        IComponent *pin[1];
        std::pair<size_t, size_t> link;

    public:
        virtual ~ASpecialComponent();
        ASpecialComponent(std::string const &name);
        virtual Tristate Compute(size_t pin_num_this);
        virtual void SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target);
        void Dump(std::string const &componentType) const;
        Tristate getValue() const;
        void setName(const std::string &name);
    };
}

#endif //CPP_NANOTEKSPICE_TRUE_HPP
