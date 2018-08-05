/*
 * IActionListener.h
 *
 *  Created on: 7 Απρ 2018
 *      Author: Synodiporos
 */

#ifndef COMMONS_IACTIONLISTENER_H_
#define COMMONS_IACTIONLISTENER_H_
#include "Action.h"

class IActionListener {
public:
	IActionListener();
	virtual ~IActionListener();

	virtual void actionPerformed(Action action) = 0;
};

#endif /* COMMONS_IACTIONLISTENER_H_ */
