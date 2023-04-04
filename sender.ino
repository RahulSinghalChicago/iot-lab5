Adafruit_GPS GPS;
PulseOximeter pox;

// Sound Sensor
int sensorPin = 7;
int ledPin = 13;

void setup()
{
	// pox(Vitals)
	pinMode(2, INPUT);
	pinMode(3, OUTPUT);

	// Temperature
	pinMode(A1, INPUT);

	// Sound Sensor
	pinMode(sensorPin, INPUT);
	pinMode(ledPin, OUTPUT);

	// network
	pinMode(0, OUTPUT);

	Serial.begin(9600);
}
void loop()
{
	if (Serial.available() > 0)
	{
		// GPS
		string gpsResult = GPS.read();
		Serial.println(gpsResult);

		// pox(Vitals)
		if (pox.begin())
		{
			string spO2_res = pox.getSpO2();
			string hb_res = pox.getHeartRate();
			Serial.println("Oxygen percentage: " + spO2_res + "; Heart rate: " + hb_res);
		}
		digitalWrite(3, HIGH);

		// Temperature
		float temp = analogRead(A1) / 1023.0 * 5.0 * 100.0;
		Serial.println("temperature: " + to_string(temp));

		// Sounce Sensor
		float val = digitalRead(sensorPin);
		if (val == HIGH)
		{
			digitalWrite(ledPin, HIGH);
		}
		else
		{
			Serial.println(val);
			digitalWrite(ledPin, LOW);
		}

		// network
		string msg = "Your message here";
		Serial.sendMessage(0, msg, "1680090096354");
	}
	else
	{
		Serial.write("No data");

		// pox(Vitals)
		digitalWrite(3, LOW);
	}
	delay(1000);
}
