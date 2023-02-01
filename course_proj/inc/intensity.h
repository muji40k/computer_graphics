#ifndef _COLOR_H_
#define _COLOR_H_

#include "point.h"

#include <cstdlib>

template <size_t nDim = 3>
class Intensity : public Point<double, nDim>
{
    private:
        void trim(void);

    public:
        Intensity(void) : Point<double, nDim>() {};
        template <size_t oDim = nDim>
        Intensity(const Intensity<oDim> &intensity) : Point<double, nDim>(intensity) {}
        explicit Intensity(const std::initializer_list<double> &intensity) : Point<double, nDim>(intensity) {};

        Intensity<nDim> operator + (const Intensity<nDim> &intensity) const;
        Intensity<nDim> operator - (const Intensity<nDim> &intensity) const;
        template <typename Other>
        Intensity<nDim> operator * (const Other &value) const;
        template <typename Other>
        Intensity<nDim> operator / (const Other &value) const;

        Intensity<nDim> &operator += (const Intensity<nDim> &intensity);
        Intensity<nDim> &operator -= (const Intensity<nDim> &intensity);
        template <typename Other>
        Intensity<nDim> &operator *= (const Other &value);
        template <typename Other>
        Intensity<nDim> &operator /= (const Other &value);

        virtual void apply(const Transform<double, nDim> &transform) override;
        virtual void undo(const Transform<double, nDim> &transform) override;
};

#include "intensity.hpp"

#endif

