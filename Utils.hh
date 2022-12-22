#pragma once

#include "GUI/jardinRendering.hh"

#include <list>
#include <memory>

class Instruction;

/**
 * @brief Represent a linked list of shared pointers to instructions.
 */
using InstructionList = std::list<std::shared_ptr<Instruction>>;

/**
 * @brief Represent a pointer to the field.
 */
using Field = JardinRendering* const &;