#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

struct SystemCoord;

struct Point
{
    double x = 0;
    double y = 0;
    double z = 0;
};

class Vector
{
public:
    enum Thickness { thin, medium, bold };
private:
    double cx;
    double cy;
    double cz;
    double clen;

    Point capp_point       = Point{0, 0, 0};
    sf::VertexArray cline  = sf::VertexArray(sf::Lines, 2);
    sf::VertexArray carrow = sf::VertexArray(sf::LineStrip, 3);
    Thickness cthickness   = Thickness::thin;

    void fillVertexArray();
    void createLine();
    void createArrow();
    void moveFigure(int x, int y);
public:
    Vector(double x = 0, double y = 0, double z = 0) : cx(x),       cy(y),       cz(z),         clen(NAN) {}
    Vector(const Vector& init)                       : cx(init.cx), cy(init.cy), cz(init.cz),   clen(init.clen) {}
    Vector(double x, double y, double z, const SystemCoord& sys);

    double length();

    void setThickness(Thickness thickness) { cthickness = thickness; }
    void setAppPoint(const Point& app_point, const SystemCoord& sys_coord);
    void setAppPoint(const Point& app_point);
    void setColor(const sf::Color& color);

    void setX(double x) { cx = x; clen = NAN; }
    void setY(double y) { cy = y; clen = NAN; }
    void setZ(double z) { cz = z; clen = NAN; }

    void setX(double x, const SystemCoord& sys_coord);
    void setY(double y, const SystemCoord& sys_coord);
    void setZ(double z, const SystemCoord& sys_coord);

    double getX() const { return cx; }
    double getY() const { return cy; }
    double getZ() const { return cz; }

    Vector& operator+=(const Vector& rvec);
    Vector& operator-=(const Vector& rvec);
    Vector& operator/=(double number);
    Vector& operator*=(double number);

    Vector operator+(const Vector& rvec) const;
    Vector operator-(const Vector& rvec) const;
    Vector operator/(double number) const;
    Vector operator*(double number) const;

    int operator*(const Vector& rvec) const { return cx * rvec.cx + cy * rvec.cy + cz * rvec.cz; }

    Vector operator-() const { return Vector(-cx, -cy, -cz); }

    Vector normalize() { return Vector(cx / length(), cy / length(), cz / length()); }

    void draw(sf::RenderWindow& window);

    operator sf::Vector2f() const { return sf::Vector2f(cx, cy); }

    friend double cos(Vector& left, Vector& right) { return left * right / (left.length() * right.length()); }

    friend std::ostream& operator<<(std::ostream& out, const Vector& vec);
    friend std::istream& operator>>(std::istream& in, Vector& vec);
};

struct SystemCoord
{
    Vector cstart_point;
    Vector ce1;
    Vector ce2;
    Vector ce3;

    SystemCoord(const Vector& start_point, const Vector& e1, const Vector& e2, const Vector& e3) :
        cstart_point(start_point),
        ce1(e1),
        ce2(e2),
        ce3(e3)
        {}
};
