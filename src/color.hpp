// #pragma once
// #include "vector.hpp"
// #include <SFML/Graphics.hpp>

// class Color : public Vector
// {
// public:
//     explicit Color(double R = 0, double G = 0, double B = 0) : Vector(R, G, B) {}
//     Color(const Vector vec) : Vector(vec) {}
//     Color(const sf::Color color) : Vector(color.r, color.g, color.b) {}

//     Color& operator*=(const Color& right)
//     {
//         double R = getX();
//         double G = getX();
//         double B = getX();

//         R *= right.getX();
//         G *= right.getY();
//         B *= right.getZ();

//         R /= 255;
//         G /= 255;
//         B /= 255;

//         setX(R);
//         setY(G);
//         setZ(B);

//         return *this;
//     }

//     Color operator*(const Color& right)
//     {
//         Color result = *this;
//         result *= right;
//         return result;
//     }

//     operator sf::Color() { return sf::Color(getX(), getY(), getZ()); }
// };
