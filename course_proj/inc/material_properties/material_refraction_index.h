#ifndef _MATERIAL_REFRACTION_INDEX_H_
#define _MATERIAL_REFRACTION_INDEX_H_

#include <memory>
#include <complex>

#include "material_property.h"
#include "intensity.h"

class MaterialRefractionIndex : public MaterialProperty
{
    public:
        static const size_t ATTRI = 4;
        static const Attribute &ATTRIBUTE(void);

    public:
        MaterialRefractionIndex(const std::complex<double> &n,
                                const Intensity<> &albedo);
        virtual ~MaterialRefractionIndex(void) override;
        virtual const Attribute &getAttribute(void) const override;

        const std::complex<double> &getValue(void);
        const Intensity<> &getAlbedo(void);

    private:
        std::shared_ptr<std::complex<double>> n;
        std::shared_ptr<Intensity<>> albedo;
};

#endif

