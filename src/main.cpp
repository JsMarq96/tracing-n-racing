#include <cstdio>
#include <cstring>

#include "scene.h"
#include "camera.h"
#include "utils.h"
#include "intersection/intersection_types.h"

#define BASE_WITDH 1920.0f
#define ASPECT_RATIO (1.0f)
#define BASE_HEIGHT (BASE_WITDH / ASPECT_RATIO)
#define MAX_RAY_COUNT (BASE_WITDH * BASE_HEIGHT + 1)

glm::vec3 image[(uint32_t) (BASE_WITDH * BASE_HEIGHT)];

int main() {
    printf("Raytracer test\n");

    sCamera camera;
    sScene scene;

    Camera_config_view(&camera, glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Camera_config_projection(&camera, DEG2RAD(90.0f), ASPECT_RATIO, 0.01f, 10.00f);

    Intersection::sRay *ray_list = (Intersection::sRay*) malloc(sizeof(Intersection::sRay) * MAX_RAY_COUNT);
    Intersection::sResult *ray_results = (Intersection::sResult*) malloc(sizeof(Intersection::sResult) * MAX_RAY_COUNT);
    glm::uvec2 *ray_screen_coords = (glm::uvec2*) malloc(sizeof(glm::uvec2) * MAX_RAY_COUNT);

    // Populate the scene
    {
        Scene_Add_sphere(&scene, glm::vec3(5.0f, 0.0f, 0.0f), 0.250f, {.albedo = glm::vec3(1.0f, 0.0f, 0.0f)});
    }

    uint32_t ray_count = 0u;
    Camera_create_camera_rays(&camera, BASE_WITDH, MAX_RAY_COUNT, ray_list, ray_screen_coords, &ray_count);

    uint32_t intersction_count = 0u;
    Scene_test_rays(&scene, ray_count, ray_list, &intersction_count, ray_results);

    // Ray dir test
    /*{
        for(uint32_t i = 0u; i < MAX_RAY_COUNT; i++) {
            const float facing = glm::dot(glm::vec3(1.0f, 0.0f, 0.0f), ray_list[i].direction);
            image[i] = glm::vec3(facing);
        }

        write_ppm((float*) image, BASE_WITDH, BASE_WITDH / ASPECT_RATIO, "intersection_debug.ppm");
    }*/

    memset(image, 0, BASE_WITDH * BASE_HEIGHT * sizeof(float) * 3);

    for(uint32_t i = 0u; i < intersction_count; i++) {
        uint32_t ray_idx = ray_results[i].ray_idx;
        image[ray_idx] = glm::vec3(1.0f);
        glm::uvec2 &coords = ray_screen_coords[ray_idx];
        printf("%d %d OG: %d %d\n", ray_idx % (uint32_t)BASE_WITDH, ray_idx / (uint32_t) BASE_WITDH, coords.x, coords.y);
    }

    write_ppm((float*) image, BASE_WITDH, BASE_HEIGHT, "intersection_debug.ppm");

    printf("Total hit count %d of %d\n", intersction_count, ray_count);

    free(ray_list);
    free(ray_results);
    free(ray_screen_coords);
    return 0;
}
