//
// Created by sauvau_m on 2/9/17.
//

#include <iostream>
#include <Exception.hpp>
#include <components/Output.hpp>
#include "components/AComponent.hpp"

nts::AComponent::~AComponent() {
}

nts::AComponent::AComponent(std::string const &name, int numberOfPin) : name(name), numberOfPin(numberOfPin) {
    for (int i = 1; i <= numberOfPin; ++i)
        pin[i] = NULL;
}

nts::Tristate nts::AComponent::Compute(size_t pin_num_this) {
    if (pinComputeFunction.find(pin_num_this) == pinComputeFunction.end())
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    return pinComputeFunction[pin_num_this](pin_num_this);
}

nts::Tristate nts::AComponent::input(size_t pin_num_this) const {
    if (!pin.at(pin_num_this))
        return UNDEFINED;
    if (dynamic_cast<Output *>(pin.at(pin_num_this)))
        throw PinError("PinError : Output used as Input");
    return pin.at(pin_num_this)->Compute(link.at(pin_num_this));
}

void nts::AComponent::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) {
    if (pin.find(pin_num_this) == pin.end())
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    if (!pin[pin_num_this]) {
        link[pin_num_this] = pin_num_target;
        pin[pin_num_this] = &component;
        if (pin[pin_num_this]) {
            pin[pin_num_this]->SetLink(pin_num_target, *this, pin_num_this);
        }
    }
}

nts::Tristate nts::AComponent::vdd(size_t pin_num_this) const {
    (void) pin_num_this;
    return UNDEFINED;
}

nts::Tristate nts::AComponent::vss(size_t pin_num_this) const {
    (void) pin_num_this;
    return UNDEFINED;
}

void nts::AComponent::Dump(std::string const &str) const {
    std::cout << str << "<" << name << ">" << std::endl;
    for (size_t i = 1; i <= numberOfPin; ++i) {
        std::cout << "\tpin #" << i << " : " << ((pin.at(i)) ? std::to_string(pin.at(i)->Compute(link.at(i))) : "NULL")
                  << std::endl;
    }
}

nts::Tristate nts::AComponent::tristate_and(Tristate a, Tristate b) const {
    if (a == FALSE || b == FALSE)
        return (FALSE);
    if (a == TRUE && b == TRUE)
        return (TRUE);
    return (UNDEFINED);
}

nts::Tristate nts::AComponent::tristate_nand(nts::Tristate a, nts::Tristate b) const {
    Tristate c = tristate_and(a, b);
    if (c == UNDEFINED)
        return (UNDEFINED);
    return (static_cast<Tristate>(!c));
}

nts::Tristate nts::AComponent::tristate_or(nts::Tristate a, nts::Tristate b) const {
    if (a == UNDEFINED || b == UNDEFINED)
        return (UNDEFINED);
    if (a == TRUE || b == TRUE)
        return (TRUE);
    return (FALSE);
}

nts::Tristate nts::AComponent::tristate_nor(nts::Tristate a, nts::Tristate b) const {
    Tristate c = tristate_or(a, b);
    if (c == UNDEFINED)
        return (UNDEFINED);
    return (static_cast<Tristate>(!c));
}

nts::Tristate nts::AComponent::tristate_xor(nts::Tristate a, nts::Tristate b) const {
    if (a == UNDEFINED && b == UNDEFINED)
        return (UNDEFINED);
    if (a == TRUE && b == TRUE)
        return (FALSE);
    return (tristate_or(a, b));
}
