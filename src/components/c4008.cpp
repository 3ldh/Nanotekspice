//
// Created by sauvau_m on 2/7/17.
//

#include <Exception.hpp>
#include <components/Output.hpp>
#include <iostream>
#include "components/c4008.hpp"

nts::c4008::~c4008() {
}

nts::c4008::c4008(std::string const &name) : AComponent(name, 16) {

    // A4 to A1
    pinComputeFunction[1] = std::bind(&c4008::input, this, 1);
    pinComputeFunction[3] = std::bind(&c4008::input, this, 3);
    pinComputeFunction[5] = std::bind(&c4008::input, this, 5);
    pinComputeFunction[7] = std::bind(&c4008::input, this, 7);
    // B4 to B1
    pinComputeFunction[15] = std::bind(&c4008::input, this, 15);
    pinComputeFunction[6] = std::bind(&c4008::input, this, 7);
    pinComputeFunction[4] = std::bind(&c4008::input, this, 4);
    pinComputeFunction[2] = std::bind(&c4008::input, this, 2);
    //CarryIn
    pinComputeFunction[9] = std::bind(&c4008::input, this, 9);
    //carryOut
    pinComputeFunction[14] = std::bind(&c4008::carryOut, this, 14);
    //VDD
    pinComputeFunction[16] = std::bind(&c4008::vdd, this, 16);
    //VSS
    pinComputeFunction[8] = std::bind(&c4008::vss, this, 8);
    //Sum s1 to s4
    pinComputeFunction[10] = std::bind(&c4008::output, this, 10);
    pinComputeFunction[11] = std::bind(&c4008::output, this, 11);
    pinComputeFunction[12] = std::bind(&c4008::output, this, 12);
    pinComputeFunction[13] = std::bind(&c4008::output, this, 13);
    //output link with inputs
    mapPinOutputs[10] = std::make_pair(6, 7);
    mapPinOutputs[11] = std::make_pair(4, 5);
    mapPinOutputs[12] = std::make_pair(2, 3);
    mapPinOutputs[13] = std::make_pair(15, 1);
}

void nts::c4008::Dump(void) const {
    AComponent::Dump("Chipset 4008 : ");
}

nts::Tristate nts::c4008::outputOrCarryOut(size_t pin_num_this, bool computeCarry = false) const {
    Tristate result = UNDEFINED;
    Tristate carry = FALSE;

    if (!computeCarry && mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
        return UNDEFINED;
    if (pin.at(9))
        carry = pin.at(9)->Compute(link.at(9));
    for (size_t i = 10; i <= pin_num_this; ++i) {
        if (mapPinOutputs.find(i) != mapPinOutputs.end()) {
            size_t i1 = mapPinOutputs.at(i).first;
            size_t i2 = mapPinOutputs.at(i).second;
            Tristate a, b, tmp;
            pin.at(i1) ? a = pin.at(i1)->Compute(link.at(i1)) : a = UNDEFINED;
            pin.at(i2) ? b = pin.at(i2)->Compute(link.at(i2)) : b = UNDEFINED;
            tmp = tristate_xor(a, b);
            result = tristate_xor(tmp, carry);
            carry = tristate_or(tristate_and(a, b), tristate_and(tmp, carry));
        }
    }
    if (computeCarry)
        return carry;
    return result;
}

nts::Tristate nts::c4008::output(size_t pin_num_this) {
    return outputOrCarryOut(pin_num_this);
}

nts::Tristate nts::c4008::carryOut(size_t pin_num_this) const {
    return outputOrCarryOut(pin_num_this, true);
}

