//
// Created by sauvau_m on 2/2/17.
//

#include <iostream>
#include "ComponentFactory.hpp"

nts::ComponentFactory::~ComponentFactory() {

}

nts::ComponentFactory::ComponentFactory() {
    mapPtr["input"] = std::bind(&ComponentFactory::createInput, this, std::placeholders::_1);
    mapPtr["output"] = std::bind(&ComponentFactory::createOutput, this, std::placeholders::_1);
    mapPtr["false"] = std::bind(&ComponentFactory::createFalse, this, std::placeholders::_1);
    mapPtr["true"] = std::bind(&ComponentFactory::createTrue, this, std::placeholders::_1);
    mapPtr["clock"] = std::bind(&ComponentFactory::createClock, this, std::placeholders::_1);
}

nts::Tristate nts::ComponentFactory::convertStringToTristate(std::string const &value) {
    if (value == "0")
        return FALSE;
    else if (value == "1")
        return TRUE;
    return UNDEFINED;
}

nts::IComponent *nts::ComponentFactory::createComponent(const std::string &type, const std::string &value) {
    if (mapPtr.find(type) == mapPtr.end())
        return NULL;
    return mapPtr[type](value);
}

nts::IComponent *nts::ComponentFactory::createInput(const std::string &value) const {
    return new Input(convertStringToTristate(value));
}

nts::IComponent *nts::ComponentFactory::createOutput(const std::string &value) const {
    (void)value;
    return new Output();
}

nts::IComponent *nts::ComponentFactory::createClock(const std::string &value) const {
    return new Clock(convertStringToTristate(value));
}

nts::IComponent *nts::ComponentFactory::createFalse(const std::string &value) const {
    (void)value;
    return new False();
}

nts::IComponent *nts::ComponentFactory::createTrue(const std::string &value) const {
    (void)value;
    return new True();
}