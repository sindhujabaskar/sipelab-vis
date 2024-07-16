#include <Encoder.h>

Encoder myEnc(2, 3); // Create an Encoder object using pins 2 and 3

unsigned long lastTime = 0;
long lastPosition = 0; // Variable to store the last known encoder position

// PARAMETERS TO BE MODIFIED BELOW
const float radius = 2.75; // Radius in inches (from center of the disc to the mouse's headplate)
const int samplingRateHz = 20; // Sampling rate in Hertz

// PARAMETERS CALCULATED FROM THE ABOVE
const float circumference = 3.14159 * (radius * 2); // Circumference of the disc in inches
const int pulsesPerRevolution = 600; // Number of pulses per revolution of the encoder
float totalDistance = 0.0; // Running total of distance traveled in inches
const unsigned long samplingInterval = 1000 / samplingRateHz; // Sampling interval in milliseconds

void setup() {
  Serial.begin(9600);

  // Enable internal pull-up resistors
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - lastTime;

  if (elapsedTime >= samplingInterval) { // Sample based on the specified interval
    long newPosition = myEnc.read();
    float revolutions = (float)newPosition / (pulsesPerRevolution * 4); // Adjust for quadrature encoding
    float distanceTraveled = fabs(revolutions * circumference); // Use fabs to ensure positive value

    if (distanceTraveled < 100.0) { // Sanity check: discard large outliers
      totalDistance += distanceTraveled; // Update the total distance traveled
    }

    Serial.print(" Total Distance: ");    // COMMENT OUT THIS ENTIRE LINE WHEN READING FROM RASPBERRY PI VIA SERIAL FOR CLARITY
    Serial.println(totalDistance); // Print the total distance in inches

    lastTime = currentTime;
    myEnc.write(0); // Reset the encoder position
  }
}
