/*
 * State.h
 *
 *  Created on: 22 Ξ‘Ο€Ο� 2018
 *      Author: Synodiporos
 */

#ifndef COMMONS_STATE_H_
#define COMMONS_STATE_H_
#include <string>

class State {
public:
	State();
	State(void* source, char name, void* value);
	virtual ~State();

	void setSource(void* source);
	void* getSource();
	void setName(char name);
	char getName();
	void setValue(void* value);
	void* getValue();

private:
	void* source = nullptr;
	char name = 0;
	void* value = nullptr;
};

#endif /* COMMONS_STATE_H_ */
