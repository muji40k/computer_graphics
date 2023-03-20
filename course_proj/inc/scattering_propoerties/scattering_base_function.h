#ifndef _SCATTERING_BASE_FUNCTION_H_
#define _SCATTERING_BASE_FUNCTION_H_

#include "scattering_property.h"

#include "scattering_function.h"

class ScatteringBaseFunction : public ScatteringProperty
{
    public:
        static const size_t ATTRI = 5;
        static const Attribute &ATTRIBUTE(void);

    public:
        ScatteringBaseFunction(const std::shared_ptr<ScatteringFunction> &function);
        virtual ~ScatteringBaseFunction(void) override;
        const std::shared_ptr<ScatteringFunction> &getBaseFunction(void);
        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<ScatteringFunction> function;

};

#endif

