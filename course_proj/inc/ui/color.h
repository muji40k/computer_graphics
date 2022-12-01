#ifndef _COLOR_H_
#define _COLOR_H_

#include <QColor>

class Color
{
    private:
        double _x = 0;
        double _y = 0;
        double _z = 0;

    private:
        void trim(void);
        double &operator [] (const size_t i);

    public:
        Color(const double x = 0, const double y = 0, const double z = 0);
        Color(const int r = 0, const int g = 0, const int b = 0);
        Color(const Color &color);

        double x(void) const;
        double y(void) const;
        double z(void) const;
        void setX(const double x);
        void setY(const double y);
        void setZ(const double z);

        int r(void) const;
        int g(void) const;
        int b(void) const;

        Color operator + (const Color &color) const;
        Color &operator += (const Color &color);
        Color operator - (const Color &color) const;
        Color &operator -= (const Color &color);
        Color operator * (const Color &color) const;
        Color &operator *= (const Color &color);
        Color operator * (const double value) const;
        Color &operator *= (const double value);
};


QColor toQColor(const Color &color);


#endif

