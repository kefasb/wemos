/*
 * SimpleWifiManager.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "SimpleWifiManager.h"

SimpleWifiManager::SimpleWifiManager(ESP8266WiFiClass& wifi, const IWifiConnectionData& wifiData,
        const ILogger& logger) :
        wifi(wifi), wifiData(wifiData), logger(logger) {
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

void SimpleWifiManager::configureAndConnectWifi(const char* ssid, const char* pass) {
    wifi.mode(WIFI_STA);
    /**
     * It was intended to call {@code wifi.begin()} without arguments when
     * settings not changed. However not worked at sight.
     * TODO to be investigated
     */
    wifi.begin(ssid, pass);
}

bool SimpleWifiManager::connect(const char* ssid, const char* pass, uint32_t timeout) {
    if (isConnected()) {
        return true;
    }

    bool result = false;
    logger.logInfo("Connecting to WiFi");
    configureAndConnectWifi(ssid, pass);
    TimeoutTimer connectionTimer = TimeoutTimer(timeout);
    connectionTimer.start();
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

bool SimpleWifiManager::connect(uint32_t timeout) {
    return connect(wifiData.getSsid(), wifiData.getPass(), timeout);
}

bool SimpleWifiManager::isConnected() const {
    return wifi.isConnected();
}

