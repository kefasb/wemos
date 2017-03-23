#include <BlynkSimpleEsp8266.h>

#include "Duration.h"
#include "Logger.h"

#include "SimpleWifiManager.h"

#include "Pms3003.h"
#include "PmsMeasurement.h"
#include "EmptyData.h"
#include "PmsData.h"

#include "Timers.h"

uint32_t startTime;

/* PMS settings */
const uint8_t PMS_SET_PIN = D3;
const uint32_t PMS_TIMER = Duration::Minutes(4);
Logger pmsLogger(Serial, "Pms3003", INFO);
Pms3003 pms3003(Serial, PMS_SET_PIN, pmsLogger);
PmsData lastPmsData = EmptyData();

/* WiFi settings */
const char ssid[] = "xxx";
const char pass[] = "xxx";

/* Blynk settings */
const uint8_t BLYNK_PM25_DISPLAY = V20;
const uint8_t BLYNK_PM10_DISPLAY = V21;
const uint8_t BLYNK_PREVIOUS_DISPLAY = V22;
const char authToken[] = "xxx";

/* Wifi */
Logger simpleWifiManagerLogger(Serial, "SimpleWifiManger", INFO);
SimpleWifiManager wifiManager = SimpleWifiManager(WiFi, simpleWifiManagerLogger);

/* Other */
Timers timers;

bool connectWifi() {
    return wifiManager.connect(ssid, pass);
}

void disconnectWifi() {
    wifiManager.disconnectAndOff();
}

bool connectBlynk() {
    Blynk.config(authToken);
    return Blynk.connect();
}

bool connect() {
    bool connected = false;
    if (connectWifi()) {
        if (Blynk.connected()) {
            if (Blynk.run()) {
                connected = true;
            }
        } else {
            connectBlynk();
        }
    }
    return connected;
}

PmsData readPms() {
    PmsMeasurement pmsMeasurement = PmsMeasurement(pms3003);
    PmsData pmsData = pmsMeasurement.measure();
    if (pmsData == EmptyData()) {
        Serial.println("No data received");
    }

    return pmsData;
}

bool isTimeout(uint32_t timer, uint32_t length) {
    return millis() - timer >= length;
}

void resetTimer(uint32_t& timer) {
    timer = millis();
}

uint32_t retryTimeout;

void gatherPmsData() {
    lastPmsData = readPms();
    resetTimer(retryTimeout);
}

void firstGatherPmsData() {
    gatherPmsData();
    timers.intervalTimer(PMS_TIMER, gatherPmsData);
}

void sendDataToBlynk() {
    Blynk.virtualWrite(BLYNK_PM25_DISPLAY, lastPmsData.getPm25());
    Blynk.virtualWrite(BLYNK_PM10_DISPLAY, lastPmsData.getPm10());
}

void processPmsData() {
    bool processingEnd = false;
    if (lastPmsData != EmptyData()) {
        if (connect()) {
            sendDataToBlynk();
            timers.timeoutTimer(Duration::Seconds(3), disconnectWifi);
            processingEnd = true;
        } else {
            if (isTimeout(retryTimeout, Duration::Minutes(1))) {
                Serial.println("Unable to process pms data");
                processingEnd = true;
            }
        }

        if (processingEnd) {
            lastPmsData.print(Serial);
            lastPmsData = EmptyData();
        }
    }
}

void setup() {
    pinMode(PMS_SET_PIN, OUTPUT);

    Serial.begin(9600);

    startTime = millis();

    timers.timeoutTimer(Duration::Seconds(20), firstGatherPmsData);
    timers.intervalTimer(Duration::Seconds(1), processPmsData);
}

void loop() {
    timers.tick();

    delay(100);
}

