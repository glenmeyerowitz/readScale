/*
  This code will allow you to connect a digital scale to an Arduino and read the weights from the scale. 

  The current code has been calibrated and works with a Walgreens Digital Glass Scale. A full document on 
  how to connect the scale to the Arduino can be found online at http://github.com/glenmeyerowitz/readScale. 
  The scale will need to be calibrated before use. Calibration instructions are also online. 

  March 21, 2014
  Glen Meyerowitz

  This code is in the public domain. 
*/

int scalePowerPin = 2;   // scale power from digital pin 2
int scalePin = A1;       // scale output connected to analog pin 1

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // set pin modes
  pinMode(scalePowerPin, OUTPUT);
  pinMode(scalePin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  double scaleValue = 0;       // the analog signal from the pin
  double weight = 0;           // stores the weight of the scale
  int iter = 75;               // number of iterations
  analogReference(EXTERNAL);   // use the AREF pin as a voltage reference. AREF should be shorted to 3.3V

  // turn scale on before data collection
  digitalWrite(scalePowerPin, LOW);
  delay(2500);
  
  // average lots of readings together to get a stable value
  for(int i=1; i<=iter; i++){
      scaleValue += analogRead(scalePin);
  }
  
  // print out the value you read:
  scaleValue = scaleValue / iter;
  weight = -0.00392590100618584*scaleValue*scaleValue + 8.92845692964501*scaleValue - 3649.30220197361;
  Serial.println(weight);

  // turn scale off after data collection
  digitalWrite(scalePowerPin, HIGH);

  delay(10000); // wait 10 seconds before collecting more data
}
