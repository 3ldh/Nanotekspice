//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include "components/True.hpp"

nts::True::~True() {

}

nts::True::True(std::string const &name) : ASpecialComponent(name) {
    value = TRUE;
}

void nts::True::Dump(void) const {
    ASpecialComponent::Dump("True");
}

