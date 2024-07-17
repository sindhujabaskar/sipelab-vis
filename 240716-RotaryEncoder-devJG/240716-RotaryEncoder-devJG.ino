#include <Encoder.h>

// Define the encoder pins
Encoder rotary(2, 3);

// Initialize variables
long previousPosition = 0;
long currentPosition;
int positionChange;
int startTime;
const int sampleWindow = 50; // Sample window in milliseconds
int currentTime = 0;
int lastSampleTime = 0;
float elapsedTime;

void setup() {
  // Initialize serial communication at a baud rate of 57600
  Serial.begin(57600);
  // Record the start time
  startTime = millis();
}

void loop() {
  // Calculate the elapsed time since the start
  currentTime = millis() - startTime;
  
  // Check if the current time is a multiple of the sample window and not equal to the last sample time
  if (currentTime % sampleWindow == 0 && lastSampleTime != currentTime) {
    // Calculate the elapsed time in seconds
    elapsedTime = currentTime / 1000.0;
    
    // Read the current position of the encoder
    currentPosition = rotary.read();
    
    // Calculate the change in position
    positionChange = currentPosition - previousPosition;
    
    // Print the position change to the serial monitor
    Serial.println(positionChange);
    
    // Update the last sample time
    lastSampleTime = currentTime;
    
    // Reset the position change
    positionChange = 0;
    
    // Update the previous position
    previousPosition = currentPosition;
  }
}
