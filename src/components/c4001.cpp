//
// Created by sauvau_m on 2/9/17.
//

#include "components/c4001.hpp"

nts::c4001::~c4001() {

}

nts::c4001::c4001(std::string const &name) : AComponent(name, 14) {
    //gate NOR 1
    pinComputeFunction[1] = std::bind(&c4001::input, this, 1);
    pinComputeFunction[2] = std::bind(&c4001::input, this, 2);
    pinComputeFunction[3] = std::bind(&c4001::output, this, 3);
    //gate NOR 2
    pinComputeFunction[5] = std::bind(&c4001::input, this, 5);
    pinComputeFunction[6] = std::bind(&c4001::input, this, 6);
    pinComputeFunction[4] = std::bind(&c4001::output, this, 4);
    //gate NOR 3
    pinComputeFunction[8] = std::bind(&c4001::input, this, 8);
    pinComputeFunction[9] = std::bind(&c4001::input, this, 9);
    pinComputeFunction[10] = std::bind(&c4001::output, this, 10);
    //gate NOR 4
    pinComputeFunction[12] = std::bind(&c4001::input, this, 12);
    pinComputeFunction[13] = std::bind(&c4001::input, this, 13);
    pinComputeFunction[11] = std::bind(&c4001::output, this, 11);
    //VSS
    pinComputeFunction[7] = std::bind(&c4001::vss, this, 7);
    //VDD
    pinComputeFunction[14] = std::bind(&c4001::vdd, this, 14);
    //link output with inputs
    mapPinOutputs[3] = std::make_pair(1, 2);
    mapPinOutputs[4] = std::make_pair(5, 6);
    mapPinOutputs[10] = std::make_pair(8, 9);
    mapPinOutputs[11] = std::make_pair(12, 13);
}

nts::Tristate nts::c4001::output(size_t pin_num_this) {
    size_t i1;
    size_t i2;

    if (mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
        return UNDEFINED;
    i1 = mapPinOutputs.at(pin_num_this).first;
    i2 = mapPinOutputs.at(pin_num_this).second;
    return tristate_nor(pin.at(i1)->Compute(link.at(i1)), pin.at(i2)->Compute(link.at(i2)));
}

void nts::c4001::Dump(void) const {
    AComponent::Dump("Chipset 4001 : ");
}
