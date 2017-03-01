//
// Created by sauvau_m on 2/27/17.
//

#include <components/Clock.hpp>
#include <components/Input.hpp>
#include "components/c4013.hpp"

nts::c4013::~c4013() {
}

nts::c4013::c4013(const std::string &name) : AComponent(name, 14) {
    q1 = UNDEFINED;
    q2 = UNDEFINED;
    //First flipflop
    //q1
    pinComputeFunction[1] = std::bind(&c4013::output, this, 1);
    //q2
    pinComputeFunction[2] = std::bind(&c4013::output, this, 2);
    //clock 1
    pinComputeFunction[3] = std::bind(&c4013::input, this, 3);
    //Reset
    pinComputeFunction[4] = std::bind(&c4013::input, this, 4);
    //Data
    pinComputeFunction[5] = std::bind(&c4013::input, this, 5);
    //Set
    pinComputeFunction[6] = std::bind(&c4013::input, this, 6);
    //VSS
    pinComputeFunction[7] = std::bind(&c4013::vss, this, 7);

    //Second flipflop
    //q2
    pinComputeFunction[13] = std::bind(&c4013::output, this, 13);
    //q4
    pinComputeFunction[12] = std::bind(&c4013::output, this, 12);
    //clock 2
    pinComputeFunction[11] = std::bind(&c4013::input, this, 11);
    //Reset 2
    pinComputeFunction[10] = std::bind(&c4013::input, this, 10);
    //Data 2
    pinComputeFunction[9] = std::bind(&c4013::input, this, 9);
    //Set 2
    pinComputeFunction[8] = std::bind(&c4013::input, this, 8);
    //VDD
    pinComputeFunction[14] = std::bind(&c4013::vdd, this, 14);
}


void nts::c4013::whenDoesntCare(nts::IComponent *reset, nts::IComponent *set) {
    if (reset && set && reset->Compute() == TRUE && set->Compute() == FALSE) {
        q1 = FALSE;
        q2 = TRUE;
    } else if (reset && set && reset->Compute() == FALSE && set->Compute() == TRUE) {
        q1 = TRUE;
        q2 = FALSE;
    } else if (reset && set && reset->Compute() == TRUE && set->Compute() == TRUE) {
        q1 = TRUE;
        q2 = TRUE;
    }
}

nts::Tristate nts::c4013::flipFlop(size_t pin_num_this, IComponent *clock, IComponent *reset,
                                   IComponent *data, IComponent *set) {
    Clock *cl = dynamic_cast<Clock *>(clock);
    if (cl) {
        if (cl->isLowToHigh() == TRUE) {
            if (data && reset && set &&
                data->Compute() == FALSE && reset->Compute() == FALSE && set->Compute() == FALSE) {
                q1 = FALSE;
                q2 = TRUE;
            } else if (data && reset && set &&
                       data->Compute() == TRUE && reset->Compute() == FALSE && set->Compute() == FALSE) {
                q1 = TRUE;
                q2 = FALSE;
            }
        }
        if (cl->isLowToHigh() == FALSE) {
            if (reset && set && reset->Compute() == FALSE && set->Compute() == FALSE) {
                if (pin_num_this == 1 || pin_num_this == 13)
                    return q1;
                return q2;
            }
        }
        whenDoesntCare(reset, set);
    } else {
        whenDoesntCare(reset, set);
    }
    if (pin_num_this == 1 || pin_num_this == 13)
        return q1;
    return q2;
}

nts::Tristate nts::c4013::output(size_t pin_num_this) {
    if (pin_num_this == 1 || pin_num_this == 2)
        return flipFlop(pin_num_this, pin.at(3), pin.at(4), pin.at(5), pin.at(6));
    else if (pin_num_this == 13 || pin_num_this == 12)
        return flipFlop(pin_num_this, pin.at(11), pin.at(10), pin.at(9), pin.at(8));
    return (UNDEFINED);
}

void nts::c4013::Dump(void) const {
    AComponent::Dump("Chipset 4013 FlipFLop : ");
}
