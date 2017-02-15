//
// c4030.cpp for 4030 in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 14:44:27 2017 Alexandre BLANCHARD
// Last update Mon Feb 13 14:59:58 2017 Alexandre BLANCHARD
//

#include "components/c4030.hpp"

nts::c4030::c4030(std::string const &name) : AComponent(name, 14)
{
  // gate XOR 1
  pinComputeFunction[1] = std::bind(&c4030::computeInput, this, 1);
  pinComputeFunction[2] = std::bind(&c4030::computeInput, this, 2);
  pinComputeFunction[3] = std::bind(&c4030::computeOutput, this, 3);
  // gate XOR 2
  pinComputeFunction[5] = std::bind(&c4030::computeInput, this, 5);
  pinComputeFunction[6] = std::bind(&c4030::computeInput, this, 6);
  pinComputeFunction[4] = std::bind(&c4030::computeOutput, this, 4);
  // gate XOR 3
  pinComputeFunction[8] = std::bind(&c4030::computeInput, this, 8);
  pinComputeFunction[9] = std::bind(&c4030::computeInput, this, 9);
  pinComputeFunction[10] = std::bind(&c4030::computeOutput, this, 10);
  // gate XOR 4
  pinComputeFunction[12] = std::bind(&c4030::computeInput, this, 12);
  pinComputeFunction[13] = std::bind(&c4030::computeInput, this, 13);
  pinComputeFunction[11] = std::bind(&c4030::computeOutput, this, 11);
  // VSS
  pinComputeFunction[7] = std::bind(&c4030::computeOutput, this, 7);
  // VDD
  pinComputeFunction[14] = std::bind(&c4030::computeOutput, this, 14);
  // link output with input
  mapPinOutputs[3] = std::make_pair(1, 2);
  mapPinOutputs[4] = std::make_pair(5, 6);
  mapPinOutputs[10] = std::make_pair(8, 9);
  mapPinOutputs[11] = std::make_pair(12, 13);
}

nts::c4030::~c4030()
{

}

nts::Tristate	nts::c4030::computeOutput(size_t pin_num_this) const
{
  Tristate	result;
  size_t	i1;
  size_t	i2;

  if (mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
    return (UNDEFINED);
  i1 = mapPinOutputs.at(pin_num_this).first;
  i2 = mapPinOutputs.at(pin_num_this).second;
  result = static_cast<Tristate>(pin.at(i1)->Compute(link.at(i1)) xor pin.at(i2)->Compute(link.at(i2)));
  return (result);
}

void	nts::c4030::Dump(void) const
{
  AComponent::Dump("Chipset 4030 : ");
}
