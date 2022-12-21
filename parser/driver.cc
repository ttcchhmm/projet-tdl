#include "driver.hh"
#include "jardinHandler.hh"
#include <iostream>

Driver::Driver(JardinHandler * J) {
    monJardin = J;
}

Driver::~Driver() {
	delete monJardin;
}

const Contexte& Driver::getContexte() const {
    return variables;
}

double Driver::getVariable(const std::string & name) const {
    return variables.get(name);
}

void Driver::setVariable(const std::string & name, double value) {
    variables[name] = value;
}

JardinRendering * Driver::getJardin() {
    return monJardin->getJardinRendering();
}

bool Driver::addFunction(std::string const & name, std::list<std::shared_ptr<Instruction>> const & instructions) {
    if(functions.find(name) != functions.end()) { // Already exists.
        return false;
    }

    functions[name] = std::make_shared<Function>();

    for(auto const & i : instructions) {
        functions[name]->addInstruction(i);
    }

    return true;
}

bool Driver::runMain() {
    if(functions.find("main") == functions.end()) { // Not found
        return false;
    } else {
        return functions.at("main")->execute(getJardin());
    }
}

std::shared_ptr<Function>& Driver::getFunction(std::string const & name) {
    return functions.at(name);
}