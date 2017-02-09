//
// Created by sauvau_m on 2/2/17.
//

#include <iostream>
#include <algorithm>
#include <csignal>
#include "Nanotekspice.hpp"

bool nts::Nanotekspice::looper = true;

nts::Nanotekspice::~Nanotekspice() {

}

nts::Nanotekspice::Nanotekspice(std::string const &filename, int ac, char const *const *const av) : mainLooper(true) {

    std::map<std::string, std::string> inputValue;

    for (int i = 0; i < ac; ++i) {
        std::string arg(av[i]);
        size_t found = arg.find_first_of("=");
        if (found != std::string::npos) {
            std::string value = arg.substr(found + 1, arg.size());
            if (value != "0" && value != "1")
                throw nts::SyntaxError("Input value must be equal to 0 or 1");
            inputValue[arg.substr(0, found)] = value;
        }
    }
    commmands["exit"] = std::bind(&Nanotekspice::exit, this);
    commmands["simulate"] = std::bind(&Nanotekspice::simulate, this);
    commmands["display"] = std::bind(&Nanotekspice::display, this);
    commmands["loop"] = std::bind(&Nanotekspice::loop, this);
    commmands["dump"] = std::bind(&Nanotekspice::dump, this);
    circuit = new nts::Circuit(filename, inputValue);
    mainLoop();
}

void nts::Nanotekspice::mainLoop() {
    std::string cmd;

    signal(SIGINT, cancelCancel);
    simulate();
    display();
    std::cout << ">";
    while (mainLooper && std::getline(std::cin, cmd)) {
        cmd = cleanCommand(cmd);
        if (commmands.find(cmd) != commmands.end())
            commmands[cmd]();
        else if (!setInputValue(cmd))
            std::cout << "Error : Unknow commmand line" << std::endl;
        if (mainLooper)
            std::cout << "> ";
    }
}

void nts::Nanotekspice::exit() {
    mainLooper = false;
}

void nts::Nanotekspice::loop() {
    Nanotekspice::looper = true;
    signal(SIGINT, cancel);
    while (Nanotekspice::looper) {
        simulate();
    }
    signal(SIGINT, cancelCancel);
}


void nts::Nanotekspice::simulate() {
    circuit->inverseClocks();
}


void nts::Nanotekspice::display() {
    if (circuit)
        circuit->display();
}

void nts::Nanotekspice::dump() {
    if (circuit)
        circuit->dump();
}

bool nts::Nanotekspice::setInputValue(std::string const &str) {
    size_t found = str.find_first_of("=");
    if (found != std::string::npos && circuit) {
        try {
            circuit->updateInput(str.substr(0, found), str.substr(found + 1, str.size()));
        } catch (NtsError const &err) {
            std::cout << err.what() << std::endl;
        }
        return true;
    }
    return false;
}

void nts::Nanotekspice::cancel(int i) {
    (void) i;
    nts::Nanotekspice::looper = false;
}

void nts::Nanotekspice::cancelCancel(int i) {
    (void) i;
}

std::string nts::Nanotekspice::cleanCommand(std::string const &cmd) {
    std::string tmp;
    std::unique_copy(cmd.begin(), cmd.end(), std::back_insert_iterator<std::string>(tmp),
                     [](char a, char b) { return isspace(a) && isspace(b); });
    tmp.erase(tmp.begin(), std::find_if(tmp.begin(), tmp.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    tmp.erase(std::find_if(tmp.rbegin(), tmp.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
              tmp.end());
    return tmp;
}