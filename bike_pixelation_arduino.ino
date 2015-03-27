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

	sensorVal = analogRead(hall);

	if (sensorVal < sensorThreshold && sensorActive == false) {

		sensorActive = true;

		timeDifference = currentTime - prevTime;

		wheelSpeed = map(timeDifference, 150, 680, 1023, 0);
		Serial.println(wheelSpeed);

		prevTime = currentTime;

	} else if (sensorVal > sensorThreshold)  {

		sensorActive = false;

	} 

        if (currentTime - prevTime > 2000 && sensorVal > sensorThreshold) {
         wheelSpeed = 1;
        Serial.println(wheelSpeed);
       delay(10); 
        }
}
