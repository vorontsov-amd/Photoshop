#include "vector.hpp"

Vector::Vector(double x, double y, double z, const SystemCoord& sys) :
    cx(sys.ce1.cx * x + sys.ce2.cx * y + sys.ce3.cx * z + sys.cstart_point.cx),
    cy(sys.ce1.cy * x + sys.ce2.cy * y + sys.ce3.cy * z + sys.cstart_point.cy),
    cz(sys.ce1.cz * x + sys.ce2.cz * y + sys.ce3.cz * z + sys.cstart_point.cz),
    clen(NAN),
    capp_point{sys.cstart_point.cx, sys.cstart_point.cy, sys.cstart_point.cz}
    {}

double Vector::length() 
{ 
    if (std::isnan(clen))
    {
        clen = std::sqrt(cx * cx + cy * cy + cz * cz);
    }
    return clen;
}

void Vector::setX(double x, const SystemCoord& sys)
{
    cx = sys.ce1.cx * x + sys.ce2.cx * cy + sys.ce3.cx * cz + sys.cstart_point.cx;
    clen = NAN;
}

void Vector::setY(double y, const SystemCoord& sys)
{
    cy = sys.ce1.cy * cx + sys.ce2.cy * y + sys.ce3.cy * cz + sys.cstart_point.cy;
    clen = NAN;
}

void Vector::setZ(double z, const SystemCoord& sys)
{
    cz = sys.ce1.cz * cx + sys.ce2.cz * cy + sys.ce3.cz * z + sys.cstart_point.cz;
    clen = NAN;
}

Vector& Vector::operator+=(const Vector& rvec)
{
    cx += rvec.cx;
    cy += rvec.cy;
    cz += rvec.cz;
    clen = NAN;
    return *this;
}

Vector& Vector::operator-=(const Vector& rvec)
{
    cx -= rvec.cx;
    cy -= rvec.cy;
    cz -= rvec.cz;
    clen = NAN;
    return *this;
}

Vector& Vector::operator/=(double number)
{
    cx /= number;
    cy /= number;
    cz /= number;
    clen = NAN;
    return *this;
}

Vector& Vector::operator*=(double number)
{
    cx *= number;
    cy *= number;
    cz *= number;
    clen = NAN;
    return *this;
}

Vector Vector::operator+(const Vector& rvec) const
{
    Vector res = *this;
    res += rvec;
    return res;
}

Vector Vector::operator-(const Vector& rvec) const
{
    Vector res = *this;
    res -= rvec;
    return res;
}

Vector Vector::operator/(double number) const
{
    Vector res = *this;
    res /= number;
    return res;
}

Vector Vector::operator*(double number) const
{
    Vector res = *this;
    res *= number;
    return res;
}

std::ostream& operator<<(std::ostream& out, const Vector& vec)
{
    return out << "{ " << vec.cx << ", " << vec.cy << ", " << vec.cz << " }";
}

std::istream& operator>>(std::istream& in, Vector& vec)
{
    return in >> vec.cx >> vec.cy >> vec.cz;
}

void Vector::setAppPoint(const Point& app_point, const SystemCoord& sys)
{
    Vector to_app_point(app_point.x, app_point.y, app_point.z, sys);
    
    double x = getX() + to_app_point.getX() - capp_point.x;
    double y = getY() + to_app_point.getY() - capp_point.y;
    setX(x);
    setY(y);

    capp_point.x = to_app_point.getX();
    capp_point.y = to_app_point.getY();
}

void Vector::setAppPoint(const Point& app_point)
{
    double x = getX() + app_point.x - capp_point.x;
    double y = getY() + app_point.y - capp_point.y;
    setX(x);
    setY(y);

    capp_point.x = app_point.x;
    capp_point.y = app_point.y;
}

void Vector::setColor(const sf::Color& color) 
{
    cline[0].color    = color;
    cline[1].color    = color;
    carrow[0].color   = color;
    carrow[1].color   = color;
    carrow[2].color   = color;
}

void Vector::draw(sf::RenderWindow& window)
{
    if (getX() == capp_point.x && getY() == capp_point.y) return;

    fillVertexArray();

    for (int dy = -cthickness; dy <= cthickness; ++dy)
    {
        for (int dx = -cthickness; dx <= cthickness; ++dx)
        {
            moveFigure(dx, dy);
            window.draw(cline);
            window.draw(carrow);
            moveFigure(-dx, -dy);
        }
    }
}

void Vector::moveFigure(int dx, int dy)
{
    cline[0].position.x += dx;
    cline[0].position.y += dy;
    cline[1].position.x += dx;
    cline[1].position.y += dy;

    carrow[0].position.x += dx;
    carrow[0].position.y += dy;
    carrow[1].position.x += dx;
    carrow[1].position.y += dy;
    carrow[2].position.x += dx;
    carrow[2].position.y += dy;
}

void Vector::fillVertexArray()
{
    createLine();
    createArrow();
}

void Vector::createLine()
{
    cline[0].position = sf::Vector2f(capp_point.x, capp_point.y);
    cline[1].position = sf::Vector2f(getX(), getY());   
}

void Vector::createArrow()
{
    const double cos30 = std::cos(7 * M_PI / 6); 
    const double sin30 = std::sin(7 * M_PI / 6); 

    auto left_line  = Vector(cos30 * (getX() - capp_point.x) + sin30 * (getY() - capp_point.y),
                            -sin30 * (getX() - capp_point.x) + cos30 * (getY() - capp_point.y));
    left_line = left_line.normalize() * 10;

    auto right_line = Vector(cos30 * (getX() - capp_point.x) - sin30 * (getY() - capp_point.y),
                             sin30 * (getX() - capp_point.x) + cos30 * (getY() - capp_point.y));

    right_line = right_line.normalize() * 10;

    auto left_point_vec  = sf::Vector2f( left_line.getX() + getX(),  left_line.getY() + getY());
    auto right_point_vec = sf::Vector2f(right_line.getX() + getX(), right_line.getY() + getY());
    
    carrow[0].position = left_point_vec;
    carrow[1].position = cline[1].position;
    carrow[2].position = right_point_vec;
}
