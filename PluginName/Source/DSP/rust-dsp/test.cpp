#include "gain.hpp"

int main(void) {
   auto pGain = gain::create(0.5f);
   gain::set_gain(pGain, 0.7f);
   gain::destroy(pGain);
}
