//
// c4030.hpp for Nano in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 14:53:28 2017 Alexandre BLANCHARD
// Last update Mon Feb 13 14:56:54 2017 Alexandre BLANCHARD
//

#ifndef CPP_NANOTEKSPICE_C4030_HPP
# define CPP_NANOTEKSPICE_C4030_HPP

#include "AComponent.hpp"

namespace nts
{
  class c4030 : public AComponent
  {
    Tristate computeOutput(size_t pin_num_this) const;

  public:
    virtual ~c4030();
    c4030(std::string const &name);
    void Dump(void) const override;
  };
}

#endif // CPP_NANOTEKSPICE_C4030_HPP
