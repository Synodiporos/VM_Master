/*
 * PostSurgeRequest.cpp
 *
 *  Created on: 8 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PostSurgeRequest.h"

PostSurgeRequest::PostSurgeRequest(uint8_t source,
			unsigned long charge, unsigned int slope):
			HttpRequest(),
			source(source),
			charge(charge),
			slope(slope){

}

PostSurgeRequest::~PostSurgeRequest() {
	// TODO Auto-generated destructor stub
}

std::string PostSurgeRequest::getRequest(){
	char at[36];
	sprintf (at, "source=%d&charge=%lu&slope=%d",
			source, charge, slope);

	return string(at);
}
