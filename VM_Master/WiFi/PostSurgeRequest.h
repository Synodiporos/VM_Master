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
	PostSurgeRequest(uint8_t source,
			unsigned long charge, unsigned int slope);
	virtual ~PostSurgeRequest();

	char* getRequest();

	unsigned long foo1();
	unsigned long foo2();
	unsigned long foo3();
	unsigned long foo4();
	unsigned long foo5();
	unsigned long foo6();
	unsigned long foo7();


private:

	uint8_t source ;
	unsigned long charge ;
	unsigned int slope ;
};

#endif /* WIFI_POSTSURGEREQUEST_H_ */
