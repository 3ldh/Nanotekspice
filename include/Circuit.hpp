//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_CIRCUIT_HPP
#define CPP_NANOTEKSPICE_CIRCUIT_HPP


#include "Parser.hpp"

namespace nts {
    class Circuit {
        nts::t_ast_node *tree;
        std::string file;
        Parser *parser;
    public:
        virtual ~Circuit();
        Circuit(const std::string &file, std::vector<std::pair<std::string const&, std::string const&> > inputValue);
        void dumpTree(t_ast_node *node) const;
    };
}

#endif //CPP_NANOTEKSPICE_CIRCUIT_HPP
