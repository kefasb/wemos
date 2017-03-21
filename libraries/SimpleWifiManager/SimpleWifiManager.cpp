/*
 * SimpleWifiManager.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "SimpleWifiManager.h"

void SimpleWifiManager::initialize() {
    this->wifi.persistent(false);
    this->ssid[0] = 0;
    this->pass[0] = 0;
}

SimpleWifiManager::SimpleWifiManager(ESP8266WiFiClass& wifi, const Logger& logger) :
        wifi(wifi), logger(logger) {
    initialize();
}

SimpleWifiManager::~SimpleWifiManager() {
}

bool SimpleWifiManager::disconnect(bool off) {
    bool disconnected = wifi.disconnect(off);
    if (disconnected) {
        logger.logInfo("WiFi disconnected");
    } else {
        logger.logError("Unable to disconnect WiFi");
    }
    return disconnected;
}

bool SimpleWifiManager::disconnect() {
    return disconnect(false);
}

bool SimpleWifiManager::disconnectAndOff() {
    return disconnect(true);
}

bool SimpleWifiManager::settingsChanged(const char* ssid, const char* pass) const {
    return strcmp(this->ssid, ssid) || strcmp(this->pass, pass);
}

void SimpleWifiManager::configureAndConnectWifi(const char* ssid, const char* pass) {
    wifi.mode(WIFI_STA);
    /**
     * It was intended to call {@code wifi.begin()} without arguments when
     * settings not changed. However not worked at sight.
     * TODO to be investigated
     */
    if (!settingsChanged(ssid, pass)) {
        logger.logDebug("Same WiFi settings");
        wifi.begin(ssid, pass);
    } else {
        logger.logDebug("New WiFi settings");
        strcpy(this->ssid, ssid);
        strcpy(this->pass, pass);
        wifi.begin(ssid, pass);
    }
}

bool SimpleWifiManager::connect(const char* ssid, const char* pass, uint32_t timeout) {
    if (isConnected()) {
        return true;
    }

    bool result = false;
    logger.logInfo("Connecting to WiFi");
    configureAndConnectWifi(ssid, pass);
    TimeoutTimer connectionTimer = TimeoutTimer(timeout);
    while (!isConnected() && connectionTimer.isRunning()) {
        delay(500);
        logger.logInfo(".");
        connectionTimer.tick();
    }

    if (isConnected()) {
        logger.logInfo("WiFi connected");
        result = true;
    } else {
        logger.logError("Unable to connect to WiFi");
        disconnect();
    }

    return result;
}

bool SimpleWifiManager::isConnected() const {
    return wifi.isConnected();
}

