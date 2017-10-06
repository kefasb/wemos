#ifndef _CONNECTION_DATA_H
#define _CONNECTION_DATA_H

#include "IHttpConnectionData.h"

struct HttpConnectionData: public IHttpConnectionData {
    const char* blynkAuth = "";

private:
    const char* httpAuth = "";
    const char* httpHost = "";
    const uint16_t httpPort = 80;
    const char* httpUrlPattern = "";

public:
    virtual const char* getHttpHost() const {
        return httpHost;
    }

    virtual uint16_t getHttpPort() const {
        return httpPort;
    }

    virtual const char* getUrlPattern() const {
        return httpUrlPattern;
    }
};

#endif /* _CONNECTION_DATA_H */
