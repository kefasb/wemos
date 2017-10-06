/*
 * HttpClient.h
 *
 * Author: Piotr Borkowski
 */

#ifndef HTTPCLIENT_HTTPCLIENT_H_
#define HTTPCLIENT_HTTPCLIENT_H_

#include <IHttpConnectionData.h>
#include "Client.h"
#include "ILogger.h"

class HttpClient {
public:
    HttpClient(Client& client, IHttpConnectionData& connectionData, ILogger& logger);
    virtual ~HttpClient();

    bool sendGetRequest(uint8_t fake = 0, ...);

private:
    const Client& client;
    const IHttpConnectionData& connectionData;
    const ILogger& logger;
};

#endif /* HTTPCLIENT_HTTPCLIENT_H_ */
