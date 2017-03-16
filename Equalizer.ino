// Arduino pin numbers
const int DO_pin = 2;
const int AO_pin = 0;
int frequency;
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;
int led6 = 8;
int led7 = 9;


 
void setup() {
  pinMode(DO_pin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  Serial.begin(9600);
}
 
void loop() {

    if (frequency > 31) {
    digitalWrite(led1, HIGH);
  }
    if (frequency < 31) {
    digitalWrite(led1, LOW);
  }
    if (frequency > 35) {
    digitalWrite(led2, HIGH);
  }
    if (frequency < 35) {
    digitalWrite(led2, LOW);
  }
    if (frequency > 40) {
    digitalWrite(led3, HIGH);
  }
    if (frequency < 40) {
    digitalWrite(led3, LOW);
  }
    if (frequency > 45) {
    digitalWrite(led4, HIGH);
  }
    if (frequency < 45) {
    digitalWrite(led4, LOW);
  }
    if (frequency > 50) {
    digitalWrite(led5, HIGH);
  }
    if (frequency < 50) {
    digitalWrite(led5, LOW);
  }
    
    if (frequency < 55) {
    digitalWrite(led6, HIGH);
  }
    
    if (frequency < 55) {
    digitalWrite(led6, LOW);
  }
    
    if (frequency < 60) {
    digitalWrite(led7, HIGH);
  }
    
    if (frequency < 60) {
    digitalWrite(led7, LOW);
  }
  frequency = analogRead(AO_pin);
  Serial.print(digitalRead(DO_pin));
  Serial.print("-");
  Serial.println(analogRead(AO_pin));
} 

