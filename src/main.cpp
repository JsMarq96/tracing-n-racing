#include <cstdio>

#include "scene.h"
#include "camera.h"
#include "utils.h"
#include "intersection/intersection_types.h"

#define BASE_WITDH 1080
#define MAX_RAY_COUNT (1080 * 720) + 1

int main() {
    printf("Raytracer test");

    sCamera camera;
    sScene scene;

    Camera_config_view(&camera, glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    Camera_config_projection(&camera, DEG2RAD(90.0f), 16.0f/9.0f, 0.001f, 10.00f);

    Intersection::sRay *ray_list = (Intersection::sRay*) malloc(sizeof(Intersection::sRay) * MAX_RAY_COUNT);
    Intersection::sResult *ray_results = (Intersection::sResult*) malloc(sizeof(Intersection::sResult) * MAX_RAY_COUNT);

    // Populate the scene
    {
        Scene_Add_sphere(&scene, glm::vec3(5.0f, 0.0f, 0.0f), 1.0f, {.albedo = glm::vec3(1.0f, 0.0f, 0.0f)});
    }

    uint32_t ray_count = 0u;
    Camera_create_camera_rays(&camera, BASE_WITDH, MAX_RAY_COUNT, ray_list, &ray_count);

    uint32_t intersction_count = 0u;
    Scene_test_rays(&scene, ray_count, ray_list, &intersction_count, ray_results);

    printf("Total hit count %d of %d\n", intersction_count, ray_count);

    free(ray_list);
    free(ray_results);
    return 0;
}
