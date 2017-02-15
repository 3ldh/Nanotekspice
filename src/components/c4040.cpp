//
// Created by sauvau_m on 2/14/17.
//

#include "components/c4040.hpp"

nts::c4040::~c4040() {

}

nts::c4040::c4040(const std::string &name) : AComponent(name, 16) {

}

nts::Tristate nts::c4040::computeOutput(size_t pin_num_this) const {
    return UNDEFINED;
}

void nts::c4040::Dump(void) const {
    AComponent::Dump("Chipset 4040 : ");
}
