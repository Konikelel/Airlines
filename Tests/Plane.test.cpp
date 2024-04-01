#include "Plane/Plane.h"

#include <iostream>

#include "Utils/CustomErrors.h"

int testPlane() {
    Plane plane1{101, "B737", 100, 3, 2};
    Plane plane2{102, "B737", 100, 3, 2};

    Plane plane3{101, "B737", 100, 3, 2};

    return 0;
}