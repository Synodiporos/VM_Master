/*
 * PostSurgeRequest.h
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef WIFI_POSTSURGEREQUEST_H_
#define WIFI_POSTSURGEREQUEST_H_

#include <stdint.h>
#include "HttpRequest.h"

class PostSurgeRequest : public HttpRequest{
public:
	PostSurgeRequest(uint8_t source,
			unsigned long charge, unsigned int slope);
	virtual ~PostSurgeRequest();

	std::string getRequest();

private:
	uint8_t source ;
	unsigned long charge ;
	unsigned int slope ;
};

#endif /* WIFI_POSTSURGEREQUEST_H_ */
