unsigned long tickStartTrigger, tickStartEcho, tickEnd;
unsigned long elapsedTimeTrigger, elapsedTimeEcho;
int triggerPin = 2, echoPin = 3;
int num_samples = 100;
int max_dist = 50;
const float velocitatSo = 34320; // cm/s
float real_dist;
float t;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float time_to_cm(unsigned long t) {
    return (float(t)/1000000) * velocitatSo / 2;
}

float get_dist() {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  tickStartTrigger = micros();
  while (digitalRead(echoPin) == LOW);
  tickStartEcho = micros();
  while (digitalRead(echoPin) == HIGH);
  tickEnd = micros();
  elapsedTimeTrigger = tickEnd - tickStartTrigger;
  elapsedTimeEcho = tickEnd - tickStartEcho;
  t = ((tickEnd + tickStartEcho) / 2);
  return time_to_cm(elapsedTimeEcho);
}
  
void loop() {
  float x0 = get_dist();
  float t0 = t;
  while (true) {
    delay(1000);
    float x1 = get_dist();
    float t1 = t;
    float inc_dist = x1 - x0;
    float inc_t = (t1 - t0) / 1000000;
    Serial.println( inc_dist / inc_t );
    x0 = x1;
    t0 = t1;
  }
}
