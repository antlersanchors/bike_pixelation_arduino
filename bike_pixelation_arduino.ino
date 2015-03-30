//hall_effect.ino

int led = 13;

#define hall A0

int sensorVal;

unsigned long prevTime;
unsigned long currentTime;
int timeDifference;

// what value registers as a rotation
int sensorThreshold;
boolean sensorActive;

// how fast are you going?
int wheelSpeed;

void setup() {
 // put your setup code here, to run once:
 pinMode(led, OUTPUT);

 Serial.begin(9600);

 // initialize our timer
 prevTime = 0;
 currentTime = 0;

 sensorActive = false;
 sensorThreshold = 7;

}

void loop() {

	currentTime = millis();
       timeDifference = currentTime - prevTime;

	sensorVal = analogRead(hall);
        

	if (sensorVal < sensorThreshold && sensorActive == false && timeDifference > 150) {

		sensorActive = true;

 		wheelSpeed = int(map(timeDifference, 150, 680, 16, 1));
               wheelSpeed = constrain(wheelSpeed, 1, 16);
 		Serial.write(wheelSpeed);
 		//Serial.write(10);

		prevTime = currentTime;

	} else if (sensorVal > sensorThreshold)  {

		sensorActive = false;

	}

       // if wheel hasn't turned in a while, send a value of maximum slowness
       if (currentTime - prevTime > 2000 && sensorVal > sensorThreshold) {
         wheelSpeed = 1;
         Serial.write(wheelSpeed);
         delay(100);
       }
}
