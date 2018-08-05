/*
 * Timer.h
 *
 *  Created on: 9 Ιουν 2018
 *      Author: Synodiporos
 */

#ifndef SYSTEM_TIMER_H_
#define SYSTEM_TIMER_H_
#include "../Commons/IActionListener.h"
#include "../Commons/Action.h"
#include <stdint.h>

#define STARTED 2
#define STOPED 0
#define PAUSED 1

class Timer {
public:
	static const unsigned short int TIMER_START = 1;
	static const unsigned short int TIMER_STOP = 2;
	static const unsigned short int TIMER_PAUSE = 3;
	static const unsigned short int TIMER_TIC = 4;

	Timer();
	Timer(unsigned long interval, unsigned int iterations);
	Timer(unsigned long interval, unsigned int iterations, unsigned int actionId);
	virtual ~Timer();

	void start();
	void pause();
	void stop();

	void setActionId(unsigned int actionId);
	unsigned int getActionId();
	void setInterval(unsigned long interval);
	unsigned long getInterval();
	void setIterations(unsigned int iterations);
	unsigned int getIterations();
	unsigned int getIterationsPerformed();
	unsigned long getMillisPassed();
	uint8_t getState();

	void setActionListener(IActionListener* listener);
	IActionListener* getActionListener();
	void validate();


private:
	IActionListener* actionListener = nullptr;
	uint8_t state = STOPED;
	unsigned int actionId = 0;
	unsigned long interval = 0;
	unsigned long startTime = 0;
	unsigned long millisPassed = 0;

	unsigned int iterations = 1;
	unsigned int iterPerf = 0;
	void notifyActionPerformed(unsigned short int act);
	void updateStartTime();
	void resetIterations();
	void onAction();
};

#endif /* SYSTEM_TIMER_H_ */
