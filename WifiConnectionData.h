/*
 * WifiConnectionData.h
 *
 * Author: Piotr Borkowski
 */

#ifndef WIFICONNECTIONDATA_H_
#define WIFICONNECTIONDATA_H_

struct WifiConnectionData: public IWifiConnectionData {
private:
    const char* ssid = "";
    const char* pass = "";

public:
    const char* getSsid() const {
        return ssid;
    }

    const char* getPass() const {
        return pass;
    }

};

#endif /* WIFICONNECTIONDATA_H_ */
