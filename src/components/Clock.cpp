//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include "components/Clock.hpp"

nts::Clock::~Clock() {

}

nts::Clock::Clock(std::string const &name) : ASpecialComponent(name) {}

void nts::Clock::Dump(void) const {
    ASpecialComponent::Dump("Clock");
}

void nts::Clock::inverse() {
    if (value != UNDEFINED)
        value = (value == FALSE) ? TRUE : FALSE;
}
