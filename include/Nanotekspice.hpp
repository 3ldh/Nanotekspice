//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_NANOTEKSPICE_HPP
#define CPP_NANOTEKSPICE_NANOTEKSPICE_HPP

#include <map>
#include <functional>
#include "Exception.hpp"
#include "Circuit.hpp"

namespace nts {
    class Nanotekspice {
        bool mainLooper;
        nts::Circuit *circuit;
        std::map<std::string, std::function<void(void)> > commmands;

        bool setInputValue(std::string const& str);
        void exit();
        void display();
        void simulate();
        void loop();
        void dump();
        std::string cleanCommand(std::string const &cmd);

        static void cancel(int);
        static void cancelCancel(int);

    public:
        static bool looper;
        virtual ~Nanotekspice();
        Nanotekspice(std::string const &filename, int ac, char const * const * const av);
        void mainLoop();
    };
}



#endif //CPP_NANOTEKSPICE_NANOTEKSPICE_HPP
