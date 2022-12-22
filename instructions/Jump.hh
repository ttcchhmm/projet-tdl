#pragma once

#include "Instruction.hh"

/**
 * @brief An instruction that makes a turtle jump.
 */
class Jump: public Instruction {
    private:
        /**
         * @brief The number of jumps to perform.
         */
        unsigned int _amount;

    public:
        /**
         * @brief Construct a new Jump instance.
         * 
         * @param turtle The targeted turtle.
         * @param amount The number of jumps to perform.
         */
        Jump(std::size_t turtle, unsigned int amount);
        Jump(Jump const &) = default;
        ~Jump() = default;

        bool execute(Field garden) override;

    private:
        /**
         * @brief Display an error message.
         */
        void displayErrorMessage() const;
};