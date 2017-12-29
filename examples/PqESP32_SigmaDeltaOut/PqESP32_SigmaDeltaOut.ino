/**
 * Pq_SigmaDeltaOut
 * Demonstrates analog sigma-delta output by sending a ramping value into a LED output
 * connected to pin 18.
 *
 * The circuit:
 * - LED anode (long leg) attached to output 18
 * - LED cathode (short leg) attached to ground
 *
 * Created in 2017 by Sofian Audry
 *
 * This example code is in the public domain.
 */
#include <PlaquetteESP32.h>

// The LED.
SigmaDeltaOut led;

// The triangle/saw oscillator.
/* NOTES:
   - try changing the second parameter to 0 and 1 and see how it affects the LED
   - try replacing the line with the following:
       SineOsc oscillator(5.0);
*/
TriOsc oscillator(5.0, 0.5); // period of 5 seconds, width of 50% (triangle)

void begin() {
  led.attach(18);
}

void step() {
  oscillator >> led;
}
