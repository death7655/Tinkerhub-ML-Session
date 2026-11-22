#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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


/*
    input  
        value - double
    
    output = probality double
*/

double sigmoid(double value);

double sigmoid(double value)
{
    if(value >= 0)
    {
        return 1.0 / (1 + exp(-value));
    }
    else
    {
        double z = exp(value);
        return z / (1 + z);
    }
}

/*
    log loss
    l = 1/n * sum(y log(p) - (1-y)log(1-p))

    p = sigmoid(z)
    z = wx + b
*/

double log_loss(double *x, double *y, double count, double slope, double intercept)
{
    double total = 0;
    double y_pred = 0; 
    double p = 0; 

    double positive = 0; 
    double negative = 0;
    for(int i = 0; i < count; i++)
    {
        y_pred = x[i] * slope + intercept; //(-inf, inf)
        p = sigmoid(y_pred); // (0, 1)

        positive = y[i] * log(p);
        negative = (1 - y[i]) * log(1 - p);

        total = total + positive + negative;
    }

    total = total / count;
    return total; 
}

double predict(double slope, double intercept, double input)
{
    double y_pred = slope * input + intercept;
    return sigmoid(y_pred);
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

        double p = 0; 
        double delta_m = 0;
        double delta_b = 0;

        for(int i = 0; i < count; i++)
        {
            y_pred = *slope * x[i] + *intercept;
            p = sigmoid(y_pred);
            y_diff = p - y[i];

            delta_m = delta_m + (y_diff * x[i]);
            delta_b = delta_b + y_diff; 
        }

        delta_m = delta_m / count; 
        delta_b = delta_b / count; 

        *slope = *slope - learning_rate * delta_m;
        *intercept = *intercept - learning_rate * delta_b;
    }

    
}

int main(void)
{
    double x[] = {1,2,3,4,5,6,7,8};
    double y[] = {0, 0, 0, 1, 1, 1, 1, 1};

    int x_count = (int)(sizeof(x) / sizeof(double));
    int y_count = (int)(sizeof(y) / sizeof(double));

    if(x_count != y_count)
    {
        printf("Invalid Dataset\n");
        return -1;
    }

    double slope = 0;
    double intercept = 0; 


    double learning_rate = 0.05;
    double iter = 1000;
    gd(x, y, x_count, &slope, &intercept, learning_rate, iter);
    double error = log_loss(x, y, x_count, slope, intercept);
    printf("gd y = %.2fx + %.2f\n", slope, intercept);
    printf("Error: %.2f\n", error);

    double input = 10; 
    double predicted = predict(slope, intercept, input);
    printf("Hours: %.2f, Probablity: %.2f", input, predicted);

    return 0; 
}