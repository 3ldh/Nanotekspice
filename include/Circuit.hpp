//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_CIRCUIT_HPP
#define CPP_NANOTEKSPICE_CIRCUIT_HPP


#include <map>
#include <components/Clock.hpp>
#include <components/True.hpp>
#include <components/False.hpp>
#include <components/Output.hpp>
#include <components/Input.hpp>
#include "Parser.hpp"

namespace nts {
    class Circuit {
        nts::t_ast_node *tree;
        Parser *parser;
        std::map<std::string, Input *> inputs;
        std::map<std::string, Output *> outputs;
        std::map<std::string, Clock *> clocks;
        std::map<std::string, True *> trues;
        std::map<std::string, False *> falses;
        std::map<std::string, IComponent *> components;

    public:
        virtual ~Circuit();
        Circuit(const std::string &file, std::map<std::string, std::string> inputValue);
        void dumpTree(t_ast_node *node) const;
        void updateInput(std::string const &inputName, std::string const &inputValue);
        void display();
        void dump();
        void inverseClocks();

        std::map<std::string, Input *> &getInputs();
        std::map<std::string, Output *> &getOutputs();
        std::map<std::string, Clock *> &getClocks();
        std::map<std::string, True *> &getTrues();
        std::map<std::string, False *> &getFalses();
        std::map<std::string, IComponent *> &getComponents();
    };
}

#endif //CPP_NANOTEKSPICE_CIRCUIT_HPP
