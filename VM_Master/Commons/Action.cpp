/*
 * Action.cpp
 *
 *  Created on: 29 Μαΐ 2018
 *      Author: Synodiporos
 */

#include "Action.h"

Action::Action() {
	// TODO Auto-generated constructor stub

}

Action::Action(void* source, unsigned int actionId,
			char* actionName, void* container){
	this->source = source;
	this->actionId = actionId;
	this->actionName = actionName;
	this->container = container;
}

Action::~Action() {
	// TODO Auto-generated destructor stub
}

void Action::setSource(void* source){
	this->source = source;
}

void* Action::getSource(){
	return source;
}

void Action::setContainer(void* container){
	this->container = container;
}

void* Action::getContainer(){
	return container;
}

void Action::setActionId(unsigned int actionId){
	this->actionId = actionId;
}

unsigned int Action::getActionId(){
	return actionId;
}

void Action::setActionName(char* name){
	this->actionName = name;
}

char* Action::getActionName(){
	return actionName;
}

