//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include "components/False.hpp"

nts::False::~False() {

}

nts::False::False() : ASpecialComponent(FALSE) {}

void nts::False::Dump(void) const {
    ASpecialComponent::Dump("False");
}

