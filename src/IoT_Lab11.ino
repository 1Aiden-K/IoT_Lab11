/*
 * Project IoT_Lab11
 * Description:
 * Author:
 * Date:
 */

#include "LIS3DH.h"
#include "oled-wing-adafruit.h"
#include "Particle.h"

unsigned long lastPrintSample = 0;
const unsigned long PRINT_SAMPLE_PERIOD = 100;

OledWingAdafruit display;
LIS3DHSPI accel(SPI, D3, WKP);

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup() {
    Serial.begin(9600);

	display.setup();
	display.setCursor(0,0);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.display();

	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);
}

void loop() {
    LIS3DHSample sample;

	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();
		display.setCursor(0,0);
		display.clearDisplay();
		if (accel.getSample(sample)) {
			display.println("X: " + String(sample.x));
			display.println("Y: " + String(sample.y));
			display.println("Z: " + String(sample.z));
		}
		else {
			display.println("no sample");
		}
		display.display();
	}
}