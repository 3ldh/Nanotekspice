//
// c4069.hpp for 4069 in /home/blanch_p/rendu/Semestre3/CPP/cpp_nanotekspice
//
// Made by Alexandre BLANCHARD
// Login   <blanch_p@epitech.net>
//
// Started on  Mon Feb 13 16:40:27 2017 Alexandre BLANCHARD
// Last update Mon Feb 13 16:42:31 2017 Alexandre BLANCHARD
//

#ifndef CPP_NANOTEKSPICE_C4069_HPP
# define CPP_NANOTEKSPICE_C4069_HPP

#include "AComponent.hpp"

namespace nts
{
  class c4069 : public AComponent
  {
    Tristate output(size_t pin_num_this);

  public:
    virtual ~c4069();
    c4069(std::string const &name);
    void Dump(void) const override;
  };
}

#endif // CPP_NANOTEKSPICE_C4069_HPP
