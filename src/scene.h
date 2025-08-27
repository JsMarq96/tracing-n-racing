#pragma once

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>

#define MAX_SCENE_COUNT 1024u

namespace Intersection {
    struct sRay;
    struct sResult;
}

enum eShape : uint8_t {
    SHAPE_SPHERE = 0u,
    SHAPE_NONE
};

struct sTransform {
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};

struct sMaterial {
    glm::vec3 albedo;
    float roughness;
    float metalness;
};

struct sScene {
    uint32_t obj_count = 0u;
    eShape obj_shape[MAX_SCENE_COUNT];
    sTransform obj_transforms[MAX_SCENE_COUNT];
    sMaterial obj_metarial[MAX_SCENE_COUNT];
};

uint32_t Scene_Add_sphere(sScene *scene, const glm::vec3 position, const float radius, const sMaterial &mat);
void Scene_test_rays(sScene *scene, const uint32_t ray_count, const Intersection::sRay *ray_list, uint32_t *intersection_count, Intersection::sResult *intersection_results);
