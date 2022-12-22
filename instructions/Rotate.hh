#pragma once

#include "Instruction.hh"
#include "directions.hh"

/**
 * @brief An instruction that rotates a turtle.
 */
class Rotate : public Instruction {
    private:
        /**
         * @brief The direction used to rotate.
         */
        directions _dir;

        /**
         * @brief The number of repetitions.
         */
        unsigned int _amount;

    public:
        /**
         * @brief Construct a new Rotate instruction. 
         *
         * @param turtle The turtle to target.
         * @param dir The direction used to rotate.
         * @param amount The number of repetitions.
         */
        explicit Rotate(std::size_t turtle, directions dir, unsigned int amount);
        Rotate(Rotate const &) = default;
        ~Rotate() override = default;

        bool execute(JardinRendering* const & garden) override;
};