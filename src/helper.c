#include "helper.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double to_radians(double angle) {
        return angle * (M_PI/180);
}
