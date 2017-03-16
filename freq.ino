//clipping indicator variables
boolean clipping = 0;
//data storage variables
byte newData = 0;
byte prevData = 0;
//freq variables
unsigned int timer = 0;//counts period of wave
unsigned int period;
int frequency;
void setup(){
 Serial.begin(9600);

 pinMode(13,OUTPUT);//led indicator pin

 cli();//diable interrupts

 //set up continuous sampling of analog pin 0

 //clear ADCSRA and ADCSRB registers
 ADCSRA = 0;
 ADCSRB = 0;
 
 ADMUX |= (1 << REFS0); //set reference voltage
 ADMUX |= (1 << ADLAR); //left align the ADC value- so we can readhighest 8 bits from ADCH register only

 ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32prescaler- 16mHz/32=500kHz
 ADCSRA |= (1 << ADATE); //enabble auto trigger
 ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
 ADCSRA |= (1 << ADEN); //enable ADC
 ADCSRA |= (1 << ADSC); //start ADC measurements

 sei();//enable interrupts
}
ISR(ADC_vect) {//when new ADC value ready
 prevData = newData;//store previous value
 newData = ADCH;//get value from A0
 if (prevData < 127 && newData >=127){//if increasing and crossingmidpoint
 period = timer;//get period
 timer = 0;//reset timer
 }


 if (newData == 0 || newData == 1023){//if clipping
 PORTB |= B00100000;//set pin 13 high- turn on clipping indicatorled
 clipping = 1;//currently clipping
 }

 timer++;//increment timer at rate of 38.5kHz
}
void loop(){
 if (clipping){//if currently clipping
 PORTB &= B11011111;//turn off clippng indicator led
 clipping = 0;
 }
 frequency = 38462/period;//timer rate/period
 //print results
 Serial.print(frequency);
 Serial.println(" hz");

 delay(100);
}
