#include "../Headers/ProcessScheduler.h"
#include "../Headers/Interpreter.h"
#include <list>

extern PCB* ActiveProcess;
extern ProcessesManager *pm;
extern Interpreter* i;

void ProcessScheduler::RunProcess(int count)
{
	for (int i = 0; i < count; i++)
	{
		RunProcess();
	}
}

void ProcessScheduler::RunProcess()
{
	if (ActiveProcess == nullptr || ActiveProcess->GetState()!=State::Ready || ActiveProcess->wait)
	{
		ActiveProcess = pm->findPCBbyPID(1);
		SRTSchedulingAlgorithm();
	}

	else
	{
		//Sprawdzenie, czy wyst�pi� jaki� b��d lub proces zako�czy� si� wykonywa�
		if (ActiveProcess->errorCode != 0 || ActiveProcess->GetState() == 4)
		{
			while (ActiveProcess->errorCode != 0 || ActiveProcess->GetState() == 4)
			{
				pm->killProcess(ActiveProcess->GetPID());
				ActiveProcess = pm->findPCBbyPID(1);
				instructions = 0;

				//zabezpieczenie przed nullptr; zanim cos sie stanie - ustawiany jest proces bezczynnosci
				for (std::list<PCB*>::iterator p = pm->readyProcesses.begin(); p != pm->readyProcesses.end(); ++p)
				{
					if ((*p)->GetPID() == 1)
					{
						ActiveProcess = *p;
					}
				}

				SRTSchedulingAlgorithm();
			}
		}

		else
		{
			SRTSchedulingAlgorithm();
		}
	}

	//Wywo�anie metody DoCommand() interpretera i wykonanie instrukcji ActiveProcess
	i->DoCommand();

	if (ActiveProcess->GetPID() > 1) {
		//Dla ActiveProcess innego ni� proces bezczynno�ci liczone s� wykonane instrukcje
		instructions++;
	}

	if(ActiveProcess->wait)
	{
		ActiveProcess->wait = false;
		ActiveProcess = pm->findPCBbyPID(1);
		SRTSchedulingAlgorithm();
	}
}

void ProcessScheduler::SRTSchedulingAlgorithm()
{
	//Przypadek, w kt�rym jest dost�pny tylko jeden proces w li�cie readyProcesses (proces bezczynno�ci)
	if (pm->readyProcesses.size() == 1)
	{
		ActiveProcess = *pm->readyProcesses.begin();
		instructions = 0;
		return;
	}

	//Sprawdzenie, czy ActiveProcess jest ustawiony na jaki� proces i czy jest to proces inny od procesu bezczynno�ci
	if (ActiveProcess->GetPID() > 1 && ActiveProcess != nullptr) {
		//W tej sytuacji nast�puje wyliczenie nowego czasu dla ActiveProcess
		ActiveProcess->SetProcesBurstTime(.5 * ActiveProcess->GetProcesBurstTime() + .5 * instructions);
	}

	//Ustawienie iteratora pomocniczego na proces z listy readyProcesses na ten o najkr�tszym czasie, zgodnie z ide� SRT
	iteratorToMinElement = std::min_element(pm->readyProcesses.begin(), pm->readyProcesses.end(), [](PCB* x, PCB* y) { return x->GetProcesBurstTime() < y->GetProcesBurstTime(); });

	if (ActiveProcess == nullptr)
	{
		ActiveProcess = *iteratorToMinElement;
		instructions = 0;
		return;
	}

	else
	{
		//Sprawdzenie przy pomoy PID, czy wybrany proces jest na pewno innym procesem, dodatkowe zabezpieczenie
		if ((*iteratorToMinElement)->GetPID() != ActiveProcess->GetPID())
		{
			//Dodatkowe sprawdzenie, czy czas wybranego procesu jest kr�tszy od ActiveProcess
			if ((*iteratorToMinElement)->GetProcesBurstTime() < ActiveProcess->GetProcesBurstTime())
			{
				ActiveProcess = *iteratorToMinElement;
				instructions = 0;
				return;
			}

			else
			{
				return;
			}
		}

		//Sytuacja, w kt�rej zosta� wybrany ten sam proces, co ActiveProcess, co znaczy, �e ActiveProcess wci�� ma najkr�tszy czas
		else
		{
			return;
		}
	}
}