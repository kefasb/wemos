/*
 * SimpleWifiManager.h
 *
 * Author: Piotr Borkowski
 *
 * Wraps Esp8266 Wifi libraries to facilitate WiFi management.
 */

#ifndef SIMPLEWIFIMANAGER_SIMPLEWIFIMANAGER_H_
#define SIMPLEWIFIMANAGER_SIMPLEWIFIMANAGER_H_

#include <ESP8266WiFi.h>
#include "Duration.h"
#include "TimeoutTimer.h"
#include "IWifiConnectionData.h"
#include "ILogger.h"
#include "NullLogger.h"

class SimpleWifiManager {
public:
    /**
     * Creates wifi manager. Uses provided logger for logging.
     * If no logger provided it does not log anything.
     * @param wifi WiFi object to be handled
     * @param wifiData Data necessary to establish connection
     * @param logger (@link Logger} to be used for logging
     */
    SimpleWifiManager(ESP8266WiFiClass& wifi, const IWifiConnectionData& wifiData,
            const ILogger& logger = DefaultNullLogger);

    /**
     * destructor
     */
    virtual ~SimpleWifiManager();

    /**
     * Connects to wifi.
     * Tries to connect within given timeout (default 1 minute).
     * @return true when successfully connected, false otherwise.
     */
    bool connect(uint32_t timeout = Duration::Minutes(1));

    /**
     * Disconnects from wifi but does NOT turn wifi off.
     * @return true if successfully disconnected, false otherwise
     */
    bool disconnect();

    /**
     * Disconnects from wifi AND turns wifi off.
     * @return true if successfully disconnected, false otherwise
     */
    bool disconnectAndOff();

    /**
     * Checks whether connected to wifi.
     * @return true when connected to wifi, false otherwise.
     */
    bool isConnected() const;

private:
    ESP8266WiFiClass& wifi;
    const IWifiConnectionData& wifiData;
    const ILogger& logger;

    /**
     * Connects to wifi using given credentials.
     * Tries to connect within given timeout (default 1 minute).
     * @return true when successfully connected, false otherwise.
     */
    bool connect(const char *ssid, const char *pass, uint32_t timeout = Duration::Minutes(1));

    bool disconnect(bool off);
    void configureAndConnectWifi(const char* ssid, const char* pass);
};

#endif /* SIMPLEWIFIMANAGER_SIMPLEWIFIMANAGER_H_ */
