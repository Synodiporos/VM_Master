/*
 * PostSurgeRequest.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_POSTSURGEREQUEST_H_
#define WIFI_POSTSURGEREQUEST_H_

#include "HttpRequest.h"

//#define POST_SURGE_REQUEST "POST %s%s HTTP/1.1\r\nHost: %s\r\nAccept: */*\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n%s"
//#define POST_SURGE_REQUEST_DATA "source=%d&charge=%lu&slope=%d"

class PostSurgeRequest : public HttpRequest{
public:
	PostSurgeRequest(uint32_t datetime, uint8_t source,
			uint32_t charge, uint16_t slope);
	virtual ~PostSurgeRequest();

	uint8_t getRequestType();
	uint8_t createRequestContent(char* buffer);

private:
	uint32_t datetime;
	uint8_t source ;
	uint32_t charge ;
	uint16_t slope ;
};

#endif /* WIFI_POSTSURGEREQUEST_H_ */
