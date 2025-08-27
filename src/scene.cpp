#include "scene.h"

#include <cassert>
#include <glm/glm.hpp>

#include "utils.h"
#include "intersection/intersection_types.h"

bool ray_sphere_intersection(   const glm::vec3 sphere_origin,
                                const float raidus,
                                const Intersection::sRay ray,
                                float *intersection_t) {
    const glm::vec3 OC = ray.origin - sphere_origin;
    float t1, t2;

    if (!quadratic_solver(glm::dot(ray.direction, ray.direction),
                            2.0f * glm::dot(ray.direction, OC),
                            glm::dot(OC, OC) - raidus * raidus,
                            &t1, &t2)) {
        return false;
    }

    if (t1 < 0.0f) {
        *intersection_t = t2;
    } else if (t2 > 0.0f) {
        *intersection_t = t1;
    } else {
        return false;
    }

    return true;
}

void Scene_test_rays(   sScene *scene,
                        const uint32_t ray_count,
                        const Intersection::sRay *ray_list,
                        uint32_t *intersection_count,
                        Intersection::sResult *intersection_results) {
    uint32_t inters_count = 0u;

    // Compute intersections and add to collision list
    for(uint16_t obj_idx = 0u; obj_idx < scene->obj_count; obj_idx++) {
        sTransform *curr_transform = &scene->obj_transforms[obj_idx];
        const glm::vec3 sphere_origin = (glm::vec3) curr_transform->position;
        const float radius = 0.5f * glm::max(   curr_transform->scale[0],
                                                glm::max(   curr_transform->scale[1],
                                                            curr_transform->scale[2]));

        float ray_t = 0.0;
        for(uint32_t ray_idx = 0u; ray_idx < ray_count; ray_idx++) {
            if (ray_sphere_intersection(sphere_origin,
                                        radius,
                                        ray_list[ray_idx],
                                        &ray_t)) {
                intersection_results[inters_count].ray_idx = ray_idx;
                intersection_results[inters_count].ray_t = ray_t;
                intersection_results[inters_count].object_idx = obj_idx;
                inters_count++;
            }
        }
    }

    // Compute the other collision data (position and normal)
    for(uint32_t i = 0u; i < inters_count; i++) {
        Intersection::sResult &curr_result = intersection_results[i];
        const glm::vec3 col_point = curr_result.ray_t * (glm::vec3) ray_list[curr_result.ray_idx].origin;
        const glm::vec3 col_normal = glm::normalize((glm::vec3) scene->obj_transforms[curr_result.object_idx].position - col_point);

        curr_result.col_normal = col_normal;
        curr_result.col_point = col_point;
    }

    *intersection_count = inters_count;
}


uint32_t Scene_Add_sphere(  sScene *scene,
                            const glm::vec3 position,
                            const float radius,
                            const sMaterial &mat) {
    const uint32_t obj_idx = scene->obj_count;
    assert(obj_idx < MAX_SCENE_COUNT);

    scene->obj_shape[obj_idx] = SHAPE_SPHERE;
    scene->obj_metarial[obj_idx] = mat;
    scene->obj_transforms[obj_idx] = {  .position = position,
                                        .scale = glm::vec3(radius*2.0f)
                                    };

    return scene->obj_count++;
}
