/*
 * PersistBuffer.cpp
 *
 *  Created on: 24 Σεπ 2018
 *      Author: Synodiporos
 */

#include "PersistBuffer.h"

PersistBuffer* PersistBuffer::instance = nullptr;

PersistBuffer::PersistBuffer() {
	// TODO Auto-generated constructor stub

}

PersistBuffer::~PersistBuffer() {
	// TODO Auto-generated destructor stub
}

PersistBuffer* PersistBuffer::getInstance(){
	if(!instance)
		instance = new PersistBuffer();
	return instance;
}

void PersistBuffer::initialize(){
	this->size = EEPROM.read(PB_START_INDEX);
	this->index = EEPROM.read(PB_START_INDEX + 1);
}

uint8_t PersistBuffer::getSize(){
	return this->size;
}

bool PersistBuffer::isEmpty(){
	return this->size==0;
}

uint8_t PersistBuffer::push(Surge &surge){
	uint8_t size = getSize();
	uint8_t i = 0;
	if(size<PB_CAPACITY){
		i = index + size;
		if(i>=PB_CAPACITY)
			i = i % PB_CAPACITY;

		setSize(getSize()+1);
		return write(i, surge);
	}
	else{
		i = this->index;
		write(i, surge);

		i++;
		if(i<PB_CAPACITY)
			return setIndex(i);
		else
			return setIndex(0);
	}
}

uint8_t PersistBuffer::getAt(uint8_t index, Surge& surge){
	uint8_t size = getSize();
	if(index<size){
		uint8_t i = index + this->index;
		if(i>=PB_CAPACITY)
			i = i % PB_CAPACITY;
		return read(i, surge);
	}
	return 0;
}

uint8_t PersistBuffer::top(Surge &surge){
	if(!isEmpty()){
		return read(this->index, surge);
	}
	return 0;
}

uint8_t PersistBuffer::pop(){
	if(!isEmpty()){
		uint8_t size = getSize();
		if(size>1){
			setIndex(this->index + 1);
			setSize(getSize() - 1);
		}
		else{
			//Optional
			setIndex(0);
			setSize(0);
		}
		return 1;
	}
	return 0;
}

void PersistBuffer::clear(){
	setSize(0);
	setIndex(0);
}

void PersistBuffer::print(){
	Serial.print(F("BUFFER["));
	Serial.print(this->index);
	Serial.print(",");
	Serial.print(getSize());
	Serial.println(F("]"));
}

bool PersistBuffer::setIndex(uint8_t index){
	uint8_t i = index;
	if(index>=PB_CAPACITY)
		i = index % PB_CAPACITY;
	if(this->index!=i){
		this->index = i;
		onIndexChanged();
		return true;
	}
	return false;
}

bool PersistBuffer::setSize(uint8_t size){
	if(size>PB_CAPACITY)
		return false;
	if(this->size!=size){
		this->size = size;
		onSizeChanged();
		return true;
	}
	return false;
}

void PersistBuffer::onIndexChanged(){
	EEPROM.update(PB_START_INDEX+1, this->index);
}

void PersistBuffer::onSizeChanged(){
	EEPROM.update(PB_START_INDEX, this->size);
}

uint8_t PersistBuffer::write(uint8_t index, Surge &surge){
	uint8_t address = index * sizeof(surge);
	const byte* p = (const byte*)(const void*)&surge;
	unsigned int i;
	for (i = 0; i < sizeof(surge); i++)
		  EEPROM.write(address++, *p++);
	return i;
}

uint8_t PersistBuffer::read(uint8_t index, Surge &surge){
	uint8_t address = index * sizeof(surge);
	byte* p = (byte*)(void*)&surge;
	unsigned int i;
	for (i = 0; i < sizeof(surge); i++)
		  *p++ = EEPROM.read(address++);
	return i;
}
