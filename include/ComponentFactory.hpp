//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_COMPONENTFACTORY_HPP
#define CPP_NANOTEKSPICE_COMPONENTFACTORY_HPP

#include <string>
#include <map>
#include <functional>
#include "components/Clock.hpp"
#include "components/False.hpp"
#include "components/True.hpp"
#include "components/Input.hpp"
#include "components/Output.hpp"

namespace nts {
    class ComponentFactory {
        std::map<std::string, std::function<IComponent *(std::string const&)> > mapPtr;
        IComponent *createInput(const std::string &value) const;
        IComponent *createOutput(const std::string &value) const;
        IComponent *createClock(const std::string &value) const;
        IComponent *createFalse(const std::string &value) const;
        IComponent *createTrue(const std::string &value) const;
        IComponent *create4008(const std::string &value) const;
    public:
        virtual ~ComponentFactory();
        ComponentFactory();
        IComponent *createComponent(const std::string &type, const std::string &value);
        static Tristate convertStringToTristate(std::string const &value);
    };
}

#endif //CPP_NANOTEKSPICE_COMPONENTFACTORY_HPP
