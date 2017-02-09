//
// Created by sauvau_m on 2/2/17.
//

#ifndef CPP_NANOTEKSPICE_PARSER_H
#define CPP_NANOTEKSPICE_PARSER_H

#include <sstream>
#include <map>
#include "IParser.hpp"
#include "IComponent.hpp"

namespace nts {
    class Circuit;
    class Parser : public nts::IParser {
        std::stringstream stream;
        std::map<std::string, std::string> inputValue;

        void createChipsetsSection(t_ast_node &node);
        void createLinksSection(t_ast_node &node);
        void createComponentsNodes(t_ast_node &node, std::string const &str);
        void createLinksNodes(t_ast_node &node, std::string const &str);
        void createLinksEndNodes(t_ast_node &node, std::string const &str);
        void checkChipsetsIntegrity(t_ast_node const &chipsetsNode, t_ast_node const &linksNode) const;
        void checkLinksIntegrity(t_ast_node const &chipsetsNode, t_ast_node const &linksNode) const;
        void checkLinkEndIntegrity(t_ast_node const &linkEndNode) const;
        void checkComponentIntegrity(t_ast_node const &node, nts::t_ast_node const &chipsetsNode) const;
        void checkComponentNameExist(t_ast_node const &chipsetsNode, t_ast_node const &linksNode) const;
        int checkNameOccurence(t_ast_node const &node, std::string const &name) const;
        int checkOutputLink(t_ast_node const &linksNode, std::string const &name) const;
        t_ast_node *findSection(t_ast_node const &root, std::string const &section) const;
        t_ast_node *createNewLineNode();
        bool isNumber(std::string const&);
    public:
        Parser(std::map<std::string, std::string> inputValue);
        virtual ~Parser();
        virtual void feed(std::string const &input);
        virtual void parseTree(t_ast_node &root);
        virtual nts::t_ast_node *createTree();
        void dumpStream() const;
        void createComponents(t_ast_node const &node, Circuit &circuit);
    };
}

#endif //CPP_NANOTEKSPICE_PARSER_H
