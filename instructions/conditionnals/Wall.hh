#pragma once

#include "Empty.hh"

/**
 * @brief An instruction that checks for a wall.
 */
class Wall: public Empty {
    public:
        /**
         * @brief Construct a new Wall instruction.
         * 
         * @param turtle The turtle to use.
         * @param dir The direction to check.
         */
        Wall(std::size_t turtle, CheckDirection const & dir);
        Wall(Wall const &) = default;
        ~Wall() override = default;

        bool execute(JardinRendering* const & garden) override;
};