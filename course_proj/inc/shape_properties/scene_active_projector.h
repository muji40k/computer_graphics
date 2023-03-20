#ifndef _SCENE_ACTIVE_PROJECTOR_H_
#define _SCENE_ACTIVE_PROJECTOR_H_

#include <memory>

#include "common_property.h"
#include "projector.h"

class SceneActiveProjector : public CommonProperty
{
    public:
        static const size_t ATTRI = 4;
        static const Attribute &ATTRIBUTE(void);

    public:
        SceneActiveProjector(const std::shared_ptr<const Projector> &projector);
        virtual ~SceneActiveProjector(void) override;

        const Projector &getProjector(void) const;
        void setProjector(const std::shared_ptr<const Projector> &projector);

        virtual const Attribute &getAttribute(void) const override;

    private:
        std::shared_ptr<const Projector> projector;
};

#endif

