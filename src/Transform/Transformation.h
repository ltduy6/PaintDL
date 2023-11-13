#pragma once

struct Transformation
{
    double translationX{0.0};
    double translationY{0.0};
    double rotationAngle{0.0};
    double scaleX{1.0};
    double scaleY{1.0};

    bool operator==(const Transformation &other) const
    {
        return translationX == other.translationX && translationY == other.translationY && rotationAngle == other.rotationAngle && scaleX == other.scaleX && scaleY == other.scaleY;
    }
};