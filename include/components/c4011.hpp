//
// c4011.hpp for Nano in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 13:19:50 2017 Alexandre BLANCHARD
// Last update Mon Feb 13 13:23:41 2017 Alexandre BLANCHARD
//

#ifndef CPP_NANOTEKSPICE_C4011_HPP
# define CPP_NANOTEKSPICE_C4011_HPP

#include "AComponent.hpp"

namespace nts
{
  class	c4011 : public AComponent
  {
    Tristate output(size_t pin_num_this);

  public:
    virtual ~c4011();
    c4011(std::string const &name);
    void Dump(void) const;
  };
}

#endif // CPP_NANOTEKSPICE_C4011_HPP
