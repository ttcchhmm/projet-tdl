#pragma once

#include "Instruction.hh"
#include "Function.hh"

#include <memory>

/**
 * @brief Represent a function call.
 */
class FunctionCall: public Instruction {
    private:
        std::shared_ptr<Function> _function;
        std::shared_ptr<std::vector<double>> _args;

    public:
        /**
         * @brief Construct a new FunctionCall.
         * 
         * @param function The function to call.
         * @param args The arguments.
         */
        FunctionCall(std::shared_ptr<Function> function, std::shared_ptr<std::vector<double>> const & args);
        FunctionCall(FunctionCall const &) = default;
        ~FunctionCall() override = default;

        bool execute(JardinRendering* const & garden) override;
};