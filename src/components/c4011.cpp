//
// c4011.cpp for Nano in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 12:56:17 2017 Alexandre BLANCHARD
// Last update Mon Feb 13 14:08:10 2017 Alexandre BLANCHARD
//

#include "components/c4011.hpp"

nts::c4011::c4011(std::string const &name) : AComponent(name, 14) {
    // gate NAND 1
    pinComputeFunction[1] = std::bind(&c4011::input, this, 1);
    pinComputeFunction[2] = std::bind(&c4011::input, this, 2);
    pinComputeFunction[3] = std::bind(&c4011::output, this, 3);
    // gate NAND 2
    pinComputeFunction[5] = std::bind(&c4011::input, this, 5);
    pinComputeFunction[6] = std::bind(&c4011::input, this, 6);
    pinComputeFunction[4] = std::bind(&c4011::output, this, 4);
    // gate NAND 3
    pinComputeFunction[8] = std::bind(&c4011::input, this, 8);
    pinComputeFunction[9] = std::bind(&c4011::input, this, 9);
    pinComputeFunction[10] = std::bind(&c4011::output, this, 10);
    // gate NAND 4
    pinComputeFunction[12] = std::bind(&c4011::input, this, 12);
    pinComputeFunction[13] = std::bind(&c4011::input, this, 13);
    pinComputeFunction[11] = std::bind(&c4011::output, this, 11);
    // VSS
    pinComputeFunction[7] = std::bind(&c4011::output, this, 7);
    // VDD
    pinComputeFunction[14] = std::bind(&c4011::output, this, 14);
    // link output with input
    mapPinOutputs[3] = std::make_pair(1, 2);
    mapPinOutputs[4] = std::make_pair(5, 6);
    mapPinOutputs[10] = std::make_pair(8, 9);
    mapPinOutputs[11] = std::make_pair(12, 13);
}

nts::c4011::~c4011() {

}

nts::Tristate nts::c4011::output(size_t pin_num_this) {
    size_t i1;
    size_t i2;

    if (mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
        return UNDEFINED;
    i1 = mapPinOutputs.at(pin_num_this).first;
    i2 = mapPinOutputs.at(pin_num_this).second;
    return tristate_nand(pin.at(i1)->Compute(link.at(i1)), pin.at(i2)->Compute(link.at(i2)));
}

void nts::c4011::Dump(void) const {
    AComponent::Dump("Chipset 4011 : ");
}
