//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include <Exception.hpp>
#include "components/Output.hpp"

nts::Output::~Output() {

}

nts::Output::Output() : ASpecialComponent(UNDEFINED) {}

nts::Tristate nts::Output::Compute(size_t pin_num_this) {
    if (pin_num_this != 1)
        throw nts::PinError("PinError : Pin " + std::to_string(pin_num_this) + " does not exist");
    if (!pin[0])
        throw nts::LinkError("Link error : output is not linked");
    value = pin[0]->Compute(link.second);
    return value;
}

void nts::Output::Dump(void) const {
    ASpecialComponent::Dump("Output");
}
