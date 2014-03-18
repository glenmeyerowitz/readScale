/*
  This code will allow you to connect a digital scale to an Arduino and read the weights from the scale. 

  The current code has been calibrated and works with a Walgreens Digital Glass Scale. A full document on 
  how to connect the scale to the Arduino can be found online at http://github.com/glenmeyerowitz/readScale. 
  The scale will need to be calibrated before use. Calibration instructions are also online. 

  March 17, 2014
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
  // average lots of readings together to get a stable value
  for(int i=1; i<=iter; i++){
      scaleValue += analogRead(scalePin);
      scaleValue -= 545.25;
      delay(15);
  }
  
  // print out the value you read:
  scaleValue = scaleValue / iter;
  weight = 0.001*scaleValue*scaleValue + 4.5899*scaleValue + 0.0007;
  Serial.println(weight);

  // turn scale off after data collection
  digitalWrite(scalePowerPin, HIGH);

  delay(100); // wait 0.1 seconds before collecting more data
}
