#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "EspSoftwareSerial/SoftwareSerial.h"
#include "SparkFun_Si7021/src/Si7021.h"

#include "Duration.h"
#include "Logger.h"

#include "SimpleWifiManager.h"
#include "../WifiConnectionData.h"

#include "PmsX003.h"
#include "PmsMeasurement.h"
#include "EmptyData.h"
#include "PmsData.h"

#include "TempRhData.h"

#include "Timers.h"

#include "HttpClient.h"
#include "../HttpConnectionData.h"

Logger logger(Serial, "Powietrze", INFO);

/* PMS settings */
static const uint8_t PMS_SET_PIN = D7;
static const uint32_t PMS_READ_INTERVAL = Duration::Minutes(4);
Logger pmsLogger(Serial, "PmsX003", INFO);
SoftwareSerial pmsSerial(D5, D6, false, 256);
PmsX003 pmsX003(pmsSerial, PMS_SET_PIN, pmsLogger);
static const PmsData emptyPmsPata = EmptyData();
PmsData lastPmsData = emptyPmsPata;

/* Http */
HttpConnectionData httpConnectionData;
Logger httpLogger(Serial, "HttpClient", INFO);

/* Wifi */
WifiConnectionData wifiConnectionData;
Logger simpleWifiManagerLogger(Serial, "SimpleWifiManger", INFO);
SimpleWifiManager wifiManager = SimpleWifiManager(WiFi, wifiConnectionData,
		simpleWifiManagerLogger);
WiFiClient client;

/* Timers */
Logger timersLogger(Serial, "Timers", INFO);
Timers timers(timersLogger);

/* Si7021 */
static const TempRhData emptySiData = TempRhData();
TempRhData lastSiData = emptySiData;
Si7021 si7021;

bool connectWifi() {
	return wifiManager.connect();
}

void disconnectWifi() {
	wifiManager.disconnectAndOff();
	client.stop();
}

PmsData readPms() {
	PmsMeasurement pmsMeasurement = PmsMeasurement(pmsX003);
	PmsData pmsData = pmsMeasurement.measure();
	if (pmsData == EmptyData()) {
		logger.logInfo("No data received");
	}

	return pmsData;
}

TempRhData readSi() {
	float rh = si7021.getRH();
	float temp = si7021.readTemp();
	lastSiData = TempRhData(temp, rh);
	return lastSiData;
}

void clearWeatherData() {
	lastPmsData = emptyPmsPata;
	lastSiData = emptySiData;
}

bool isTimeout(uint32_t timer, uint32_t length) {
	return millis() - timer >= length;
}

void resetTimer(uint32_t& timer) {
	timer = millis();
}

uint32_t retryTimeout;

void gatherWeatherData() {
	lastPmsData = readPms();
	lastSiData = readSi();
	resetTimer(retryTimeout);
}

void firstGatherWeatherData() {
	gatherWeatherData();
	timers.intervalTimer(PMS_READ_INTERVAL, gatherWeatherData);
}

bool sendDataToHttp() {
	if (!client.connect(httpConnectionData.getHttpHost(),
			httpConnectionData.getHttpPort())) {
		logger.logError("Http connection failed");
		return false;
	}

	HttpClient http(client, httpConnectionData, httpLogger);
	http.sendGetRequest(0, 2, 0, lastPmsData.getPm25(), lastPmsData.getPm10());
	return true;
}

void processWeatherData() {
	static bool httpSent = false;
	bool processingEnd = false;
	if (lastPmsData != emptyPmsPata) {
		if (connectWifi()) {
			if (!httpSent && sendDataToHttp()) {
				httpSent = true;
			}
		}

		if (httpSent) {
			timers.timeoutTimer(Duration::Seconds(5), disconnectWifi);
			processingEnd = true;
		} else {
			if (isTimeout(retryTimeout, Duration::Minutes(1))) {
				logger.logError("Unable to process weather data");
				processingEnd = true;
			}
		}

		if (processingEnd) {
			httpSent = false;
			lastPmsData.print(Serial);
			clearWeatherData();
		}
	}
}

void printData() {
	if (emptyPmsPata == lastPmsData) {
		return;
	}
	logger.logInfo("PM2.5: %u, PM10: %u", lastPmsData.getPm25(),
			lastPmsData.getPm10());
	logger.logInfo("Temp: %f, RH: %f", lastSiData.getTemp(),
			lastSiData.getRh());

	clearWeatherData();
}

void setup() {
	pinMode(PMS_SET_PIN, OUTPUT);

	Serial.begin(9600);
	pmsSerial.begin(9600);

	WiFi.persistent(false);

	timers.timeoutTimer(Duration::Seconds(20), firstGatherWeatherData);
	timers.intervalTimer(Duration::Seconds(5), processWeatherData);
	//timers.intervalTimer(Duration::Seconds(5), printData);
}

void loop() {
	timers.tick();

	delay(100);
}

