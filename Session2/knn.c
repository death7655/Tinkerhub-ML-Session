#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _point
{
    double x;
    double y;
    int vote;
} point;

int predict(point *pts, point *input, int categories, int points, int k);
int predict(point *pts, point *input, int categories, int points, int k)
{
    double distances[k][2];

    for(int i = 0; i < k; i++)
    {
        // distance[k][0] = distance
        // distance[k][1] = vote

        distances[i][0] = 1e9; 
        distances[i][1] = 1; 
    }

    // sqrt((inputx - pointx) ^ 2 + (inputy - pointy) ^ 2)

    double distance = 0;
    double x = 0;
    double y = 0; 

    for(int i = 0; i < points; i++)
    {
        x = (input->x - pts[i].x);
        x = x * x;

        y = (input->y - pts[i].y);
        y = y*y;

        distance = x + y;
        distance = sqrt(distance);

        int largest_index = 0;
        for(int j = 1; j < k; j++)
        {
            if(distances[largest_index][0] < distances[j][0])
            {
                largest_index = j;
            }
        }

        if(distances[largest_index][0] > distance)
        {
            distances[largest_index][0] = distance;
            distances[largest_index][1] = pts[i].vote;
        }
    }

    int votes[categories];
    for(int i = 0; i < categories; i++)
    {
        votes[i] = 0;
    }

    int index = 0;
    for(int i = 0; i < k; i++)
    {
        index = (int)distances[i][1];
        votes[index] += 1;
    }

    int most_voted = 0;
    for(int i = 1; i < categories; i++)
    {
        if(votes[most_voted] < votes[i])
        {
            most_voted = i;
        }
    }

    return most_voted;
}

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
    int k = 3;

    point input = {10.0, 10.0};
    int predicted_class = predict(pts, &input, 4, n, 3);

    printf("Predicted class for point (%.2f, %.2f) is %d\n", input.x, input.y, predicted_class);
    return 0;
}