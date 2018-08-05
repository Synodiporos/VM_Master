/*
 * IStateListener.h
 *
 *  Created on: 27 Ξ�Ξ±Ο� 2018
 *      Author: Synodiporos
 */

#ifndef ISTATELISTENER_H_
#define ISTATELISTENER_H_
#include "State.h"

class IStateListener {
public:
	IStateListener();
	virtual ~IStateListener();
	virtual void stateChanged(State* state) = 0;
};

#endif /* ISTATELISTENER_H_ */
