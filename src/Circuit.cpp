//
// Created by sauvau_m on 2/2/17.
//

#include <Exception.hpp>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ComponentFactory.hpp>
#include "Circuit.hpp"

nts::Circuit::~Circuit() {
    delete (parser);
}

nts::Circuit::Circuit(const std::string &file,
                      std::vector<std::pair<std::string const &, std::string const &> > inputValue) {

    size_t found = file.find_last_of(".");
    if (found == std::string::npos || file.substr(found, file.size()) != ".nts")
        throw nts::FileError("FileError : Bad file format");
    std::ifstream ifs;
    ifs.open(file.c_str());
    if (ifs.is_open()) {
        try {
            std::string buffer;
            parser = new Parser(inputValue);
            while (std::getline(ifs, buffer))
                parser->feed(buffer);
            parser->dumpStream();
            tree = parser->createTree();
            dumpTree(tree);
            parser->parseTree(*tree);
            parser->createComponents(*tree, *this);
        } catch (nts::NtsError const &err) {
            throw err;
        }
        ifs.close();
    } else
        throw nts::FileError("FileError : Can't open file : " + file);
}

void nts::Circuit::dumpTree(t_ast_node *node) const {
    if (node) {
        if (node->children)
            std::cout << node->lexeme << " : " << node->children->size() << std::endl;
        else
            std::cout << node->lexeme << std::endl;
        if (node->type != ASTNodeType::NEWLINE && node->type != ASTNodeType::COMPONENT
            && node->type != ASTNodeType::LINK && node->type != ASTNodeType::LINK_END)
            std::cout << "\t" << node->value << std::endl;
        if (node->children) {
            for (int i = 0; i < node->children->size(); ++i) {
                dumpTree((*node->children)[i]);
            }
        }
    }
}

void nts::Circuit::inverseClocks() {
    std::for_each(clocks.begin(), clocks.end(), [](std::pair<std::string, Clock *> const &pair) {
        pair.second->inverse();
    });
}

void nts::Circuit::display() {
    std::for_each(outputs.begin(), outputs.end(), [](std::pair<std::string, Output *> const &pair) {
        std::cout << pair.first << "=" << pair.second->Compute(1) << std::endl;
    });
}

void nts::Circuit::dump() {
    std::for_each(components.begin(), components.end(), [](std::pair<std::string, IComponent *> const &pair) {
        pair.second->Dump();
    });
}

void nts::Circuit::updateInput(std::string const &inputName, std::string const &inputValue) {
    if (inputs.find(inputName) == inputs.end())
        throw nts::NtsError("Error : \"" + inputName + "\" is not an input");
    inputs[inputName]->setValue(ComponentFactory::convertStringToTristate(inputValue));
}

std::map<std::string, nts::Input *> &nts::Circuit::getInputs() {
    return inputs;
}

std::map<std::string, nts::Output *> &nts::Circuit::getOutputs() {
    return outputs;
}

std::map<std::string, nts::Clock *> &nts::Circuit::getClocks() {
    return clocks;
}

std::map<std::string, nts::True *> &nts::Circuit::getTrues() {
    return trues;
}

std::map<std::string, nts::False *> &nts::Circuit::getFalses() {
    return falses;
}

std::map<std::string, nts::IComponent *> &nts::Circuit::getComponents() {
    return components;
}
