#include "camera.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

#include "intersection/intersection_types.h"

void Camera_config_view(sCamera *cam,
                        const glm::vec3 position,
                        const glm::vec3 look_at,
                        const glm::vec3 up)  {
    cam->position = position;
    cam->view_mat = glm::lookAt(position,
                                look_at,
                                up  );
    cam->view_proj_mat = cam->proj_mat * cam->view_mat;
    cam->inv_view_proj_mat = glm::inverse(cam->view_proj_mat);
}
void Camera_config_projection(  sCamera *cam,
                                const float rad_FOV,
                                const float aspect_ratio,
                                const float near,
                                const float far) {
    cam->proj_mat = glm::perspective(rad_FOV, aspect_ratio, near, far);
    cam->proj_mat[1][1] *= -1.0f;

    cam->view_proj_mat = cam->proj_mat * cam->view_mat;
    cam->inv_view_proj_mat = glm::inverse(cam->view_proj_mat);
    cam->aspect_ratio = aspect_ratio;
}

glm::mat4 Camera_get_view_projection(sCamera *cam) {
    return cam->view_proj_mat;
}

#include <cstdio>
void Camera_create_camera_rays( sCamera *cam,
                                const uint32_t width_resolution,
                                const uint32_t max_ray_count,
                                Intersection::sRay *ray_list,
                                uint32_t *ray_count) {
    const uint32_t height_resolution = (uint32_t) (width_resolution / cam->aspect_ratio);

    glm::vec2 screen_res = glm::vec2(width_resolution, height_resolution);

    assert((screen_res.x * screen_res.y) <= max_ray_count);

    uint32_t ray_idx = 0u;
    for(uint32_t x = 0u; x < width_resolution; x++) {
        for(uint32_t y = 0u; y < height_resolution; y++) {
            // Compute NDC coordinates from the pixel position, and the convert those to wordl coord
            // all the rays are in word position
            glm::vec4 nd_coords = glm::vec4((x / screen_res.x) * 2.0f - 1.0f, (y / screen_res.y) * 2.0f - 1.0f, -1.0f, 1.0f);
            glm::vec4 world_coords = cam->inv_view_proj_mat * nd_coords;
            world_coords /= world_coords.w;

            ray_list[ray_idx++] = {
                .origin = cam->position,
                .direction = glm::normalize(glm::vec3(world_coords) - cam->position)
            };
        }
    }

    *ray_count = ray_idx;
}
