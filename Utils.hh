#pragma once

#include "instructions/Instruction.hh"

#include <list>
#include <memory>

/**
 * @brief Represent a linked list of shared pointers to instructions.
 */
using InstructionList = std::list<std::shared_ptr<Instruction>>;