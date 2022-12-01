#include "color.h"

double trim_color(const double x)
{
    double res = x;

    if (1 < x)
        res = 1;
    else if (0 > x)
        res = 0;

    return res;
}

void Color::trim(void)
{
    for (size_t i = 0; 3 > i; i++)
        (*this)[i] = trim_color((*this)[i]);
}

double &Color::operator [] (const size_t i)
{
    size_t j = i % 3;

    if (0 == j)
        return this->_x;

    if (1 == j)
        return this->_y;

    return this->_z;
}

Color::Color(const double x, const double y, const double z)
    : _x(x), _y(y), _z(z)
{
    this->trim();
}

Color::Color(const int r, const int g, const int b)
{
    this->_x = 0.4124564 * r + 0.3575761 * g + 0.1804375 * b;
    this->_y = 0.2126729 * r + 0.7151522 * g + 0.0721750 * b;
    this->_z = 0.0193339 * r + 0.1191920 * g + 0.9503041 * b;
    this->trim();
}

Color::Color(const Color &color)
{
    this->_x = color._x;
    this->_y = color._y;
    this->_z = color._z;
    this->trim();
}

double Color::x(void) const
{
    return this->_x;
}

double Color::y(void) const
{
    return this->_y;
}

double Color::z(void) const
{
    return this->_z;
}

void Color::setX(const double x)
{
    this->_x = x;
    this->trim();
}

void Color::setY(const double y)
{
    this->_y = y;
    this->trim();
}

void Color::setZ(const double z)
{
    this->_z = z;
    this->trim();
}

int Color::r(void) const
{
    return 3.2404542 * this->_x - 1.5371385 * this->_y - 0.4985314 * this->_z;
}

int Color::g(void) const
{
   return -0.9692660 * this->_x + 1.8760108 * this->_y + 0.0415560 * this->_z;
}

int Color::b(void) const
{
    return 0.0556434 * this->_x - 0.2040259 * this->_y + 1.0572252 * this->_z;
}

Color Color::operator + (const Color &color) const
{
    Color out (*this);

    return out += color;
}

Color &Color::operator += (const Color &color)
{
    this->_x += color._x;
    this->_y += color._y;
    this->_z += color._z;
    this->trim();

    return *this;
}

Color Color::operator - (const Color &color) const
{
    Color out (*this);

    return out -= color;
}

Color &Color::operator -= (const Color &color)
{
    this->_x -= color._x;
    this->_y -= color._y;
    this->_z -= color._z;
    this->trim();

    return *this;
}

Color Color::operator * (const Color &color) const
{
    Color out (*this);

    return out *= color;
}

Color &Color::operator *= (const Color &color)
{
    this->_x *= color._x;
    this->_y *= color._y;
    this->_z *= color._z;
    this->trim();

    return *this;
}

Color Color::operator * (const double value) const
{
    Color out (*this);

    return out *= value;
}

Color &Color::operator *= (const double value)
{
    this->_x *= value;
    this->_y *= value;
    this->_z *= value;
    this->trim();

    return *this;
}

QColor toQColor(const Color &color)
{
    QColor out;
    out.setRgb(color.r(), color.g(), color.b());

    return out;
}

