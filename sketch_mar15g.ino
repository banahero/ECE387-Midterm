//clipping indicator variables
boolean clipping = 0;
//data storage variables
byte newData = 0;
byte prevData = 0;
//freq variables
unsigned int timer = 0;//counts period of wave
unsigned int period;
int frequency;
int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;
int led5 = 7;
int led6 = 8;
int led7 = 9;
int DO = 2; //Pin for Digital Output - DO
int DA = A0; // Pin for Analog Output - AO
int threshold = 100; //Set minimum threshold for LED lit
int sensorvalue = 0;
const int DO_pin = 2;
const int AO_pin = 0;
void setup(){

 Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
 cli();//diable interrupts

 //set up continuous sampling of analog pin 0

 //clear ADCSRA and ADCSRB registers
 ADCSRA = 0;
 ADCSRB = 0;
 
 ADMUX |= (1 << REFS0); //set reference voltage
 ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only

 ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
 ADCSRA |= (1 << ADATE); //enabble auto trigger
 ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
 ADCSRA |= (1 << ADEN); //enable ADC
 ADCSRA |= (1 << ADSC); //start ADC measurements

 sei();//enable interrupts
}
ISR(ADC_vect) {//when new ADC value ready
 prevData = newData;//store previous value
 newData = ADCH;//get value from A0
 if (prevData < 127 && newData >=127){ //if increasing and crossing midpoint
 period = timer; //get period
 timer = 0; //reset timer
 }


 if (newData == 0 || newData == 1023){//if clipping
 PORTB |= B00100000;//
 clipping = 1; //currently clipping
 }

 timer++;//increment timer at rate of 38.5kHz
}
void loop()
{
 if (clipping){ //if currently clipping
 PORTB &= B11011111;//turn off clippng indicator led
 clipping = 0;
 }
 frequency = 38462/period;//timer rate/period
 //print results
 Serial.println(frequency);
 Serial.println(" hz");
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
    
    if (frequency > 55) {
    digitalWrite(led6, LOW);
  }
    
    if (frequency < 60) {
    digitalWrite(led7, HIGH);
  }
    
    if (frequency > 60) {
    digitalWrite(led7, LOW);
  }
  frequency = analogRead(AO_pin);
 Serial.print(digitalRead(DO_pin));
  Serial.print("-");
  Serial.println(analogRead(AO_pin));
} 
