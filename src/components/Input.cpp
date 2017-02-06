//
// Created by sauvau_m on 2/5/17.
//

#include <Exception.hpp>
#include <iostream>
#include "components/Input.hpp"

nts::Input::~Input() {

}

nts::Input::Input(nts::Tristate value) : ASpecialComponent(value) {

}

void nts::Input::Dump(void) const {
    ASpecialComponent::Dump("Input");
}

void nts::Input::setValue(nts::Tristate value) {
    if (value == UNDEFINED)
        throw NtsError("Error : input value must be 0 or 1");
    Input::value = value;
}

