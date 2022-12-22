#pragma once

#include "Instruction.hh"

/**
 * @brief An instruction that makes a turtle goes forward.
 */
class Forward : public Instruction {
    private:
        /**
         * @brief The delta that will be applied to the actual position.
         */
        int _amount;
    
    public:
        /**
         * @brief Construct a new Forward instruction. 
         *
         * @param turtle The targeted turtle.
         * @param amount The delta that will be applied to the actual position.
         */
        explicit Forward(std::size_t turtle, int amount);
        Forward(Forward const &) = default;
        ~Forward() override = default;
        
        bool execute(Field garden) override;

    private:
        void displayErrorMessage() const;
};