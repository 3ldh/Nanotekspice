//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_PARSER_H
#define CPP_NANOTEKSPICE_PARSER_H

#include <sstream>
#include "IParser.hpp"

namespace nts {
    class Parser : public nts::IParser {
        std::stringstream stream;

        void createChipsetsNodes(t_ast_node &node);
        void createLinksNodes(t_ast_node &node);
        void createComponentsNodes(t_ast_node &node, std::string const &str);
        void createLinksNodes(t_ast_node &node, std::string const &str);
        void createLinksEndNodes(t_ast_node &node, std::string const &str);
        void checkChipsetsIntegrity(t_ast_node const &chipsetsNode) const;
        void checkComponentIntegrity(t_ast_node const &node, nts::t_ast_node const &chipsets_node) const;
        int checkExistingName(t_ast_node const &node, std::string const &name) const;
        t_ast_node *findSection(t_ast_node const &root, std::string const &section) const;
        t_ast_node *createNewLineNode();

    public:
        Parser(std::vector< std::pair<std::string const&, std::string const&> > inputValue);
        virtual ~Parser();
        virtual void feed(std::string const &input);
        virtual void parseTree(t_ast_node &root);
        virtual nts::t_ast_node *createTree();
        void checkIntegrity(t_ast_node const &root, t_ast_node const *node) const;
        void dumpStream() const;
    };
}

#endif //CPP_NANOTEKSPICE_PARSER_H