//
// Created by sauvau_m on 2/9/17.
//

#include <iostream>
#include <Exception.hpp>
#include "components/AComponent.hpp"

nts::AComponent::~AComponent() {
    for (int i = 0; i < numberOfPin; ++i) {
        if (pin[i])
            delete(pin[i]);
    }
    delete [] pin;
}

nts::AComponent::AComponent(int numberOfPin) : numberOfPin(numberOfPin) {
    pin = new IComponent*[numberOfPin];
    for (int i = 0; i < numberOfPin; ++i)
        pin[i] = NULL;
}

nts::Tristate nts::AComponent::Compute(size_t pin_num_this) {
    if (pinComputeFunction.find(pin_num_this) == pinComputeFunction.end())
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    return pinComputeFunction[pin_num_this](pin_num_this);
}

void nts::AComponent::SetLink(size_t pin_num_this, nts::IComponent &component, size_t pin_num_target) {
    if (pin_num_this > numberOfPin || pin_num_this == 0)
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    if (!pin[pin_num_this - 1]) {
        link[pin_num_this] = pin_num_target;
        pin[pin_num_this - 1] = &component;
        if (pin[pin_num_this - 1]) {
            pin[pin_num_this - 1]->SetLink(pin_num_target, *this, pin_num_this);
        }
    }
}

nts::Tristate nts::AComponent::computeVDD(size_t pin_num_this) const {
    (void) pin_num_this;
    std::cerr << "Computing VDD result to an UNDEFINED state" << std::endl;
    return UNDEFINED;
}

nts::Tristate nts::AComponent::computeVSS(size_t pin_num_this) const {
    (void) pin_num_this;
    std::cerr << "Computing VSS result to an UNDEFINED state" << std::endl;
    return UNDEFINED;
}

void nts::AComponent::Dump(std::string const &str) const {
    std::cout << str << std::endl;
    for (size_t i = 0; i < numberOfPin; ++i) {
        std::cout << "\tpin #" << i + 1 << " : " << ((pin[i]) ? std::to_string(pin[i]->Compute(link.at(i + 1))) : "NULL")
                  << std::endl;
    }
}