#include "utils.h"

#include <cstdint>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <glm/ext.hpp>

#ifdef _WIN32
#include <chrono>
#else
#include <sys/time.h>
#endif

inline double random_double() {
    return glm::linearRand(0.0, 1.0);
}

inline uint64_t get_timestamp_microsecs() {
#ifdef _WIN32
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
#else
    struct timeval stamp;
    gettimeofday(&stamp, NULL);

    return stamp.tv_sec * 1000000u + stamp.tv_usec;
#endif
}

 void write_ppm(  const float* raw_data,
                        const uint32_t width,
                        const uint32_t height,
                        const char* file_name) {
    FILE* file = fopen(file_name, "w");

    // Write header with format
    fprintf(file, "P3\n%d %d\n255\n", width, height);

    // Write the clamped img data
    for(uint32_t j = 0u; j < height; j++) {
        for(uint32_t i = 0u; i < width; i++) {
            const uint32_t idx = (i + width * j) * 3u;
            fprintf(file,
                    "%d %d %d\n",
                    uint32_t(255.999f * glm::clamp(raw_data[idx], 0.0f, 0.999f)),
                    uint32_t(255.999f * glm::clamp(raw_data[idx+1u], 0.0f, 0.999f)),
                    uint32_t(255.999f * glm::clamp(raw_data[idx+2u], 0.0f, 0.999f)));
        }
    }

    fclose(file);
}


bool quadratic_solver(const float a, const float b, const float c, float* t1, float *t2) {
    const float term = b * b - 4.0f * a * c;

    if (term < 0.0f) {
        return false;
    }

    const float denom = 2.0f * a;
    const float minus_b = -b;

    if (term == 0.0f) {
        *t1 = minus_b / denom;
        *t2 = *t1;
    } else {
        const float sqrt_term = sqrtf(term);
        const float tt1 = (minus_b + sqrt_term) / denom;
        const float tt2 = (minus_b - sqrt_term) / denom;

        *t1 = glm::min(tt1, tt2);
        *t2 = glm::max(tt1, tt2);
    }

    return true;
}
