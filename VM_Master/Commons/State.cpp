/*
 * State.cpp
 *
 *  Created on: 22 Απρ 2018
 *      Author: Synodiporos
 */

#include "State.h"

State::State() {
	// TODO Auto-generated constructor stub

}

State::State(void* source, char name, void* value){
	this->source = source;
	this->name = name;
	this->value = value;
}

State::~State() {
	// TODO Auto-generated destructor stub
}

void State::setSource(void* source){
	this->source = source;
}

void* State::getSource(){
	return this->source;
}

void State::setName(char name){
	this->name = name;
}

char State::getName(){
	return this->name;
}

void State::setValue(void* value){
	this->value = value;
}
void* State::getValue(){
	return this->value;
}
