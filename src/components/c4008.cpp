//
// Created by sauvau_m on 2/7/17.
//

#include <Exception.hpp>
#include <components/Output.hpp>
#include <iostream>
#include "components/c4008.hpp"

nts::c4008::~c4008() {
}

nts::c4008::c4008() : AComponent(16) {

    // A4 to A1
    pinComputeFunction[1] = std::bind(&c4008::computeInput, this, 1);
    pinComputeFunction[3] = std::bind(&c4008::computeInput, this, 3);
    pinComputeFunction[5] = std::bind(&c4008::computeInput, this, 5);
    pinComputeFunction[7] = std::bind(&c4008::computeInput, this, 7);
    // B4 to B1
    pinComputeFunction[15] = std::bind(&c4008::computeInput, this, 15);
    pinComputeFunction[6] = std::bind(&c4008::computeInput, this, 7);
    pinComputeFunction[4] = std::bind(&c4008::computeInput, this, 4);
    pinComputeFunction[2] = std::bind(&c4008::computeInput, this, 2);
    //CarryIn
    pinComputeFunction[9] = std::bind(&c4008::computeInput, this, 9);
    //CarryOut
    pinComputeFunction[14] = std::bind(&c4008::computeCarryOut, this, 14);
    //VDD
    pinComputeFunction[16] = std::bind(&c4008::computeVDD, this, 16);
    //VSS
    pinComputeFunction[8] = std::bind(&c4008::computeVSS, this, 8);
    //Sum s1 to s4
    pinComputeFunction[10] = std::bind(&c4008::computeOutput, this, 10);
    pinComputeFunction[11] = std::bind(&c4008::computeOutput, this, 11);
    pinComputeFunction[12] = std::bind(&c4008::computeOutput, this, 12);
    pinComputeFunction[13] = std::bind(&c4008::computeOutput, this, 13);
    //output link with inputs
    mapPinOutputs[10] = std::make_pair(6, 7);
    mapPinOutputs[11] = std::make_pair(4, 5);
    mapPinOutputs[12] = std::make_pair(2, 3);
    mapPinOutputs[13] = std::make_pair(15, 1);
}

void nts::c4008::Dump(void) const {
    AComponent::Dump("Chipset 4008 : ");
}

nts::Tristate nts::c4008::computeOuputOrCarryOut(size_t pin_num_this, bool computeCarry = false) const {
    Tristate result = UNDEFINED;
    Tristate carry = FALSE;

    if (!computeCarry && mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
        return UNDEFINED;
    if (pin[9 - 1])
        carry = pin[9 - 1]->Compute(link.at(9));
    for (size_t i = 10; i <= pin_num_this; ++i) {
        if (mapPinOutputs.find(i) != mapPinOutputs.end()) {
            size_t i1 = mapPinOutputs.at(i).first;
            size_t i2 = mapPinOutputs.at(i).second;
            int tmp = static_cast<int>(pin[i1 - 1]->Compute(link.at(i1))) +
                      static_cast<int>(pin[i2 - 1]->Compute(link.at(i2))) +
                      static_cast<int>(carry);
            carry = static_cast<Tristate>(tmp >> 1);
            result = static_cast<Tristate>(tmp & 1);
        }
    }
    if (computeCarry)
        return carry;
    return result;
}

nts::Tristate nts::c4008::computeOutput(size_t pin_num_this) const {
    return computeOuputOrCarryOut(pin_num_this);
}

nts::Tristate nts::c4008::computeCarryOut(size_t pin_num_this) const {
    return computeOuputOrCarryOut(pin_num_this, true);
}

