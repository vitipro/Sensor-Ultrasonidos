unsigned long tickStartTrigger, tickStartEcho, tickEnd;
unsigned long elapsedTimeTrigger, elapsedTimeEcho;
int triggerPin = 2, echoPin = 3;
int num_samples = 100;
int max_dist = 50;
const float velocitatSo = 34320; // cm/s
float real_dist;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float time_to_cm(unsigned long t) {
    return (float(t)/1000000) * velocitatSo / 2;
}

float get_dist(){
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
  //Serial.print("trigger: ");
  //Serial.print(time_to_cm(elapsedTimeTrigger));
  //Serial.print(" echo: ");
  return time_to_cm(elapsedTimeEcho);
}

float get_avg() {
  float avg = 0;
  float aux;
  for (int i = 0; i < num_samples; ++i) {
      aux = get_dist();
      if (aux > max_dist) --i;
      else avg += aux;
      Serial.println(aux);
  }
  return avg / num_samples;
}  

  
void loop() {
  delay(5000);
  float inc = 5;
  for (int i = 0; i < 8; ++i){
    real_dist = 5 + inc * i;
    max_dist = real_dist + 20;
    float avg = get_avg();
    Serial.print(real_dist);
    Serial.print(" -> ");
    Serial.print(avg);
    Serial.print('\n');
    delay(5000);
  }
  while(true);
}
