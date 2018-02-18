#ifndef PROCESSESMANAGER__H
#define PROCESSESMANAGER__H

#include <iostream>
#include <string>
#include <list>
#include "Process.h"
//#include "disk_drive.h"
#include <map>

class ProcessesManager {
public:
	std::list<std::list<PCB*>>allProcesses{};
	std::list<PCB*>waitingProcesses{};
	std::list<PCB*>list{};
	std::list<PCB*>readyProcesses{};
	ProcessesManager(); 
	void createProcess(std::string fileName, int GID);
	void createProcess(std::string fileName, int GID, int AddidtionalSpace);

	void killProcess(int PID);
	void displayAllProcesses();
	void displayWaitingProcesses();
	void displayReadyProcesses();
	PCB * findPCBbyPID(int PID);
	std::list<PCB*> GiveReadyProcessesList();
	std::list<PCB*> GiveWaitingProcessesList();
	std::list<std::list<PCB*>> getAllProcesseslist();
	void AddProcessToReady(PCB*);
	void RemoveProcessFromReady(PCB*);
	void AddProcessToWaiting(PCB*);
	void RemoveProcessFromWaiting(PCB*);
};
#endif PROCESSESMANAGER__H