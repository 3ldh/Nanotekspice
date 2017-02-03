//
// Created by sauvau_m on 2/2/17.
//

#include <Exception.hpp>
#include <fstream>
#include <iostream>
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
