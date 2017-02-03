//
// Created by sauvau_m on 2/2/17.
//

#include "Exception.hpp"

nts::NtsError::~NtsError() throw() {

}

const char *nts::NtsError::what() const throw() {
    return msg.c_str();
}

nts::NtsError::NtsError() throw() {}

nts::NtsError::NtsError(const std::string &msg) throw() : msg(msg) {}

nts::ChipsetError::~ChipsetError() throw() {

}

nts::ChipsetError::ChipsetError() throw() : NtsError() {

}

nts::ChipsetError::ChipsetError(const std::string &msg) throw() : NtsError(msg) {

}

nts::PinError::~PinError() throw() {

}

nts::PinError::PinError() throw() : ChipsetError() {

}

nts::PinError::PinError(const std::string &msg) throw() : ChipsetError(msg) {

}

nts::LinkError::~LinkError() throw() {

}

nts::LinkError::LinkError() throw() : NtsError() {

}

nts::LinkError::LinkError(const std::string &msg) throw() : NtsError(msg) {

}

nts::SyntaxError::~SyntaxError() throw() {

}

nts::SyntaxError::SyntaxError() throw() : NtsError() {

}

nts::SyntaxError::SyntaxError(const std::string &msg) throw() : NtsError(msg) {

}

nts::FileError::~FileError() throw() {

}

nts::FileError::FileError() throw() : NtsError() {

}

nts::FileError::FileError(const std::string &msg) throw() : NtsError(msg) {

}
