#pragma once

#include <cstdint>
#include <glm/vec3.hpp>

namespace Intersection {
    struct sRay {
        glm::vec3 origin;
        glm::vec3 direction;
    };

    struct sResult {
        uint16_t ray_idx = 0u;
        uint32_t object_idx = 0u;

        glm::vec3 col_point;
        glm::vec3 col_normal;

        float ray_t = 0.0;

        void* payload = nullptr;
    };
}
