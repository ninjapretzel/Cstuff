
//Include guards are fucking stupid imho fam smh
#ifndef VECTOR3
#define VECTOR3

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;


float length(Vector3* v);
float sqrLength(Vector3* v);
Vector3* normalized(Vector3* v);

Vector3* newVector3(float a, float b, float c);


#endif // VECTOR3
