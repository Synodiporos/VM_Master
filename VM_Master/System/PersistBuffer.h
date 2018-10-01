/*
 * PersistBuffer.h
 *
 *  Created on: 24 Σεπ 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_PERSISTBUFFER_H_
#define SYSTEM_PERSISTBUFFER_H_

#include <Arduino.h>
#include <EEPROM.h>

#define PB_START_INDEX 317
#define PB_CAPACITY 64

struct Surge{
	uint32_t datetime;
	uint8_t device;
	uint32_t charge;
	uint16_t slope;
};

class PersistBuffer {
public:
	static PersistBuffer* getInstance();
	virtual ~PersistBuffer();
	void initialize();
	uint8_t getSize();
	bool isEmpty();
	uint8_t push(Surge &surge);
	uint8_t getAt(uint8_t index, Surge& surge);
	uint8_t top(Surge &surge);
	uint8_t pop();
	void clear();
	void print();

private:
	static PersistBuffer* instance;
	uint8_t index = 0;
	uint8_t size = 0;

	PersistBuffer();
	bool setIndex(uint8_t index);
	bool setSize(uint8_t size);
	void onIndexChanged();
	void onSizeChanged();
	uint8_t write(uint8_t index, Surge &surge);
	uint8_t read(uint8_t index, Surge &surge);
};

#endif /* SYSTEM_PERSISTBUFFER_H_ */
