/*
 * Action.h
 *
 *  Created on: 29 Ξ�Ξ±Ξ� 2018
 *      Author: Synodiporos
 */

#ifndef COMMONS_ACTION_H_
#define COMMONS_ACTION_H_

class Action {
public:
	Action();
	Action(const void* source, const unsigned int actionId,
			const char* actionName, const void* container);
	virtual ~Action();
	const void* getSource();
	const void* getContainer();
	unsigned int getActionId();
	const char* getActionName();

private:
	const void* source = nullptr;
	const unsigned int actionId = 0;
	const char* actionName = nullptr;
	const void* container = nullptr;
};

#endif /* COMMONS_ACTION_H_ */
