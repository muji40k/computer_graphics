#include "test_tracer.h"

#include <stack>

#include "simple_scene_tracer.h"
#include "direct_light_tracer.h"

#include "lighting.h"

#include "shape_material_linker.h"
#include "material.h"
#include "material_texture.h"
#include "material_scattering.h"
#include "material_albedo.h"
#include "material_refraction_index.h"
#include "material_ambient_attraction.h"

#include "ambient_lighting.h"

#include "environment_map.h"

#include "scattering_unit.h"
#include "tracing_unit.h"

#include "scattering_scale.h"
#include "scattering_intersection.h"
#include "scattering_refraction_index.h"
#include "scattering_albedo.h"
#include "scattering_base_function.h"
#include "scattering_phong_alpha.h"

#include "scaled_scattering_builder.h"
#include "lambert_difusion_builder.h"
#include "phong_specular_builder.h"
#include "specular_reflection_builder.h"
#include "specular_transmission_builder.h"

#include "tools.h"

// DEFAULTS
#define MAX_DEPTH 4

static bool init = false;

// Material

// texture
#include "solid_texture.h"
#include "uv_texture_mapper.h"
static std::shared_ptr<Texture<Intensity<>>> default_texture \
    = std::make_shared<SolidTexture<Intensity<>>>(Intensity<>({1, 1, 1}));
static std::shared_ptr<TextureMapper> default_texture_mapper \
    = std::make_shared<UVTexturueMapper>();

// scattering
static std::list<MaterialScattering::BuilderInfo> default_scattering;


// scattering
static Intensity<> default_ambient_attraction ({1, 1, 1});

// End Material

// END DEFAULTS

typedef struct
{
    std::shared_ptr<Texture<Intensity<>>> texture;
    std::shared_ptr<TextureMapper> mapper;
    std::list<MaterialScattering::BuilderInfo> scattering;
    Intensity<> albedo;
    std::complex<double> refraction_index;
    Intensity<> ralbedo;
    std::shared_ptr<const Lighting> lighting;
    Intensity<> ambient_attraction;
} unit_arg_t;

typedef struct
{
    std::shared_ptr<const AmbientLighting> ambient;
    std::shared_ptr<const EnvironmentMap> map;
} common_prop_t;

typedef struct
{
    std::shared_ptr<TracingUnit> unit;
    TracingUnit::const_iterator iter;
    bool start;
} tracing_unit_t;

static void init_default(void);

static common_prop_t get_common_prop(const Scene &scene);
static unit_arg_t get_unit_arg(const Scene &scene, const Intersection &inter);
static void parse_material(const ShapeMaterialLinker &linker, unit_arg_t &arg);
static void init_unit_arg(const common_prop_t &common, const Scene &scene,
                          tracing_unit_t &current, const SceneTracer &tracer,
                          const LightTracer &ltracer);

TestTracer::TestTracer(void)
{
    init_default();
}

TestTracer::~TestTracer(void) {}

Intensity<> TestTracer::trace(const Scene &scene, const Ray3<double> &ray) const
{
    SimpleSceneTracer stracer;
    DirectLightTracer ltracer (scene);

    common_prop_t common = get_common_prop(scene);
    ScatteringUnit head (scene,
                         std::list<std::shared_ptr<const ScatteringFunction>>(),
                         ray);
    head.scatter(stracer);

    std::stack<tracing_unit_t> stack;

    for (std::shared_ptr<TracingUnit> &unit : head)
        stack.push({unit, {}, false});

    while (0 != stack.size())
    {
        tracing_unit_t &current = stack.top();

        if (!current.start)
            init_unit_arg(common, scene, current, stracer, ltracer);
        else
            current.unit->accumulate(current.iter++);

        if (current.unit->isTerminate() || current.unit->end() == current.iter)
            stack.pop();
        else if (MAX_DEPTH > stack.size())
            for (std::shared_ptr<TracingUnit> &unit : **current.iter)
                stack.push({unit, {}, false});
    }

    Intensity<> out;

    for (std::shared_ptr<TracingUnit> &unit : head)
        out += unit->getBaseIntensity() * unit->getEmission();

    return out;
}

static void init_default(void)
{
    if (init)
        return;

    std::shared_ptr<ScatteringInfo> tmp_info = std::make_shared<ScatteringInfo>();
    tmp_info->setProperty(std::make_shared<ScatteringScale>(0.7 * Intensity({1, 1, 1})));
    default_scattering.push_back({std::make_shared<LambertDifusionBuilder>(), tmp_info});

    tmp_info = std::make_shared<ScatteringInfo>();
    tmp_info->setProperty(std::make_shared<ScatteringScale>(0.3 * Intensity({1, 1, 1})))
             .setProperty(std::make_shared<ScatteringPhongAlpha>(3));
    default_scattering.push_back({std::make_shared<PhongSpecularBuilder>(), tmp_info});

    init = true;
}

static common_prop_t get_common_prop(const Scene &scene)
{
    common_prop_t out = {nullptr, nullptr};

    std::list<std::shared_ptr<const ShapeProperty>> lst = scene.getProperties(AmbientLighting::ATTRIBUTE());

    if (0 != lst.size())
        out.ambient = std::static_pointer_cast<const AmbientLighting>(lst.front());

    lst = scene.getProperties(EnvironmentMap::ATTRIBUTE());

    if (0 != lst.size())
        out.map = std::static_pointer_cast<const EnvironmentMap>(lst.front());

    return out;
}

static unit_arg_t get_unit_arg(const Scene &scene, const Intersection &inter)
{
    unit_arg_t out = {nullptr, nullptr, {}, {0, 0, 0}, {0, 0}, {0, 0, 0}, nullptr,
                      default_ambient_attraction};

    auto lst = scene.getProperties(inter.getShape());

    for (auto prop : lst)
    {
        if (ShapeMaterialLinker::ATTRIBUTE() <= prop->getAttribute())
            parse_material(*std::static_pointer_cast<const ShapeMaterialLinker>(prop),
                           out);
        else if (Lighting::ATTRIBUTE() <= prop->getAttribute())
            out.lighting = std::static_pointer_cast<const Lighting>(prop);
    }

    return out;
}

static void parse_material(const ShapeMaterialLinker &linker, unit_arg_t &arg)
{
    const Material &material = linker.getMaterial();

    for (auto prop : material)
    {
        if (MaterialTexture::ATTRIBUTE() <= prop->getAttribute())
        {
            std::shared_ptr<MaterialTexture> tmp = std::static_pointer_cast<MaterialTexture>(prop);
            arg.texture = tmp->getTexture();
            arg.mapper = tmp->getMapper();
        }
        else if (MaterialScattering::ATTRIBUTE() <= prop->getAttribute())
        {
            std::shared_ptr<MaterialScattering> tmp = std::static_pointer_cast<MaterialScattering>(prop);
            arg.scattering = tmp->getBuilders();
        }
        else if (MaterialAlbedo::ATTRIBUTE() <= prop->getAttribute())
        {
            std::shared_ptr<MaterialAlbedo> tmp = std::static_pointer_cast<MaterialAlbedo>(prop);
            arg.albedo = tmp->getValue();
        }
        else if (MaterialRefractionIndex::ATTRIBUTE() <= prop->getAttribute())
        {
            std::shared_ptr<MaterialRefractionIndex> tmp = std::static_pointer_cast<MaterialRefractionIndex>(prop);
            arg.refraction_index = tmp->getValue();
            arg.ralbedo = tmp->getAlbedo();
        }
        else if (MaterialAmbientAttraction::ATTRIBUTE() <= prop->getAttribute())
        {
            std::shared_ptr<MaterialAmbientAttraction> tmp = std::static_pointer_cast<MaterialAmbientAttraction>(prop);
            arg.ambient_attraction = tmp->getValue();
        }
    }
}

static void init_unit_arg(const common_prop_t &common, const Scene &scene,
                          tracing_unit_t &current, const SceneTracer &tracer,
                          const LightTracer &ltracer)
{
    current.start = true;

    if (current.unit->isTerminate())
    {
        Intensity<> out;

        if (nullptr != common.map)
        {
            Ray3<double> flip = current.unit->getInRay();
            flip.setDirection(-flip.getDirection());
            out = common.map->map(flip);
        }

        current.unit->setBaseIntensity(out);

        return;
    }

    unit_arg_t props = get_unit_arg(scene, current.unit->getIntersection());

    if (nullptr != props.lighting)
    {
        current.unit->setBaseIntensity(Intensity<>({1, 1, 1}));
        current.unit->accumulate(props.lighting->getEmission());
        current.unit->makeTerminate();

        return;
    }

    std::list<MaterialScattering::BuilderInfo> builders = default_scattering;

    std::list<std::shared_ptr<ScatteringFunction>> dif_func;
    std::list<std::shared_ptr<ScatteringFunction>> ref_func;
    std::list<std::shared_ptr<ScatteringFunction>> trans_func;
    std::shared_ptr<Texture<Intensity<>>> texture = default_texture;
    std::shared_ptr<TextureMapper> mapper = default_texture_mapper;

    if (nullptr != props.texture)
        texture = props.texture;

    if (nullptr != props.mapper)
        mapper = props.mapper;

    Point2<double> uv = mapper->map(current.unit->getIntersection());
    current.unit->setBaseIntensity(texture->getAt(uv));

    if (nullptr != common.ambient)
        current.unit->accumulate(props.ambient_attraction
                                 * common.ambient->getEmission());

    Point3<double> point = current.unit->getIntersection().getPoint();
    Normal3<double> norm = current.unit->getIntersection().getNormal();
    point.apply(current.unit->getIntersection().toGlobal());
    norm.apply(current.unit->getIntersection().toGlobal());

    if (0 != props.scattering.size())
        builders = props.scattering;

    for (auto item : builders)
    {
        const ScatteringBuilder &builder = *item.builder;

        if (PhongSpecularBuilder::ATTRIBUTE() <= builder.getAttribute())
        {
            ScatteringInfo info (*item.info);
            info.setProperty(std::make_shared<ScatteringIntersection>(current.unit->getIntersection()));
            dif_func.push_back(builder.build(info));
        }
        else if (LambertDifusionBuilder::ATTRIBUTE() <= builder.getAttribute())
            dif_func.push_back(builder.build(*item.info));
        else if (SpecularReflectionBuilder::ATTRIBUTE() <= builder.getAttribute())
            ref_func.push_back(builder.build(*item.info));
        else if (SpecularTransmissionBuilder::ATTRIBUTE() <= builder.getAttribute())
            trans_func.push_back(builder.build(*item.info));
    }

    if (0 != dif_func.size())
    {
        std::list<light_trace_t> trace = ltracer.trace(point);

        for (light_trace_t &t : trace)
        {
            t.intensity *= (t.direction & norm) / (t.direction.length() * norm.length());

            for (auto f : dif_func)
                current.unit->accumulate(t.intensity
                                         * f->apply(t.direction,
                                                    current.unit->getInVector()));
        }
    }

    bool rflag = 0 == ref_func.size() || !props.albedo,
         tflag = 0 == trans_func.size() || !props.ralbedo   \
                 || 0 > fabs(props.refraction_index.real()) \
                 || 0 < fabs(props.refraction_index.imag());

    if (rflag && tflag)
        current.unit->makeTerminate();
    else
    {
        std::list<std::shared_ptr<const ScatteringFunction>> tmp;
        std::shared_ptr<ScatteringUnit> sunit = nullptr;
        ScaledScatteringBuilder builder;

        if (!rflag)
        {
            tmp.clear();
            Vector3<double> ref = tools::get_reflection(norm,
                                                        current.unit->getInVector());

            for (auto f : ref_func)
            {
                ScatteringInfo info;
                info.setProperty(std::make_shared<ScatteringBaseFunction>(f))
                    .setProperty(std::make_shared<ScatteringScale>(props.albedo));
                tmp.push_back(builder.build(info));
            }

            sunit = std::make_shared<ScatteringUnit>(scene, tmp, Ray3<double>(point, ref));
            current.unit->add(sunit);
            sunit->scatter(tracer);
        }

        if (!tflag)
        {
            const double &n1 = current.unit->getOuterRefractionIndex().real();
            double n2 = props.refraction_index.real();

            if (0 > (norm & current.unit->getInVector()))
                n2 = 1;

            tools::transmission_res_t res = \
                tools::get_transmission(norm, current.unit->getInVector(),
                                        n1, n2);

            if (!res.valid)
                tflag = true;
            else
            {
                tmp.clear();

                for (auto f : trans_func)
                {
                    ScatteringInfo info;
                    info.setProperty(std::make_shared<ScatteringBaseFunction>(f))
                        .setProperty(std::make_shared<ScatteringScale>(props.ralbedo));
                    tmp.push_back(builder.build(info));
                }

                sunit = std::make_shared<ScatteringUnit>(scene, tmp, Ray3<double>(point, res.vector), n2);
                current.unit->add(sunit);
                sunit->scatter(tracer);
            }
        }

        if (rflag && tflag)
            current.unit->makeTerminate();
        else
            current.iter = current.unit->cbegin();
    }
}

