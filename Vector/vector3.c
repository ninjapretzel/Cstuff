#include <math.h>
#include "vector3.h"
#include "util.h"

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
///Returns the length of a given Vector3
float length(Vector3* vp) {
    Vector3 v = *vp;
    return sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
///Returns the square of the length of a given Vector3
float sqrLength(Vector3* vp) {
    Vector3 v = *vp;
    return v.x*v.x + v.y*v.y + v.z*v.z;
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// Returns the pointer to a new Vector3, which is the given Vector3, normalized.
/// The returned vector has a length of 1.
Vector3* normalized(Vector3* vp) {
    float l = length(vp);
    return newVector3(vp->x / l, vp->y / l, vp->z / l);
}

void float3_c(Vector3* this, float a, float b, float c) { this->x = a; this->y = b; this->z = c; }
void float3_d(Vector3* this) { }

Vector3* newVector3(float a, float b, float c) {
    Vector3* vp = 0;
    vp = malloc(sizeof(Vector3));
    if (!vp) { panic("Vector3.newVector3: malloc failed!"); return 0; }

    float3_c(vp, a, b, c);
    return vp;
}

void kill(Vector3* this) { float3_d(this); free(this); }
