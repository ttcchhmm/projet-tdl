#pragma once

#include "Instruction.hh"

#include <string>

/**
 * @brief The zone of the turtle affected by the color change.
 */
enum class ColorZone {
    /**
     * @brief The shell of the turtle.
     */
    SHELL,

    /**
     * @brief The pattern of the turtle.
     */
    PATTERN
};

/**
 * @brief An instruction that change the color of a turtle.
 */
class Color: public Instruction {
    private:
        /**
         * @brief The targeted zone of the turtle.
         */
        ColorZone _zone;

        /**
         * @brief The color, in hexadecimal.
         */
        std::string _colorHexa;

    public:
        /**
         * @brief Construct a new Color instance.
         * 
         * @param turtle The targeted turtle.
         * @param zone The targeted zone of the turtle.
         * @param colorHexa The color in hexadecimal (without the '#' at the start).
         */
        Color(std::size_t turtle, ColorZone const & zone, std::string const & colorHexa);
        Color(Color const &) = default;
        ~Color() override = default;

        bool execute(Field garden) override;
};