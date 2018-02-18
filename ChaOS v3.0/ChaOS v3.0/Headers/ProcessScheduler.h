#ifndef PROCESSSCHEDULER__H
#define PROCESSSCHEDULER__H

#include "ProcessesManager.h"
#include "Process.h"
#include <iostream>
#include <list>

class ProcessScheduler {
private:
	//zmienna pomocnicza, potrzebna podczas wybierania procesu o najkr�tszym czasie
	std::list<PCB*>::iterator iteratorToMinElement;
	//zmienna pomocnicza do zliczania instrukcji wykonanych przez ActiveProcess
	short instructions{ 0 };
	//Procedura wywo�ywana w RunProcess(), odpowiedzialna za ustawianie ActiveProcess metod� SRT
	void SRTSchedulingAlgorithm();
public:
	//Procedura wywo�ywana przed ka�dym wykonaniem instrukcji ActiveProcess - z jej poziomu wywo�ywany jest planista oraz metoda DoCommand() interpretera
	void RunProcess();
	void RunProcess(int);
};
#endif PROCESSSCHEDULER__H