#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "new_process.h"
#include "end_cpu.h"
#include "cpu_scheduler.h"
#include "process.h"
#include "future_event_list.h"

NewProcess::NewProcess(int etime): Event(etime)
{
};

void NewProcess::Execute(CpuScheduler* cpus, FutureEventList* fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data)
{ 
	Process *process = new Process();			//tworze nowy process
	if (ini_mode == 0) {
		process->SetStartExistence(simt);
		data[0]++;
	}
	else if (simt > ini_time) {
		process->SetStartExistence(simt);
		data[0]++;
	}
	cpus->SetUniCET(process);
	cpus->SetUniICT(process);
	if (process->GetIct() > 0) {
		cpus->SetUniIOT(process);
	}
	pgt = cpus->GetExpPGT();						// random with exponential distribution intesity L
	/*	//creating statistic files
		ofstream stats;
		//stats.open("uniform.txt", ios::app);
		//stats << process->GetCet() << endl;
		//stats.close();
		stats.open("exponential.txt", ios::app);
		stats << pgt << endl;
		stats.close();
	*/
	bool was_served = false;
	int cpu_id_temp = -1;
	for (int i = 0; i < cpus->GetNumberOfCpus(); i++) {
		if (!cpus->GetCpu(i)->IsBusy()) {				//sprawdzanie zajêtoœci CPU
			was_served = true;
			cpu_id_temp = i;
			int service_time;
			if (process-> GetIct() == 0) {
				service_time = simt + process->GetCet();
				if (ini_mode == 0) {
					data[2 + i] += process->GetCet();	//CPU busy
				}
				else if (simt > ini_time) {
					data[2 + i] += process->GetCet();
				}
			}
			else {
				service_time = simt + process->GetIct();
				if (ini_mode == 0) {
					data[2 + i] += process->GetIct();
				}
				else if (simt > ini_time) {
					data[2 + i] += process->GetIct();
				}
			}
			cpus->GetCpu(i)->ServeProcess(process);		//jeœli nie jest zajêty wpisuje na procesor
			cpus->GetCpu(i)->SetBusy();					//zajmuje procesor
			cpus->GetCpu(i)->SetEndService(service_time);
			Event *process_end_cpu = new EndCpu(service_time, i);
			fel->AddEv(process_end_cpu);					// wpisuje zdarzenie czasowe na kalendarz
			if (was_served) {
				break;
			}
		}
	}	// koniec przeszukiwania CPU

	if (!was_served) {
		cpus->GetReadyQueue()->AddProcess(process);	//jeœli 4 CPUs s¹ zajête wpisuje do kolejki
		if (ini_mode == 0) process->SetStartWaiting(simt);
		else if (simt > ini_time) process->SetStartWaiting(simt);
	}

	Event *process_new = new NewProcess(simt + pgt);
	fel->AddEv(process_new);				//wpisuje zdarzenie do kalendarza
	/*
	printf("\n\n");
	fel->PrintFel();	// printing Future Event List
	printf("\n\n");
	*/
	if (sim_mode == 1) {		//	detailed printing
		printf("\n------------------------------------------------------");
		printf("\nSimulation time = %i			>>>NEW PROCESS EVENT<<<", simt);
		printf("\n------------------------------------------------------");
		printf("\nNew process at = %i \n", simt + pgt);
		if (was_served) {
			printf("Process %i   is being served by CPU %i", process->GetId(), cpu_id_temp);
			printf("   End of service at %i", cpus->GetCpu(cpu_id_temp)->GetEndService());
		}
		else {
			printf("Process %i added to Ready Queue( size = %i )",
				process->GetId(), cpus->GetReadyQueue()->GetSize());
		}
		printf("");
		cin.ignore();
	}
};

NewProcess::~NewProcess() 
{
};
