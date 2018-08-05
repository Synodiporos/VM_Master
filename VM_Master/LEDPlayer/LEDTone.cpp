/*
 * LEDTone.cpp
 *
 *  Created on: 4 Ιουλ 2018
 *      Author: Synodiporos
 */

#include "LEDTone.h"

LEDTone::LEDTone(uint8_t frequency,
			unsigned short int duration) {
	setFrequency(frequency);
	setDuration(duration);
}

LEDTone::LEDTone(uint8_t frequency,
		unsigned short int duration,
		LEDTone* next){
	setFrequency(frequency);
	setDuration(duration);
	setNextTone(next);
}

LEDTone::~LEDTone() {
	//delete this->next;
}

void LEDTone::setFrequency(uint8_t frequency){
	this->frequency = frequency;
}

uint8_t LEDTone::getFrequency(){
	return this->frequency;
}

unsigned short int LEDTone::getDuration(){
	return this->duration;
}

void LEDTone::setDuration(unsigned short int duration){
	this->duration = duration;
}

void LEDTone::setNextTone(LEDTone* next){
	this->next = next;
}

LEDTone* LEDTone::getNextTone(){
	return this->next;
}

bool LEDTone::hasNext(){
	return this->next!=0;
}
