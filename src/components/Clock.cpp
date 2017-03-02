//
// Created by sauvau_m on 2/6/17.
//

#include <string>
#include <Exception.hpp>
#include "components/Clock.hpp"

nts::Clock::~Clock() {

}

nts::Clock::Clock(std::string const &name) : ASpecialComponent(name) {
    value = FALSE;
    prevValue = value;
    lowToHigh = UNDEFINED;
}

void nts::Clock::Dump(void) const {
    ASpecialComponent::Dump("Clock");
}

void nts::Clock::inverse() {
    if (value != UNDEFINED) {
        prevValue = value;
        value = (value == FALSE) ? TRUE : FALSE;
        if (prevValue == UNDEFINED || value == UNDEFINED)
            lowToHigh = UNDEFINED;
        if (prevValue == FALSE && value == TRUE)
            lowToHigh = TRUE;
        else if (prevValue == TRUE && value == FALSE)
            lowToHigh = FALSE;
    }
}

nts::Tristate nts::Clock::isLowToHigh() const {
    return lowToHigh;
}

void nts::Clock::setValue(nts::Tristate value) {
    if (value == UNDEFINED)
        throw NtsError("Error : input value must be 0 or 1");
    Clock::value = value;
}