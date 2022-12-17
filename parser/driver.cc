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

bool Driver::addFunction(std::string const & name) {
    if(functions.find(name) != functions.end()) { // Already exists.
        return false;
    }

    functions[name] = std::make_shared<Function>();

    // Move queued instructions inside the Function.
    for(auto & i : instructionBuffer) {
        functions[name]->addInstruction(i);
    }

    // Clear the queue.
    instructionBuffer.clear();

    return true;
}

void Driver::enqueueInstruction(std::shared_ptr<Instruction> instruction) {
    instructionBuffer.push_back(instruction);
}

bool Driver::runMain() {
    if(functions.find("main") == functions.end()) { // Not found
        return false;
    } else {
        functions.at("main")->execute(getJardin());
        return true;
    }
}