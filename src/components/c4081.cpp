//
// Created by sauvau_m on 2/9/17.
//

#include "components/c4081.hpp"


nts::c4081::~c4081() {

}

nts::c4081::c4081(std::string const &name) : AComponent(name, 14) {
    //gate AND 1
    pinComputeFunction[1] = std::bind(&c4081::input, this, 1);
    pinComputeFunction[2] = std::bind(&c4081::input, this, 2);
    pinComputeFunction[3] = std::bind(&c4081::output, this, 3);
    //gate AND 2
    pinComputeFunction[5] = std::bind(&c4081::input, this, 5);
    pinComputeFunction[6] = std::bind(&c4081::input, this, 6);
    pinComputeFunction[4] = std::bind(&c4081::output, this, 4);
    //gate AND 3
    pinComputeFunction[8] = std::bind(&c4081::input, this, 8);
    pinComputeFunction[9] = std::bind(&c4081::input, this, 9);
    pinComputeFunction[10] = std::bind(&c4081::output, this, 10);
    //gate AND 4
    pinComputeFunction[12] = std::bind(&c4081::input, this, 12);
    pinComputeFunction[13] = std::bind(&c4081::input, this, 13);
    pinComputeFunction[11] = std::bind(&c4081::output, this, 11);
    //VSS
    pinComputeFunction[7] = std::bind(&c4081::vss, this, 7);
    //VDD
    pinComputeFunction[14] = std::bind(&c4081::vdd, this, 14);
    //output link with inputs
    mapPinOutputs[3] = std::make_pair(1, 2);
    mapPinOutputs[4] = std::make_pair(5, 6);
    mapPinOutputs[10] = std::make_pair(8, 9);
    mapPinOutputs[11] = std::make_pair(12, 13);
}

nts::Tristate nts::c4081::output(size_t pin_num_this) {
    size_t i1;
    size_t i2;

    if (mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
        return UNDEFINED;
    i1 = mapPinOutputs.at(pin_num_this).first;
    i2 = mapPinOutputs.at(pin_num_this).second;
    return tristate_and(pin.at(i1)->Compute(link.at(i1)), pin.at(i2)->Compute(link.at(i2)));
}

void nts::c4081::Dump(void) const {
    AComponent::Dump("Cipset 4081 : ");
}