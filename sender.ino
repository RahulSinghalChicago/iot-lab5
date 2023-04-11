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

	// Air Quality Sensor
	pinMode(A2, INPUT);
	pinMode(3, OUTPUT);
	pinMode(8, INPUT);

	// network
	pinMode(0, OUTPUT);

	Serial.begin(9600);
}
void loop()
{
	string spO2_res, hb_res, gpsResult;
	float temp, air_res;
	if (Serial.available() > 0)
	{
		// GPS
		gpsResult = GPS.read();
		//Serial.println(gpsResult);

		// pox(Vitals)
		if (pox.begin())
		{
			spO2_res = pox.getSpO2();
			hb_res = pox.getHeartRate();
			//Serial.println("Oxygen percentage: " + spO2_res + "; Heart rate: " + hb_res);
		}
		digitalWrite(3, HIGH);

		// Temperature
		temp = analogRead(A1) / 1023.0 * 5.0 * 100.0;
		//Serial.println("temperature: " + to_string(temp));

		// Air Quality Sensor
		air_res = analogRead(A2);
		delay(100);
		Serial.write("ppm: " + to_string(air_res));
		int digitalResult = digitalRead(8);
		delay(100);
		if (digitalResult == HIGH)
			digitalWrite(3, HIGH);
		else
			digitalWrite(3, LOW);

		// network
		string msg = "";
		/**
		string values[5] = {"GPS : " + gpsResult, "O2 : " + spO2_res, "HB : " + hb_res, "TMP : " + to_string(temp), "SND : " + to_string(val)};
		for (int i = 0;i < 5; i++) {
			msg += values[i];
			if (i != 4) {
				msg += ",";
			}
		}
		**/
		//msg = "{\"GPS\":[" + to_string(gpsResult[0]) + "," + to_string(gpsResult[1]) + "],\"TMP\":" + to_string(temp) + ",\"O2\":" + spO2_res + ",\"HB\":" + hb_res + ",\"SND\":" + to_string(val) + "}";
		msg = "{GPS:[" + to_string(gpsResult[0]) + "," + to_string(gpsResult[1]) + "],TMP:" + to_string(temp) + ",O2:" + spO2_res + ",HB:" + hb_res + ",AIR:" + to_string(air_res) + "}";
		//Serial.sendMessage(0, msg, "1680090096354");
		//Serial.sendMessage(0, msg, "1680659331923");
		Serial.sendMessage(0, msg);
        
	}
	else
	{
		Serial.write("No data");

		// pox(Vitals)
		digitalWrite(3, LOW);
	}
	delay(1000);
}
