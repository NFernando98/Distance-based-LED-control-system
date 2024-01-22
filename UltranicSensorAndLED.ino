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

  // Adjusted the threshold value based on your system's requirements
  if (averageDistance <= 50) {
    // If average distance is below the threshold, turn off the LED
    analogWrite(led, 0);
  } else {
    brightness = map(averageDistance, 50, 200, 0, 255);  // Adjusted mapping based on expected distance range
    brightness = constrain(brightness, 0, 255);
    analogWrite(led, brightness);
  }

  delay(1000);
}
