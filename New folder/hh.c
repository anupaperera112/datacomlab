// function prototypes
#include <stdio.h>
#include <math.h>

typedef struct
{
    float A;
    float omega;
    float sigma;
    int duration;
} asignal;

// function prototypes
float analog_signal_generator(asignal signal, int t);
void sampler(float *samples, int interval, asignal signal);
void quantizer(float *samples, int *pcmpulses, int levels, float A);
void encoder(int *pcmpulses, int *dsignal, int encoderbits);

void run(asignal *inputsignal);

// Implement functions here

int interval;
float analog_signal_generator(asignal signal, int t)
{
    // TODO
    float x_t = signal.A * sin(signal.omega * t + signal.sigma);
    return x_t;
}
void sampler(float *samples, int interval, asignal signal)
{
    // TODO
    interval = interval;
    for (int i = 0; i < interval; i++)
    {
        samples[i] = analog_signal_generator(signal, i);
    }
}

void quantizer(float *samples, int *pcmpulses, int levels, float A)
{
    // TODO
    for (int i = 0; i < interval; i++)
    {
        pcmpulses[i] = floor(((samples[i] + A) / (2 * A)) * levels);
    }
}
void encoder(int *pcmpulses, int *dsignal, int encoderbits)
{
    // TODO
    printf("anupa");
    for (int k = 0; k < interval; k++)
    {
        for (int i = encoderbits - 1; i >= 0; i--)
        {
            int bit = (pcmpulses[k] >> i) & 1;
            dsignal[k] = bit;

            printf("%d", bit);
        }
    }
}

//-------------------------------------------------------------

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

    scanf("%lf %lf %lf %lf %d %d", &A, &omega, &sigma, &duration, &interval, &encoderbits);

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
}