#pragma once

#include "../Instruction.hh"

/**
 * @brief A negation instruction.
 */
class Not: public Instruction {
    private:
        std::shared_ptr<Instruction> _cond;

    public:
        /**
         * @brief Construct a new Not instruction.
         * 
         * @param cond The condition to negate.
         */
        Not(std::shared_ptr<Instruction> cond);
        Not(Not const &) = default;
        ~Not() override = default;

        bool execute(Field garden) override;
};