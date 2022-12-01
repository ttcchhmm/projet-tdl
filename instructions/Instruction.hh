#pragma once

#include <vector>
#include "jardinRendering.hh"

/**
 * @brief The type of the arguments required by the instruction.
 *
 * @tparam ArgumentType The arguments type.
 */
template <typename ArgumentType>

/**
 * @brief Represent an atomic instruction about the state of the garden or one of its turtles.
 */
class Instruction {
    public:
        /**
         * @brief Execute the instruction.
         *
         * @param garden The JardinRendering instance to work with.
         * @param target The targeted turtle.
         * @param args The arguments needed to run the instruction. No bounds verification will be made, so check before calling !
         * @return True if the instruction succeeded, false otherwise.
         */
        virtual bool execute(JardinRendering* const & garden, std::size_t const & target, std::vector<ArgumentType> const & args) = 0;

        /**
         * @brief Get the required number of arguments.
         *
         * @return The required number of arguments.
         */
        virtual unsigned int numberOfArguments() const = 0;
};