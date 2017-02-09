//
// Created by sauvau_m on 2/2/17.
//

#include <iostream>
#include <components/c4008.hpp>
#include <components/c4081.hpp>
#include "ComponentFactory.hpp"

nts::ComponentFactory::~ComponentFactory() {

}

nts::ComponentFactory::ComponentFactory() {
    mapPtr["input"] = std::bind(&ComponentFactory::createInput, this, std::placeholders::_1);
    mapPtr["output"] = std::bind(&ComponentFactory::createOutput, this, std::placeholders::_1);
    mapPtr["false"] = std::bind(&ComponentFactory::createFalse, this, std::placeholders::_1);
    mapPtr["true"] = std::bind(&ComponentFactory::createTrue, this, std::placeholders::_1);
    mapPtr["clock"] = std::bind(&ComponentFactory::createClock, this, std::placeholders::_1);
    mapPtr["4008"] = std::bind(&ComponentFactory::create4008, this, std::placeholders::_1);
    mapPtr["4081"] = std::bind(&ComponentFactory::create4081, this, std::placeholders::_1);
}

nts::Tristate nts::ComponentFactory::convertStringToTristate(std::string const &value) {
    if (value == "0")
        return FALSE;
    else if (value == "1")
        return TRUE;
    return UNDEFINED;
}

nts::IComponent *nts::ComponentFactory::createComponent(const std::string &type, const std::string &name) {
    if (mapPtr.find(type) == mapPtr.end())
        return NULL;
    return mapPtr[type](name);
}

nts::IComponent *nts::ComponentFactory::createInput(const std::string &name) const {
    return new Input(name);
}

nts::IComponent *nts::ComponentFactory::createOutput(const std::string &name) const {
    return new Output(name);
}

nts::IComponent *nts::ComponentFactory::createClock(const std::string &name) const {
    return new Clock(name);
}

nts::IComponent *nts::ComponentFactory::createFalse(const std::string &name) const {
    return new False(name);
}

nts::IComponent *nts::ComponentFactory::createTrue(const std::string &name) const {
    return new True(name);
}

nts::IComponent *nts::ComponentFactory::create4008(const std::string &value) const {
    (void)value;
    return new c4008();
}

nts::IComponent *nts::ComponentFactory::create4081(const std::string &value) const {
    (void)value;
    return new c4081();
}
