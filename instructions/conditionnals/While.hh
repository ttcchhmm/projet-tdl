#pragma once

#include "../Instruction.hh"

/**
 * @brief The 'while' loop.
 */
class While: public Instruction {
    private:
        /**
         * @brief The condition.
         */
        std::shared_ptr<Instruction> _cond;

        /**
         * @brief The instructions to run.
         */
        std::list<std::shared_ptr<Instruction>> _instructions;

    public:
        /**
         * @brief Construct a new While instruction.
         * @param cond The condition.
         * @param instructions The instructions if the condition is true.
         */
        While(std::shared_ptr<Instruction> cond, std::list<std::shared_ptr<Instruction>> instructions);
        While(While const &) = default;
        ~While() override = default;

        bool execute(JardinRendering* const & garden) override;
};