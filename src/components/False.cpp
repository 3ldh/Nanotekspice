//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include "components/False.hpp"

nts::False::~False() {

}

nts::False::False(std::string const &name) : ASpecialComponent(name) {
    value = FALSE;
}

void nts::False::Dump(void) const {
    ASpecialComponent::Dump("False");
}

