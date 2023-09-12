// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "mypcm.h"

// function prototypes
void run(asignal *inputsignal);

int main()
{
    asignal *inputsignal = (asignal *)malloc(sizeof(asignal));
    run(inputsignal);

    // call any other function here

    free(inputsignal);
    return 0;
}

void run(asignal *inputsignal)
{
    double A, omega, sigma, duration;
    int interval, encoderbits, levels;
    printf("Enter A omega sigma duration interval encoderbits: ");
    if (scanf("%lf %lf %lf %lf %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits) != 6)
    {
        printf("Error: Invalid input format.\n");
        return 1;
    }
    inputsignal->A = A;
    inputsignal->duration = duration;
    inputsignal->omega = omega;
    inputsignal->sigma = sigma;

    levels = encoderbits * encoderbits;

    float samples[interval];
    int pcmpulses[interval];
    int dsignal[interval];

    float *ptrsamples = samples;
    int *ptrpcmpulses = pcmpulses;
    int *ptrdsignal = dsignal;

    sampler(ptrsamples, interval, *inputsignal);
    quantizer(ptrsamples, ptrpcmpulses, levels, inputsignal->A);
    encoder(ptrpcmpulses, ptrdsignal, encoderbits);

    for (int i = 0; i < interval; i++)
    {
        printf("%d \n", dsignal[i]);
    }
}
