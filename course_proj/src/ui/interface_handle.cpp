#include "interface_handle.h"

#include "uv_texture_mapper.h"
#include "shape_material_linker.h"
#include "material.h"
#include "material_albedo.h"
#include "material_refraction_index.h"
#include "material_ambient_attraction.h"
#include "material_texture.h"
#include "material_scattering.h"

#include "lambert_difusion_builder.h"
#include "phong_specular_builder.h"
#include "specular_reflection_builder.h"
#include "specular_transmission_builder.h"
#include "dielectric_reflection_builder.h"
#include "conductor_reflection_builder.h"
#include "fresnel_transmission_builder.h"

#include "scattering_scale.h"
#include "scattering_refraction_index.h"
#include "scattering_phong_alpha.h"

#include "ambient_lighting.h"
#include "scene_active_projector.h"
#include "spherical_map.h"

#include "lighting.h"

#include "orthogonal_projector.h"
#include "pinhole_projector.h"
#include "thin_lens_projector.h"

#include "solid_texture.h"
#include "image_array_texture_builder.h"
#include "light_array_texture_builder.h"

std::shared_ptr<Scene> build_scene(handle_t &handle)
{
    static std::shared_ptr<TextureMapper> texture_mapper = std::make_shared<UVTexturueMapper>();
    static const Intensity<> white ({1, 1, 1});
    std::shared_ptr<Scene> out = std::make_shared<Scene>();

    meta_t &meta = handle.meta;
    std::list<object_t> &objects = handle.objects;
    std::list<material_t> &materials = handle.materials;
    std::map<material_t *, std::shared_ptr<Material>> material_map;
    cache_t &cache = handle.cache;

    for (material_t &material : materials)
    {
        std::shared_ptr<Material> mat = std::make_shared<Material>();

        mat->add(std::make_shared<MaterialAlbedo>(material.albedo * white));
        mat->add(std::make_shared<MaterialRefractionIndex>(material.ri, material.albedo * white));
        mat->add(std::make_shared<MaterialAmbientAttraction>(material.ambient_attraction * white));

        std::shared_ptr<Texture<Intensity<>>> texture = nullptr;

        if (FILE_TEXTURE == material.texture.type && "" != material.texture.texture_name)
            texture = cache.textures[material.texture.texture_name];
        if (COLOR_TEXTURE == material.texture.type)
            texture = std::make_shared<SolidTexture<Intensity<>>>(material.texture.color);

        mat->add(std::make_shared<MaterialTexture>(texture, texture_mapper));

        std::list<MaterialScattering::BuilderInfo> builders;

        for (scattering_t &scattering : material.scattering)
        {
            std::shared_ptr<ScatteringInfo> info = std::make_shared<ScatteringInfo>();
            std::shared_ptr<ScatteringBuilder> builder = nullptr;

            info->setProperty(std::make_shared<ScatteringScale>(scattering.scale * white));

            switch (scattering.type)
            {
                case (LAMBERT_DIFUSION):
                    builder = std::make_shared<LambertDifusionBuilder>();
                    break;
                case (PHONG_SPECULAR):
                    builder = std::make_shared<PhongSpecularBuilder>();
                    info->setProperty(std::make_shared<ScatteringPhongAlpha>(scattering.phong_alpgha));
                    break;
                case (SPECULAR_REFLECTION):
                    builder = std::make_shared<SpecularReflectionBuilder>();
                    break;
                case (SPECULAR_TRANSMISSION):
                    builder = std::make_shared<SpecularTransmissionBuilder>();
                    break;
                case (DIELECTRIC_REFLECTION):
                    builder = std::make_shared<DielectricReflectionBuilder>();
                    break;
                case (CONDUCTOR_REFLECTION):
                    builder = std::make_shared<ConductorReflectionBuilder>();
                    break;
                case (FRESNEL_TRANSMISSION):
                    builder = std::make_shared<FresnelTransmissionBuilder>();
                    break;
            }

            builders.push_back({builder, info});
        }

        mat->add(std::make_shared<MaterialScattering>(builders));

        material_map[&material] = mat;
    }

    for (object_t &object : objects)
        out->add(object.shape);

    std::shared_ptr<const Projector> projector = nullptr;
    object_t &active_projector = *meta.projector;

    switch (active_projector.projector.type)
    {
        case (ORTHOGONAL_PROJECTOR):
            projector = std::make_shared<const OrthogonalProjector>(active_projector.shape.get());
            break;
        case (PINHOLE_PROJECTOR):
            projector = std::make_shared<const PinholeProjector>(active_projector.shape.get(), active_projector.projector.offset);
            break;
        case (THIN_LENS_PROJECTOR):
            projector = std::make_shared<const ThinLensProjector>(active_projector.shape.get(), *out, active_projector.projector.focus,
                                                                  active_projector.projector.aperture, active_projector.projector.autofocus);
    }

    out->addProperty(std::make_shared<SceneActiveProjector>(projector));

    if (meta.env_map.set && "" != meta.env_map.texture_name)
        out->addProperty(std::make_shared<SphericalMap>(cache.textures[meta.env_map.texture_name],
                                                        meta.env_map_size));

    if (meta.ambient.set)
        out->addProperty(std::make_shared<AmbientLighting>(meta.ambient.power * meta.ambient.color));

    for (object_t &object : objects)
    {
        if (object.lighting.set)
            out->addProperty(std::make_shared<Lighting>(object.shape.get(), object.lighting.power * object.lighting.color));
        if (object.material)
            out->addProperty(std::make_shared<ShapeMaterialLinker>(object.shape.get(), material_map[object.material]));
    }

    return out;
}

void refresh_cache(handle_t &handle)
{
    cache_t &cache = handle.cache;
    meta_t &meta = handle.meta;

    if (meta.env_map.set && "" != meta.env_map.texture_name
        && cache.textures.find(meta.env_map.texture_name) == cache.textures.end())
        cache.textures[meta.env_map.texture_name] = LightArrayTextureBuilder<Intensity<>>(meta.env_map.texture_name.c_str()).build();

    for (material_t &mat : handle.materials)
        if (mat.texture.set && FILE_TEXTURE == mat.texture.type && "" != mat.texture.texture_name
            && cache.textures.find(mat.texture.texture_name) == cache.textures.end())
            cache.textures[mat.texture.texture_name] = ImageArrayTextureBuilder<Intensity<>>(mat.texture.texture_name.c_str()).build();
}

