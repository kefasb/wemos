/*
 * HttpClient.cpp
 *
 * Author: Piotr Borkowski
 */

#include "HttpClient.h"

HttpClient::HttpClient(Client& client, IHttpConnectionData& connectionData, ILogger& logger) :
        client(client), connectionData(connectionData), logger(logger) {
}

HttpClient::~HttpClient() {
}

bool HttpClient::sendGetRequest(uint8_t fake, ...) {
    char url[200];
    const char* urlPattern = connectionData.getUrlPattern();
    va_list args;
    va_start(args, fake);
    sprintf(url, urlPattern, args);
    va_end(args);

    char request[300];
    const char* requestPattern = "GET %s HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";
    sprintf(request, requestPattern, url, connectionData.getHttpHost());

    logger.logDebug("Request: %s", request);
    const_cast<Client&>(client).print(request);

    return true;
}
