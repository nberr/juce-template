#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

namespace gain {

struct Gain;

extern "C" {

Gain *create(double value);

void destroy(Gain *gain);

void process(Gain *gain,
             const float *input_l,
             const float *input_r,
             float *output_l,
             float *output_r,
             uintptr_t sample_count);

void set_gain(Gain *gain, double value);

} // extern "C"

} // namespace gain
