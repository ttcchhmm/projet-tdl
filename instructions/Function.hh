#pragma once

#include "../Utils.hh"
#include "Instruction.hh"

#include <string>
#include <memory>

class Function {
    private:
        InstructionList _instructions;

    public:
        Function() = default;
        Function(Function const &) = delete;
        ~Function() = default;

        /**
         * @brief Add an Instruction to this Function. 
         *
         * @param instruction The Instruction to add. 
         */
        void addInstruction(std::shared_ptr<Instruction> const & instruction);

        /**
         * @brief Execute the Function.
         * 
         * @param garden The garden to use as context.
         * @return 
         */
        bool execute(Field garden) const;
};