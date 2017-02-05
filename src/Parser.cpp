//
// Created by sauvau_m on 2/2/17.
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include <Exception.hpp>
#include "Parser.hpp"

nts::Parser::~Parser() {
    //TODO delete tree
}


nts::Parser::Parser(std::vector<std::pair<std::string const &, std::string const &>> inputValue) {

}

void nts::Parser::feed(std::string const &input) {
    std::string tmp;
    std::unique_copy(input.begin(), input.end(), std::back_insert_iterator<std::string>(tmp),
                     [](char a, char b) { return isspace(a) && isspace(b); });
    tmp.erase(tmp.begin(), std::find_if(tmp.begin(), tmp.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    tmp.erase(std::find_if(tmp.rbegin(), tmp.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              tmp.end());
    size_t comment = tmp.find_first_of("#");
    stream << tmp.substr(0, comment) << std::endl;
}

nts::t_ast_node *nts::Parser::createTree() {
    t_ast_node *tree = new t_ast_node(new std::vector<t_ast_node *>());
    tree->lexeme = "root";
    tree->type = ASTNodeType::DEFAULT;
    tree->value = "root";

    while (!stream.eof()) {
        t_ast_node *node = new t_ast_node(new std::vector<t_ast_node *>());
        int input_char = stream.get();
        node->lexeme = "DEFAULT";
        if (input_char == '\n') {
            node->type = ASTNodeType::NEWLINE;
            node->lexeme = "newline";
            node->value = "\n";
        } else if (input_char == '.') {
            int peek_character = stream.peek();
            if (peek_character == 'c')
                createChipsetsSection(*node);
            else if (peek_character == 'l')
                createLinksSection(*node);
            else if (!stream.eof())
                throw nts::SyntaxError("SyntaxError : No section define");
        } else if (!stream.eof()) {
            throw nts::SyntaxError("SyntaxError : Unknown section");
        }
        tree->children->push_back(node);
    }
    return tree;
}

void nts::Parser::dumpStream() const {
    std::cout << stream.str() << std::endl;
}

void nts::Parser::createChipsetsSection(t_ast_node &section_node) {
    int input_char;
    char tmp[11];
    stream.get(tmp, 11);
    std::string section(tmp);
    if (section != "chipsets:")
        return;
    section_node.type = ASTNodeType::SECTION;
    section_node.lexeme = "chipsets";
    section_node.value = "chipsets";
    stream.get();
    while (true) {
        if (!stream.eof() && stream.peek() != '\n') {
            t_ast_node *node_component = new t_ast_node(new std::vector<t_ast_node *>());
            std::string str;
            node_component->lexeme = "component";
            node_component->type = ASTNodeType::COMPONENT;
            while (!stream.eof() && stream.peek() != '.') {
                input_char = stream.get();
                if (input_char == '\n') {
                    node_component->children->push_back(createNewLineNode());
                    break;
                } else if (input_char == ' ' || input_char == '\t') {
                    createComponentsNodes(*node_component, str);
                    str.clear();
                    break;
                } else if (isalnum(input_char))
                    str += input_char;
                else if (!stream.eof()) {
                    throw nts::SyntaxError("SyntaxError : in Chipset section");
                }
            }
            section_node.children->push_back(node_component);
        } else {
            stream.get();
            section_node.children->push_back(createNewLineNode());
        }
        if (stream.eof() || stream.peek() == '.')
            break;
    }
}

void nts::Parser::createComponentsNodes(nts::t_ast_node &node_component, std::string const &str) {
    int input_char;
    std::string val;
    t_ast_node *component_type_node = new t_ast_node(NULL);
    component_type_node->type = ASTNodeType::STRING;
    component_type_node->lexeme = "component type";
    component_type_node->value = str;
    node_component.children->push_back(component_type_node);
    while (!stream.eof()) {
        input_char = stream.get();
        if (input_char == '\n') {
            t_ast_node *component_value_node = new t_ast_node(NULL);
            component_value_node->type = ASTNodeType::STRING;
            component_value_node->lexeme = "component name";
            component_value_node->value = val;
            node_component.children->push_back(component_value_node);
            node_component.children->push_back(createNewLineNode());
            break;
        } else if (isalnum(input_char))
            val += input_char;
        else if (!stream.eof())
            throw nts::SyntaxError(
                    "SyntaxError Chipsets Section : [componentType] [spaces] [componentName] [newLine]");
    }
}

void nts::Parser::createLinksSection(t_ast_node &section_node) {
    int input_char;
    char tmp[8];
    stream.get(tmp, 8);
    std::string section(tmp);
    if (section != "links:")
        return;
    section_node.type = ASTNodeType::SECTION;
    section_node.lexeme = "links";
    section_node.value = "links";
    stream.get();
    while (true) {
        if (!stream.eof() && stream.peek() != '\n') {
            t_ast_node *node_link = new t_ast_node(new std::vector<t_ast_node *>());
            std::string str;
            node_link->lexeme = "link";
            node_link->type = ASTNodeType::LINK;
            while (!stream.eof()) {
                input_char = stream.get();
                if (input_char == '\n') {
                    node_link->children->push_back(createNewLineNode());
                    break;
                } else if (input_char == ' ' || input_char == '\t') {
                    createLinksNodes(*node_link, str);
                    str.clear();
                    break;
                } else if (isalnum(input_char) || input_char == ':')
                    str += input_char;
                else if (!stream.eof())
                    throw nts::SyntaxError(
                            "SyntaxError : The circuit file includes one or several lexical errors or syntactic errors");
            }
            section_node.children->push_back(node_link);
        } else {
            stream.get();
            section_node.children->push_back(createNewLineNode());
        }
        if (stream.eof() || stream.peek() == '.')
            break;
    }
}

void nts::Parser::createLinksEndNodes(t_ast_node &node_link, std::string const &str) {
    t_ast_node *link_end_node = new t_ast_node(new std::vector<t_ast_node *>());
    link_end_node->type = ASTNodeType::LINK_END;
    link_end_node->lexeme = "link end";
    link_end_node->value = "link end";
    size_t found_separator = str.find_first_of(":");
    if (found_separator == std::string::npos)
        throw nts::SyntaxError(
                "SyntaxError :  - Link - component name and pin value should be separated by a \":\" - " + str);
    if (!isNumber(str.substr(found_separator + 1, str.size())))
        throw nts::SyntaxError(
                "SyntaxError :  - Link - Pin value should be a number instead found : " +
                str.substr(found_separator + 1, str.size()));
    t_ast_node *component_name_link = new t_ast_node(NULL);
    component_name_link->type = ASTNodeType::STRING;
    component_name_link->lexeme = "component name for link";
    component_name_link->value = str.substr(0, found_separator);
    t_ast_node *pin_ref_link = new t_ast_node(NULL);
    pin_ref_link->type = ASTNodeType::STRING;
    pin_ref_link->lexeme = "pin number for link";
    pin_ref_link->value = str.substr(found_separator + 1, str.size());
    link_end_node->children->push_back(component_name_link);
    link_end_node->children->push_back(pin_ref_link);
    node_link.children->push_back(link_end_node);
}

void nts::Parser::createLinksNodes(t_ast_node &node_link, std::string const &str) {
    int input_char;
    std::string second_link_end_str;
    createLinksEndNodes(node_link, str);
    while (!stream.eof()) {
        input_char = stream.get();
        if (input_char == '\n') {
            createLinksEndNodes(node_link, second_link_end_str);
            node_link.children->push_back(createNewLineNode());
            break;
        } else if (isalnum(input_char) || input_char == ':')
            second_link_end_str += input_char;
        else if (!stream.eof())
            throw nts::SyntaxError(
                    "SyntaxError Link Section : [componentName]:[pinNumber] [spaces] [componentName]:[pinNumber] [newLine]");
    }
}

nts::t_ast_node *nts::Parser::createNewLineNode() {
    t_ast_node *newline_node = new t_ast_node(NULL);
    newline_node->type = ASTNodeType::NEWLINE;
    newline_node->lexeme = "newline";
    newline_node->value = "\n";
    return newline_node;
}

void nts::Parser::parseTree(nts::t_ast_node &root) {
    t_ast_node *chipsets = findSection(root, "chipsets");
    t_ast_node *links = findSection(root, "links");
    if (!chipsets)
        throw NtsError("Missing chipsets sections");
    if (!links)
        throw NtsError("Missing links sections");
    checkLinksIntegrity(*chipsets, *links);
    checkChipsetsIntegrity(*chipsets, *links);
    checkComponentNameExist(*chipsets, *links);
}

void nts::Parser::checkChipsetsIntegrity(const nts::t_ast_node &chipsets, const nts::t_ast_node &links) const {
    if (chipsets.children) {
        for (int i = 0; i < chipsets.children->size(); ++i) {
            checkComponentIntegrity(*(*chipsets.children)[i], links);
        }
        for (int i = 0; i < chipsets.children->size(); ++i) {
            if ((*chipsets.children)[i]->type == ASTNodeType::COMPONENT) {
                int count = checkNameOccurence(chipsets, (*(*chipsets.children)[i]->children)[1]->value);
                if (count > 1)
                    throw NtsError(
                            "Error : Component name \"" + (*(*chipsets.children)[i]->children)[1]->value +
                            "\" already exist");
            }
        }
    }
}

void nts::Parser::checkComponentIntegrity(nts::t_ast_node const &node, nts::t_ast_node const &linksNode) const {
    if (node.type == ASTNodeType::COMPONENT) {
        if (node.children->size() != 3 || (*node.children)[0]->type != ASTNodeType::STRING
            || (*node.children)[1]->type != ASTNodeType::STRING || (*node.children)[2]->type != ASTNodeType::NEWLINE) {
            throw NtsError("Error : Component integrity compromised check your file.nts."
                                   "Chipset section Syntax : [componentType] [spaces] [componentName] [newLine]");
        }
        if ((*node.children)[0]->value == "output") {
            int outputLinkCount = checkOutputLink(linksNode, (*node.children)[1]->value);
            if (outputLinkCount == 0)
                throw NtsError("Error : Output " + (*node.children)[1]->value + " has not been linked");
            if (outputLinkCount > 1)
                throw NtsError("Error : Output " + (*node.children)[1]->value + " has been linked multiple times");
        }
    }
}

int nts::Parser::checkNameOccurence(const nts::t_ast_node &node, std::string const &name) const {
    int count = 0;
    if (node.children) {
        for (int i = 0; i < node.children->size(); ++i) {
            if ((*node.children)[i]->type == ASTNodeType::COMPONENT) {
                std::string tmp = (*(*node.children)[i]->children)[1]->value;
                if (tmp == name)
                    count++;
            }
        }
    }
    return count;
}

int nts::Parser::checkOutputLink(const nts::t_ast_node &linksNode, std::string const &name) const {
    int count = 0;
    if (linksNode.children) {
        for (int i = 0; i < linksNode.children->size(); ++i) {
            if ((*linksNode.children)[i]->type == ASTNodeType::LINK && (*linksNode.children)[i]->children) {

                t_ast_node *linkEnd = (*(*linksNode.children)[i]->children)[0];
                std::string tmp = (*linkEnd->children)[0]->value;
                if (tmp == name)
                    count++;
            }
        }
    }
    return count;
}

void nts::Parser::checkLinksIntegrity(const nts::t_ast_node &chipsetsNode, const nts::t_ast_node &linksNode) const {
    if (linksNode.children) {
        for (int i = 0; i < linksNode.children->size(); ++i) {
            if ((*linksNode.children)[i]->type == ASTNodeType::LINK) {
                if ((*linksNode.children)[i]->children->size() != 3 ||
                    (*(*linksNode.children)[i]->children)[0]->type != ASTNodeType::LINK_END ||
                    (*(*linksNode.children)[i]->children)[1]->type != ASTNodeType::LINK_END ||
                    (*(*linksNode.children)[i]->children)[2]->type != ASTNodeType::NEWLINE) {
                    throw NtsError("Error : Links integrity compromised check your file.nts."
                                           "Link Section section: [componentName]:[pinNumber] [spaces] [componentName]:[pinNumber] [newLine]");

                }
                checkLinkEndIntegrity(*(*(*linksNode.children)[i]->children)[0]);
                checkLinkEndIntegrity(*(*(*linksNode.children)[i]->children)[1]);
            }
        }
    }
}

void nts::Parser::checkLinkEndIntegrity(const nts::t_ast_node &linkEndNode) const {
    if (linkEndNode.children->size() != 2 || (*linkEndNode.children)[0]->type != ASTNodeType::STRING
        || (*linkEndNode.children)[1]->type != ASTNodeType::STRING)
        throw NtsError("Error : Links integrity compromised check your file.nts."
                               "Link Section section: [componentName]:[pinNumber] [spaces] [componentName]:[pinNumber] [newLine]");

}

void nts::Parser::checkComponentNameExist(const nts::t_ast_node &chipsetsNode, const nts::t_ast_node &linksNode) const {
    if (linksNode.children) {
        for (int i = 0; i < linksNode.children->size(); ++i) {
            if ((*linksNode.children)[i]->type == ASTNodeType::LINK) {
                int count1 = checkNameOccurence(chipsetsNode, (*(*(*linksNode.children)[0]->children)[0]->children)[0]->value);
                int count2 = checkNameOccurence(chipsetsNode, (*(*(*linksNode.children)[0]->children)[1]->children)[0]->value);
                if (count1 == 0)
                    throw NtsError("Error link section : Can't find component named \"" + (*(*(*linksNode.children)[0]->children)[0]->children)[0]->value + "\"");
                if (count2 == 0)
                    throw NtsError("Error link section : Can't find component named \"" + (*(*(*linksNode.children)[0]->children)[1]->children)[0]->value + "\"");
            }
        }
    }
}

nts::t_ast_node *nts::Parser::findSection(t_ast_node const &root, std::string const &section) const {
    if (root.children) {
        for (int i = 0; i < root.children->size(); ++i) {
            if ((*root.children)[i]->lexeme == section)
                return ((*root.children)[i]);
        }
    }
    return (NULL);
}

bool nts::Parser::isNumber(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
