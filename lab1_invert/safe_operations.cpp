#include <limits>
#include <stdexcept>

double SafeMultiply(double x, double y) {
    if (y == 0) {
        return 0;
    }

    if (x == std::numeric_limits<double>::min()) {
        throw std::runtime_error("multiply overflow: x");
    }

    if (y == std::numeric_limits<double>::min()) {
        throw std::runtime_error("multiply overflow: y");
    }

    if ((x > 0 ? x : -x) > std::numeric_limits<double>::max() / (y > 0 ? y : -y)) {
        throw std::runtime_error("multiply overflow");
    }

    return x * y;
}

double SafeAddition(double x, double y) {
    return x + y;
}

double SafeSubtraction(double x, double y) {
    return x - y;
}