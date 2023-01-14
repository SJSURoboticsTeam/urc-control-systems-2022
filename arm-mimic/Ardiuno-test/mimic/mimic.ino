// POC test for the mimic potentiometers using an Arduino.

#define ROTUNDA_PIN A0
#define SHOULDER_PIN A1
#define ELBOW_PIN A2
#define LEFT_WRIST_PIN A3
#define RIGHT_WRIST_PIN A4

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int rotunda_out = analogRead(ROTUNDA_PIN);
  int shoulder_out = analogRead(SHOULDER_PIN);
  int elbow_out = analogRead(ELBOW_PIN);
  int left_wrist_out = analogRead(LEFT_WRIST_PIN);
  int right_wrist_out = analogRead(RIGHT_WRIST_PIN);
  Serial.print("Rotunda: " + String(rotunda_out) + " Shoulder: " +  String(shoulder_out) + " Elbow: " + String(elbow_out));
  Serial.println(" Left Wrist: " + String(left_wrist_out) + " Right Wrist: " + String(right_wrist_out));
  delay(1);
}