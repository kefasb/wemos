/*
 * IWifiConnectionData.h
 *
 * Author: Piotr Borkowski
 */

#ifndef SIMPLEWIFIMANAGER_IWIFICONNECTIONDATA_H_
#define SIMPLEWIFIMANAGER_IWIFICONNECTIONDATA_H_

class IWifiConnectionData {
public:
    virtual ~IWifiConnectionData() {
    }

    virtual const char* getSsid() const=0;
    virtual const char* getPass() const=0;
};

#endif /* SIMPLEWIFIMANAGER_IWIFICONNECTIONDATA_H_ */
