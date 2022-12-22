#pragma once

#include "../Instruction.hh"

/**
 * @brief Directions around a turtle.
 */
enum class CheckDirection {
    /**
     * @brief Front of the turtle.
     */
    FRONT,

    /**
     * @brief Back of the turtle.
     */
    BACK,

    /**
     * @brief Left of the turtle.
     */
    LEFT,

    /**
     * @brief Right of the turtle.
     */
    RIGHT
};

/**
 * @brief An instruction that checks for a free space.
 */
class Empty: public Instruction {
    private:
        CheckDirection _direction;

    public:
        /**
         * @brief Construct a new Empty instruction.
         * 
         * @param turtle The turtle to use.
         * @param dir The direction to check.
         */
        Empty(std::size_t turtle, CheckDirection const & dir);
        Empty(Empty const &) = default;
        ~Empty() = default;

        bool execute(Field garden) override;
};