/*
 * IHttpConnectionData.h
 *
 * Author: Piotr Borkowski
 */

#ifndef HTTPCLIENT_IHTTPCONNECTION_H_
#define HTTPCLIENT_IHTTPCONNECTION_H_

#include <stdint.h>

class IHttpConnectionData {
public:
    virtual ~IHttpConnectionData() {
    }

    virtual const char* getHttpHost() const=0;
    virtual uint16_t getHttpPort() const=0;
    virtual const char* getUrlPattern() const=0;
};

#endif /* HTTPCLIENT_IHTTPCONNECTION_H_ */
