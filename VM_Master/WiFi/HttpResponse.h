/*
 * HttpResponse.h
 *
 *  Created on: Oct 11, 2018
 *      Author: sgeorgiadis
 */

#ifndef WIFI_HTTPRESPONSE_H_
#define WIFI_HTTPRESPONSE_H_

#include <stdint.h>
using namespace std;

#define HR_CONTENT_TYPE_HTML "text/html"
#define HR_CONTENT_TYPE_JSON "application/json"
#define HR_CONTENT_TYPE_CSV "text/csv"
#define HR_CONTENT_TYPE_TEXT "text/plain"
#define HR_CONTENT_TYPE_OTHER ""

#define HR_CONTENT_TYPE_HTML_CODE 1
#define HR_CONTENT_TYPE_JSON_CODE 2
#define HR_CONTENT_TYPE_CSV_CODE 3
#define HR_CONTENT_TYPE_TEXT_CODE 4
#define HR_CONTENT_TYPE_OTHER_CODE 5

class HttpResponse {
public:
	HttpResponse();
	HttpResponse(uint16_t http_code, uint8_t content_type,
			uint16_t content_lenght, const char content[]);
	virtual ~HttpResponse();

	void setHttpCode(uint16_t code);
	void setContentType(uint8_t type);
	void setContentLenght(uint16_t lenght);
	void setContent(char content[]);

	uint16_t getHttpCode();
	uint8_t getContentType();
	uint16_t getContentLenght();
	const char* getContent();

private:
	uint16_t http_code = 404;
	uint8_t content_type = 0;
	uint16_t content_lenght = 0;
	char content[64];
};

#endif /* WIFI_HTTPRESPONSE_H_ */
