/*
 * LEDTonePlayer.h
 *
 *  Created on: Jul 4, 2018
 *      Author: sgeorgiadis
 */

#ifndef LEDPLAYER_LEDTONEPLAYER_H_
#define LEDPLAYER_LEDTONEPLAYER_H_
#include "LEDTone.h"

class LEDTonePlayer {
public:
	LEDTonePlayer(int8_t _pinNumber);
	LEDTonePlayer(int8_t _pinNumber,
			LEDTone* headTone);
	LEDTonePlayer(int8_t _pinNumber,
			LEDTone* headTone, short int iterations);
	virtual ~LEDTonePlayer();
	void initialize();
	int8_t getPinNumber();
	void setIterations(short int iterations);
	short int getIterations();
	void setHeadTone(LEDTone* headTone);
	uint8_t getState();
	LEDTone* getHeadTone();
	LEDTone* getCurrentTone();
	void play();
	void pause();
	void stop();
	void playTone(LEDTone* tone);
	void validate();

private:
	int8_t _pinNumber = -1;
	LEDTone* _headTone = nullptr;
	short int _iterations = 1;
	short int _performedIter = 0;
	unsigned long int _millis = 0;
	unsigned short int _interval = 0;
	LEDTone* _currentTone = _headTone;
	//0=stop, 1=pause, 2=play
	uint8_t _state = 0;

	void playNextTone();
	void resumeFromCurrent();
	void playCurrentTone();
};

#endif /* LEDPLAYER_LEDTONEPLAYER_H_ */
