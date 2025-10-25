#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double *components;
    int size;
} Vector3D;

Vector3D *createVector(int size) {
    Vector3D *vec = (Vector3D *)malloc(sizeof(Vector3D));
    vec->size = size;
    vec->components = (double *)malloc(size * sizeof(double));
    return vec;
}

void resizeVector(Vector3D *vec, int newSize) {
    vec->components = (double *)realloc(vec->components, newSize * sizeof(double));
    vec->size = newSize;
}

void inputVector(Vector3D *vec, const char *name) {
    printf("Enter %d components for vector %s: ", vec->size, name);
    for (int i = 0; i < vec->size; i++) {
        scanf("%lf", &vec->components[i]);
    }
}

void printVector(const Vector3D *vec, const char *name) {
    printf("%s: (", name);
    for (int i = 0; i < vec->size; i++) {
        printf("%.2f", vec->components[i]);
        if (i < vec->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

double dotProduct(const Vector3D *v1, const Vector3D *v2) {
    if (v1->size != v2->size) {
        printf("Error: Vectors must have the same size for dot product.\n");
        return -1;
    }

    double result = 0;
    for (int i = 0; i < v1->size; i++) {
        result += v1->components[i] * v2->components[i];
    }
    return result;
}

Vector3D *crossProduct(const Vector3D *v1, const Vector3D *v2) {
    if (v1->size != 3 || v2->size != 3) {
        printf("Error: Cross product is only defined for 3D vectors.\n");
        return NULL;
    }

    Vector3D *result = createVector(3);
    result->components[0] = v1->components[1] * v2->components[2] - v1->components[2] * v2->components[1];
    result->components[1] = v1->components[2] * v2->components[0] - v1->components[0] * v2->components[2];
    result->components[2] = v1->components[0] * v2->components[1] - v1->components[1] * v2->components[0];
    return result;
}

double magnitude(const Vector3D *vec) {
    double sum = 0;
    for (int i = 0; i < vec->size; i++) {
        sum += vec->components[i] * vec->components[i];
    }
    return sqrt(sum);
}

void freeVector(Vector3D *vec) {
    free(vec->components);
    free(vec);
}

int main() {
    int size;
    printf("Enter the size of the vectors (minimum 3 for cross product): ");
    scanf("%d", &size);

    if (size < 3) {
        printf("Error: Cross product requires vectors of size 3.\n");
        return 1;
    }

    Vector3D *v1 = createVector(size);
    Vector3D *v2 = createVector(size);

    inputVector(v1, "V1");
    inputVector(v2, "V2");

    printf("\nVectors:\n");
    printVector(v1, "V1");
    printVector(v2, "V2");

    double dot = dotProduct(v1, v2);
    if (dot != -1) {
        printf("\nDot Product: %.2f\n", dot);
    }

    Vector3D *cross = crossProduct(v1, v2);
    if (cross) {
        printf("Cross Product:\n");
        printVector(cross, "V1 x V2");
        freeVector(cross);
    }

    printf("\nMagnitude of V1: %.2f\n", magnitude(v1));
    printf("Magnitude of V2: %.2f\n", magnitude(v2));

    freeVector(v1);
    freeVector(v2);

    return 0;
}