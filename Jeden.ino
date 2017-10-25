#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>

#include "Duration.h"
#include "Logger.h"

#include "SimpleWifiManager.h"
#include "WifiConnectionData.h"

#include "PmsX003.h"
#include "PmsMeasurement.h"
#include "EmptyData.h"
#include "PmsData.h"

#include "Timers.h"

#include "HttpClient.h"
#include "HttpConnectionData.h"

/* PMS settings */
const uint8_t PMS_SET_PIN = D7;
const uint32_t PMS_READ_INTERVAL = Duration::Minutes(4);
Logger pmsLogger(Serial, "PmsX003", INFO);
SoftwareSerial pmsSerial(D5, D6, false, 256);
PmsX003 pmsX003(pmsSerial, PMS_SET_PIN, pmsLogger);
PmsData lastPmsData = EmptyData();

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
Timers timers;

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
    timers.intervalTimer(PMS_READ_INTERVAL, gatherPmsData);
}

bool sendDataToHttp() {
    if (!client.connect(httpConnectionData.getHttpHost(), httpConnectionData.getHttpPort())) {
        Serial.println("Http connection failed");
        return false;
    }

    HttpClient http(client, httpConnectionData, httpLogger);
    http.sendGetRequest(0, 2, 0, lastPmsData.getPm25(), lastPmsData.getPm10());
    return true;
}

void processPmsData() {
    static bool httpSent = false;
    bool processingEnd = false;
    if (lastPmsData != EmptyData()) {
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
                Serial.println("Unable to process pms data");
                processingEnd = true;
            }
        }

        if (processingEnd) {
            httpSent = false;
            lastPmsData.print(Serial);
            lastPmsData = EmptyData();
        }
    }
}

void printData() {
    if (EmptyData() == lastPmsData) {
        return;
    }
    Serial.print("Pms data: ");
    Serial.print("PM2.5: ");
    Serial.print(lastPmsData.getPm25());
    Serial.print("PM10: ");
    Serial.print(lastPmsData.getPm10());
    Serial.println();

    lastPmsData = EmptyData();
}

void setup() {
    pinMode(PMS_SET_PIN, OUTPUT);

    Serial.begin(9600);
    pmsSerial.begin(9600);

    WiFi.persistent(false);

    timers.timeoutTimer(Duration::Seconds(20), firstGatherPmsData);
    timers.intervalTimer(Duration::Seconds(5), processPmsData);
    //timers.intervalTimer(Duration::Seconds(5), printData);
}

void loop() {
    timers.tick();

    delay(100);
}

