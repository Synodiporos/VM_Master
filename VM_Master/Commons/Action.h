/*
 * Action.h
 *
 *  Created on: 29 Μαΐ 2018
 *      Author: Synodiporos
 */

#ifndef COMMONS_ACTION_H_
#define COMMONS_ACTION_H_

class Action {
public:
	Action();
	Action(void* source, unsigned int actionId,
			char* actionName, void* container);
	virtual ~Action();
	void setSource(void* source);
	void* getSource();
	void setContainer(void* container);
	void* getContainer();
	void setActionId(unsigned int actionId);
	unsigned int getActionId();
	void setActionName(char* name);
	char* getActionName();

private:
	void* source = nullptr;
	void* container = nullptr;
	unsigned int actionId = 0;
	char* actionName = nullptr;
};

#endif /* COMMONS_ACTION_H_ */
