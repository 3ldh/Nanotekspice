//
// c4069.cpp for Nano in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 16:27:30 2017 Alexandre BLANCHARD
// Last update Wed Feb 15 15:42:12 2017 Alexandre BLANCHARD
//

#include "components/c4069.hpp"

nts::c4069::c4069() : AComponent(14)
{
  // Invert Gate 1
  pinComputeFunction[1] = std::bind(&c4069::computeInput, this, 1);
  pinComputeFunction[2] = std::bind(&c4069::computeOutput, this, 2);
  // Invert Gate 2
  pinComputeFunction[3] = std::bind(&c4069::computeInput, this, 3);
  pinComputeFunction[4] = std::bind(&c4069::computeOutput, this, 4);
  // Invert Gate 1
  pinComputeFunction[5] = std::bind(&c4069::computeInput, this, 5);
  pinComputeFunction[6] = std::bind(&c4069::computeOutput, this, 6);
  // Invert Gate 1
  pinComputeFunction[9] = std::bind(&c4069::computeInput, this, 9);
  pinComputeFunction[8] = std::bind(&c4069::computeOutput, this, 8);
  // Invert Gate 1
  pinComputeFunction[11] = std::bind(&c4069::computeInput, this, 11);
  pinComputeFunction[10] = std::bind(&c4069::computeOutput, this, 10);
  // Invert Gate 1
  pinComputeFunction[13] = std::bind(&c4069::computeInput, this, 13);
  pinComputeFunction[12] = std::bind(&c4069::computeOutput, this, 12);
  // VSS
  pinComputeFunction[7] = std::bind(&c4069::computeOutput, this, 7);
  // VDD
  pinComputeFunction[14] = std::bind(&c4069::computeOutput, this, 14);
  // link input with output

  mapPinOutputs[2] = std::make_pair(1, 1);
  mapPinOutputs[4] = std::make_pair(3, 3);
  mapPinOutputs[6] = std::make_pair(5, 5);
  mapPinOutputs[8] = std::make_pair(9, 9);
  mapPinOutputs[10] = std::make_pair(11, 11);
  mapPinOutputs[12] = std::make_pair(13, 13);

  // mapPinOutputs[2] = 1;
  // mapPinOutputs[4] = 3;
  // mapPinOutputs[6] = 5;
  // mapPinOutputs[8] = 9;
  // mapPinOutputs[10] = 11;
  // mapPinOutputs[12] = 13;
}

nts::c4069::~c4069()
{

}

nts::Tristate	nts::c4069::computeOutput(size_t pin_num_this) const
{
  Tristate	result;
  size_t	i1;

  if (mapPinOutputs.find(pin_num_this) == mapPinOutputs.end())
    return UNDEFINED;
  i1 = mapPinOutputs.at(pin_num_this).first;
  result = static_cast<Tristate>(!pin.at(i1)->Compute(link.at(i1)));
  return (result);
}

void	nts::c4069::Dump(void) const
{
  AComponent::Dump("Chipset 4069 : ");
}
