#define trigPin 13
#define echoPin 12
#define led 11

const int numReadings = 10;
int readings[numReadings];
int index = 0;
int total = 0;
int brightness = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);

  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  total = total - readings[index] + distance;
  readings[index] = distance;
  index = (index + 1) % numReadings;

  float averageDistance = total / numReadings;

  Serial.print("Raw Distance: ");
  Serial.print(distance);
  Serial.print(" cm\t Smoothed Distance: ");
  Serial.println(averageDistance);

  // Apply a simple threshold for turning off the LED
  if (averageDistance <= 0) {
    analogWrite(led, 0);  // Turn off the LED if there is no object
  } else {
    // Map the distance to a brightness value between 0 and 255 (reverse mapping)
    brightness = map(averageDistance, 0, 100, 255, 0);
    
    // Apply the moving average filter to smooth out brightness changes
    brightness = constrain(brightness, 0, 255);  // Ensure brightness is within valid range
    analogWrite(led, brightness);
  }

  delay(100);  // Shorten the delay for more frequent updates
}
