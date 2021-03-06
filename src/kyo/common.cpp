
#include "kyo/common.h"
#include "kyo/vector/vec2.h"
#include <math.h>
#include <sstream>
#include <cxxabi.h>


inline float lerp(float a, float b, float t) {

    return a + t * (b - a);
}

vec2 lerp(vec2 a, vec2 b, float t) {

    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t)};
}

namespace game {

    float round(float n, int decimals) {

        int f = (int)pow(10, decimals);

        return roundf(n * f) / f;
    }

    std::string round_str(float n, int decimals) {

        std::ostringstream ss;
        ss.precision(decimals);

        ss << std::fixed << n;
        return ss.str();
    }

    string demangle(const char *name) {

        return abi::__cxa_demangle(name, NULL, NULL, NULL);
    }
}
