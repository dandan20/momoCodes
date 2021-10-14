/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
Mauricio:
Deuxième méthode de connexion du capteur de ligne
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Encoder.h>

Encoder knobGauche(2, 4);
Encoder knobDroite(3, 5);



// Create the motor shield object with the default I2C address
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
 Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
  

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotorGauche = AFMS.getMotor(2);
Adafruit_DCMotor *myMotorDroite = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

static unsigned long lastMilli  = 0;
static unsigned long lastMilli2 = 0;
static int token;

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  
  myMotorGauche->setSpeed(0);
  myMotorGauche->run(FORWARD);
  // turn on motor
  //myMotorGauche->run(RELEASE);

  
  
  myMotorDroite->setSpeed(0);
  myMotorDroite->run(FORWARD);
  // turn on motor
  //myMotorDroite->run(RELEASE);
  lastMilli  = millis();
  lastMilli2 = millis();
  knobGauche.write(0);
  knobDroite.write(0);
  token =2;
  
}

void loop() {
  uint8_t i;
  long newGauche, newDroite;
  static long limit_knob_Gauche=0;
  static long limit_knob_Droite=0;
  static int Haptic_01;

  if (Serial.available()>0) 
  {
    char var_read;
    var_read=Serial.read();
    if (var_read=='a') knobDroite.write(0);
    if (var_read=='b') myMotorDroite->setSpeed(0);
  
    if (var_read=='c')
      {
          myMotorGauche->run(BACKWARD);
          myMotorGauche->setSpeed(0);
          // turn on motor
          //myMotorGauche->run(RELEASE);
        
          
          myMotorDroite->run(BACKWARD);
          myMotorDroite->setSpeed(0);
          // turn on motor
          //myMotorDroite->run(RELEASE);
          knobGauche.write(0);
          knobDroite.write(0);
          token =3;
      }
  }  
  newGauche = knobGauche.read();
  newDroite = knobDroite.read();
  
      if(millis()-lastMilli > 100){ 
      Serial.println(newDroite);
      lastMilli = millis();
      }

}
