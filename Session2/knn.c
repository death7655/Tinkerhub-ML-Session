#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _point
{
    double x;
    double y;
    int vote;
} point;



int main(void)
{
    point pts[] = {
        // Cluster 0: Bottom-left around (2.0, 2.0)
        {1.8, 2.1, 0},
        {2.0, 1.9, 0},
        {2.2, 2.3, 0},
        {1.9, 1.7, 0},
        {2.3, 2.0, 0},

        // Cluster 1: Top-left around (2.5, 9.0)
        {2.3, 8.8, 1},
        {2.5, 9.1, 1},
        {2.7, 8.9, 1},
        {2.4, 9.3, 1},
        {2.6, 8.7, 1},

        // Cluster 2: Bottom-right around (9.0, 2.5)
        {8.8, 2.4, 2},
        {9.1, 2.6, 2},
        {9.0, 2.2, 2},
        {9.3, 2.5, 2},
        {8.9, 2.8, 2},

        // Cluster 3: Top-right around (9.5, 9.5)
        {9.2, 9.4, 3},
        {9.5, 9.6, 3},
        {9.7, 9.3, 3},
        {9.4, 9.8, 3},
        {9.6, 9.5, 3}
    };
    int n = sizeof(pts) / sizeof(pts[0]);

    point input = {1.0, 2.0}
    return 0;
}