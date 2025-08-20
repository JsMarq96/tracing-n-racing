#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

namespace Intersection {
    struct sRay;
};

struct sCamera {
    glm::vec3 position = {};

    float aspect_ratio;

    glm::mat4x4 view_mat;
    glm::mat4x4 proj_mat;
    glm::mat4x4 view_proj_mat;
    glm::mat4x4 inv_view_proj_mat;
};

void Camera_config_view(sCamera *cam, const glm::vec3 position, const glm::vec3 look_at, const glm::vec3 up);
void Camera_config_projection(sCamera *cam, const float rad_FOV, const float aspect_ratio, const float near, const float far);
glm::mat4 Camera_get_view_projection(sCamera *cam);
void Camera_create_camera_rays(sCamera *cam, const uint32_t width_resolution, const uint32_t max_ray_count, Intersection::sRay *ray_list, uint32_t *ray_count);
