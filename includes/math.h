#ifndef MATH_H
#define MATH_H

/// @brief Clamp the value between minimal et maximal values
/// @param value Actual value
/// @param min Minimal value of the actual value
/// @param max Maximal value of the actual value
/// @return Return clamped valued
int clamp(int value, int min , int max) {
    if (value > max)
    {
        return max;
    }

    if (value < min)
    {
        return min;
    }

    return value;
}

#endif


