#pragma once

#include "Instruction.hh"

#include <list>
#include <string>
#include <memory>

class Function {
    private:
        std::list<std::unique_ptr<Instruction>> _instructions;

    public:
        Function() = default;
        Function(Function const &) = delete;
        ~Function() = default;

        /**
         * @brief Add an Instruction to this Function. 
         *
         * @param instruction The Instruction to add. 
         */
        void addInstruction(std::unique_ptr<Instruction> const & instruction);

        /**
         * @brief Execute the Function.
         * 
         * @param garden The garden to use as context.
         * @return 
         */
        bool execute(JardinRendering* const & garden) const;
};