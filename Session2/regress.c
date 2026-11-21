#include <stdio.h>
#include <stdlib.h>

/*
    inputs
        x 
        y
        count
        slope
        intercept 
    output 
        MSE Error
*/

double mse(double *x, double *y, double count, double slope, double intercept);

/*
    ordinary Least squares
    cacluate m and calculate b

    num = sum((xi - x_mean)(yi - y_mean))
    dem = sum((xi - x_mean) ^ 2)

    b = y_mean - m * x_mean

    x_mean
    y_mean
    xi-xmean
    yi-ymean
    xi-xmean ^ 2

    slope and intercept
*/
void ols(double *x, double *y, double count, double *slope, double *intercept);

/*
    Gradident - 
    
    input
    x
    y
    count 
    *slope 
    *intercept
    alpha - learning rate
    iter - epoch


    dm = (2 * (y_predicetd - y) * xi) / count
    db = (2 *(y_predicted - y)) / count

    y_predicted
    y
    delta_m
    debta_b
*/

void gd(double *x, double *y, double count, double *slope, double *intercept, double learning_rate, double iter);



double mse(double *x, double *y, double count, double slope, double intercept)
{
    // (1 / n) * sum((y - y_pred) ^ 2)

    double total = 0; 
    double predicted = 0; 
    double y_diff = 0;
    for(int i = 0; i < count; i++)
    {
        predicted = x[i] * slope + intercept;
        y_diff = predicted - y[i];
        total = total + (y_diff * y_diff);
    }

    double mse = total / count; 
    return mse; 
}

// y = mx + b

void ols(double *x, double *y, double count, double *slope, double *intercept)
{
    double x_mean = 0;
    double y_mean = 0;
    for(int i = 0; i < count; i++)
    {
        x_mean = x_mean + x[i];
        y_mean = y_mean + y[i];
    }

    x_mean = x_mean / count;
    y_mean = y_mean / count; 

    double num = 0;
    double dem = 0; 
    double x_diff = 0;
    double y_diff = 0;
    for(int i = 0; i < count; i++)
    {
        x_diff = x[i] - x_mean;
        y_diff = y[i] - y_mean;

        num = num + (x_diff * y_diff);
        dem = dem + (x_diff * x_diff);
    }

    double m = num / dem;
    double b = y_mean - m * x_mean; 

    *slope = m;
    *intercept = b; 
}

void gd(double *x, double *y, double count, double *slope, double *intercept, double learning_rate, double iter)
{
    for(int j = 0; j < iter; j++)
    {
        if(j % 100 == 0)
        {
            double error = 0;
            double y_diff = 0; 
            for(int z = 0; z < count; z++)
            {
                y_diff = y[z] - (*slope * x[z] + *intercept);
                y_diff *= y_diff;
                error += y_diff;
            }
            error = error / count;
            printf("Iterations %d, MSE: %.2f\n", j, error);
        }
        double y_pred = 0; 
        double y_diff = 0; 
        double delta_m = 0;
        double delta_b = 0;

        for(int i = 0; i < count; i++)
        {
            y_pred = *slope * x[i] + *intercept;
            y_diff = y_pred - y[i];

            delta_m = delta_m + (y_diff * x[i]);
            delta_b = delta_b + y_diff; 
        }

        delta_m = (2 * delta_m) / count; 
        delta_b = (2 * delta_b) / count; 

        *slope = *slope - learning_rate * delta_m;
        *intercept = *intercept - learning_rate * delta_b;
    }

    
}

int main(void)
{
    double x[] = {1,2,3,4,5,6,7,8};
    double y[] = {38, 52, 58, 73, 79, 93, 101, 112};

    int x_count = (int)(sizeof(x) / sizeof(double));
    int y_count = (int)(sizeof(y) / sizeof(double));

    if(x_count != y_count)
    {
        printf("Invalid Dataset\n");
        return -1;
    }

    double slope = 0;
    double intercept = 0; 

    printf("Enter your slope: ");
    scanf("%lf", &slope);

    printf("Enter your intercept: ");
    scanf("%lf", &intercept);

    double error = mse(x, y, x_count, slope, intercept);
    printf("y = %.2fx + %.2f\n", slope, intercept);
    printf("Error: %.2f\n", error);

    ols(x, y, x_count, &slope, &intercept);
    error = mse(x, y, x_count, slope, intercept);
    printf("y = %.2fx + %.2f\n", slope, intercept);
    printf("Error: %.2f\n", error);

    slope = 0;
    intercept = 0; 

    double learning_rate = 0.05;
    double iter = 1000;
    gd(x, y, x_count, &slope, &intercept, learning_rate, iter);
    error = mse(x, y, x_count, slope, intercept);
    printf("gd y = %.2fx + %.2f\n", slope, intercept);
    printf("Error: %.2f\n", error);

    return 0; 
}