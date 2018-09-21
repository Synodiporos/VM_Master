/*
 * Action.cpp
 *
 *  Created on: 29 Ξ�Ξ±Ξ� 2018
 *      Author: Synodiporos
 */

#include "Action.h"

Action::Action() {
	// TODO Auto-generated constructor stub

}

Action::Action(const void* source, const unsigned int actionId,
		const char* actionName, const void* container):
			source(source),
			actionId(actionId),
			actionName(actionName),
			container(container){
}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

const void* Action::getSource(){
	return source;
}

const void* Action::getContainer(){
	return container;
}

unsigned int Action::getActionId(){
	return actionId;
}

const char* Action::getActionName(){
	return actionName;
}

