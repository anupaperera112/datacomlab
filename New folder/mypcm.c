// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // includes malloc(),free()
#include <math.h>
// Add any necessary headers here

// user-defined header files
#include "mypcm.h" // do not modify this file

// put your function prototypes for additional helper functions below:

// implementation
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
	char bitPattern[encoderbits];
	for (int k = 0; k < interval; k++)
	{
		for (int i = encoderbits - 1; i >= 0; i--)
		{
			int bit = (pcmpulses[k] >> i) & 1;
			dsignal[k] = bit;
		}
	}
}