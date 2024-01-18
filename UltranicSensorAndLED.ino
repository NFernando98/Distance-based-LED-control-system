#define trigPin 13
#define echoPin 12
#define led 11

int brightness = 0;    // how bright the LED is

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

}

void loop() {


  long duration, distance;

  // Clear the trigger pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a 10 microsecond pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance based on the duration
  distance = (duration / 2) / 29.1;

  // Check if the calculated distance is less than 10 cm
  // if (distance < 10) {
  //   // If yes, turn on the LED
  //   digitalWrite(led, HIGH);
  // } else {
  //   // If no, turn off the LED
  //   digitalWrite(led, LOW);
  // }


  // Print the calculated distance to the Serial Monitor
  Serial.print(distance);
  Serial.println(" cm");

   // Control the LED based on distance
  if (distance <= 0) {
    analogWrite(led, 0);  // Turn off the LED if there is no object
  } else {
    // Map the distance to a brightness value between 0 and 255 (reverse mapping)
    brightness = map(distance, 0, 100, 255, 0);
    brightness = constrain(brightness, 0, 255);  // Ensure brightness is within valid range
    analogWrite(led, brightness);
  }

  // Delay for 500 milliseconds before the next iteration
  delay(1000);
}



