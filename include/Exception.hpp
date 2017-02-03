//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_EXCEPTION_HPP
#define CPP_NANOTEKSPICE_EXCEPTION_HPP


#include <exception>
#include <string>

namespace nts {
    class NtsError :public std::exception {
        std::string msg;
    public:
        virtual ~NtsError() throw();
        NtsError() throw();
        NtsError(const std::string &msg) throw();
        virtual const char *what() const throw();
    };

    class ChipsetError : public NtsError {
    public:
        virtual ~ChipsetError() throw();
        ChipsetError() throw();
        ChipsetError(const std::string &msg) throw();
    };

    class PinError : public ChipsetError {
    public:
        virtual ~PinError() throw();
        PinError() throw();
        PinError(const std::string &msg) throw();
    };

    class LinkError : public NtsError {
    public:
        virtual ~LinkError() throw();
        LinkError() throw();
        LinkError(const std::string &msg) throw();
    };

    class SyntaxError : public NtsError {
    public:
        virtual ~SyntaxError() throw();
        SyntaxError() throw();
        SyntaxError(const std::string &msg) throw();
    };

    class FileError : public NtsError {
    public:
        virtual ~FileError() throw();
        FileError() throw();
        FileError(const std::string &msg) throw();
    };
}

#endif //CPP_NANOTEKSPICE_EXCEPTION_HPP
