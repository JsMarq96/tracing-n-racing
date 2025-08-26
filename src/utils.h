#pragma once

#include <cstdint>

#define DEG2RAD(x) (x * 0,0174533)

double random_double();

uint64_t get_timestamp_microsecs();

void write_ppm( const double* raw_data,
                const uint32_t width,
                const uint32_t height,
                const char* file_name);

bool quadratic_solver(const float a, const float b, const float c, float *t1, float *t2);
