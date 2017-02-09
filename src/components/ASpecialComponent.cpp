//
// Created by sauvau_m on 2/5/17.
//

#include <IComponent.hpp>
#include <Exception.hpp>
#include <iostream>
#include "components/ASpecialComponent.hpp"

nts::ASpecialComponent::~ASpecialComponent() {

}

nts::ASpecialComponent::ASpecialComponent(std::string const &name) : name(name) {
    value = UNDEFINED;
    pin[0] = NULL;
    link.first = 0;
    link.second = 0;
}

nts::Tristate nts::ASpecialComponent::Compute(size_t pin_num_this) {
    if (pin_num_this != 1)
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    return value;
}

void nts::ASpecialComponent::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) {
    if (pin_num_this != 1)
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    if (!pin[0]) {
        link.first = 0;
        link.second = pin_num_target;
        pin[0] = &component;
        if (pin[0])
            component.SetLink(pin_num_target, *this, pin_num_this);
    }
}

void nts::ASpecialComponent::Dump(std::string const &componentType) const {
    std::cout << "Component - "<< componentType << "<" + name + "> : " << value << std::endl;
    std::cout << "\tpin #1: " << ((pin[0]) ? "linked" : "NULL") << std::endl;
}

void nts::ASpecialComponent::setName(const std::string &name) {
    ASpecialComponent::name = name;
}
