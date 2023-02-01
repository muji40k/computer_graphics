#include <intensity.h>

template <size_t nDim>
void Intensity<nDim>::trim(void)
{
    for (size_t i = 0; nDim > i; i++)
        if (0 > (*this)[i])
            (*this)[i] = 0;
}

template <size_t nDim>
Intensity<nDim> Intensity<nDim>::operator + (const Intensity<nDim> &intensity) const
{
    Intensity<nDim> out (*this);
    out += intensity;

    return out;
}

template <size_t nDim>
Intensity<nDim> Intensity<nDim>::operator - (const Intensity<nDim> &intensity) const
{
    Intensity<nDim> out (*this);
    out -= intensity;

    return out;
}

template <size_t nDim>
template <typename Other>
Intensity<nDim> Intensity<nDim>::operator * (const Other &value) const
{
    Intensity<nDim> out (*this);
    out *= value;

    return out;
}

template <size_t nDim>
template <typename Other>
Intensity<nDim> Intensity<nDim>::operator / (const Other &value) const
{
    Intensity<nDim> out (*this);
    out /= value;

    return out;
}

template <size_t nDim>
Intensity<nDim> &Intensity<nDim>::operator += (const Intensity<nDim> &intensity)
{
    static_cast<Point<double, nDim> &>(*this) += intensity;
    this->trim();

    return *this;
}

template <size_t nDim>
Intensity<nDim> &Intensity<nDim>::operator -= (const Intensity<nDim> &intensity)
{
    static_cast<Point<double, nDim> &>(*this) -= intensity;
    this->trim();

    return *this;
}

template <size_t nDim>
template <typename Other>
Intensity<nDim> &Intensity<nDim>::operator *= (const Other &value)
{
    static_cast<Point<double, nDim> &>(*this) *= value;
    this->trim();

    return *this;
}

template <size_t nDim>
template <typename Other>
Intensity<nDim> &Intensity<nDim>::operator /= (const Other &value)
{
    static_cast<Point<double, nDim> &>(*this) /= value;
    this->trim();

    return *this;
}

template <size_t nDim>
void Intensity<nDim>::apply(const Transform<double, nDim> &transform)
{
    this->Point<double, nDim>::apply(transform);
    this->trim();
}

template <size_t nDim>
void Intensity<nDim>::undo(const Transform<double, nDim> &transform)
{
    this->Point<double, nDim>::undo(transform);
    this->trim();
}

