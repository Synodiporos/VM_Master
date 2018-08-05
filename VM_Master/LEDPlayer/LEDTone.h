/*
 * LEDTone.h
 *
 *  Created on: 4 Ιουλ 2018
 *      Author: Synodiporos
 */

#ifndef LEDPLAYER_LEDTONE_H_
#define LEDPLAYER_LEDTONE_H_
#include <stdint.h>

class LEDTone {
public:
	LEDTone(uint8_t frequency,
			unsigned short int duration);
	LEDTone(uint8_t frequency,
			unsigned short int duration,
			LEDTone* next);
	~LEDTone();

	void setFrequency(uint8_t frequency);
	uint8_t getFrequency();
	unsigned short int getDuration();
	void setDuration(unsigned short int duration);
	void setNextTone(LEDTone* next);
	LEDTone* getNextTone();
	bool hasNext();

private:
	uint8_t frequency = 0;
	//Duration in Seconds.
	unsigned short int duration = 0;
	LEDTone* next = 0;

};

#endif /* LEDPLAYER_LEDTONE_H_ */
