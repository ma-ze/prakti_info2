#ifndef FLOATIE_H_
#define FLOATIE_H_

#include <cmath>
#include <algorithm>

bool approximatelyEqual(float a, float b, float epsilon = std::numeric_limits<double>::epsilon()){
    return std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * epsilon);
}

#endif /* FLOATIE_H_ */