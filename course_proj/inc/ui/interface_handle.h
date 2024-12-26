#ifndef _INTERFACE_HANDLE_H_
#define _INTERFACE_HANDLE_H_

#include <memory>
#include <list>
#include <map>
#include <complex>

#include "scene.h"
#include "shape.h"
#include "intensity.h"
#include "texture.h"

// SCENE HANDLE

typedef enum
{
    LAMBERT_DIFUSION,
    PHONG_SPECULAR,
    SPECULAR_REFLECTION,
    SPECULAR_TRANSMISSION,
    DIELECTRIC_REFLECTION,
    CONDUCTOR_REFLECTION,
    FRESNEL_TRANSMISSION
} scattering_type_t;

typedef struct
{
    std::string name;

    scattering_type_t type;
    double scale;

    double phong_alpgha;
} scattering_t;

typedef enum
{
    COLOR_TEXTURE,
    FILE_TEXTURE
} texture_type_t;

typedef struct
{
    bool set;
    texture_type_t type;
    std::string texture_name;
    Intensity<> color;
} texture_t;

typedef struct
{
    std::string name;
    std::list<scattering_t> scattering;
    double albedo;
    std::complex<double> ri;
    double ambient_attraction;
    texture_t texture;
} material_t;

typedef enum
{
    ORTHOGONAL_PROJECTOR,
    PINHOLE_PROJECTOR,
    THIN_LENS_PROJECTOR
} projector_type_t;

typedef struct
{
    bool set;
    projector_type_t type;
    double width;

    double offset;

    double aperture;
    bool autofocus;
    double focus;
} projector_t;

typedef struct
{
    bool set;
    double power;
    Intensity<> color;
} lighting_t;

typedef struct
{
    std::string name;
    std::shared_ptr<Shape> shape;

    material_t *material;
    projector_t projector;
    lighting_t lighting;
} object_t;

typedef struct
{
    std::map<std::string, std::shared_ptr<Texture<Intensity<>>>> textures;
} cache_t;

typedef struct
{
    object_t *projector;
    lighting_t ambient;
    texture_t env_map;
    double env_map_size;
} meta_t;

typedef struct
{
    meta_t meta;
    std::list<object_t> objects;
    std::list<material_t> materials;
    cache_t cache;
} handle_t;

// RENDER PREFERENCES

typedef struct
{
    int resolution;
    int threads;
} viewport_t;

typedef enum
{
    DEST_SCREEN,
    DEST_FILE
} destination_t;

typedef struct
{
    destination_t destination;
    std::string filename;
    size_t width;
    size_t height;
    size_t camera_samples;
    size_t light_samples;
    size_t max_depth;
    size_t threads;
} complete_t;

typedef enum
{
    VIEWPORT,
    COMPLETE
} render_type_t;

typedef struct
{
    render_type_t type;
    viewport_t viewport;
    complete_t complete;
} render_pref_t;

std::shared_ptr<Scene> build_scene(handle_t &handle);

void refresh_cache(handle_t &handle);

#endif

