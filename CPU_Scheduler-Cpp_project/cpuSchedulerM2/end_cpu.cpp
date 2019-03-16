#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "end_cpu.h"
#include "end_io.h"
#include "cpu_scheduler.h"
#include "process.h"
#include "future_event_list.h"

EndCpu::EndCpu(int etime, int id) : Event(etime)
{
	cpu_id = id;
};

void EndCpu::Execute(CpuScheduler* cpus, FutureEventList* fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data)
{
	Process* prcs;
	prcs = cpus->GetCpu(cpu_id)->GetProcess();
	int prcs_id_temp = prcs->GetId();
	cpus->GetCpu(cpu_id)->ResetBusy();
	prcs->UpdateCet();
	bool was_served = false;
	bool terminated = false;
	cpus->SetUniIOD(prcs);   // IO Device requested
	if (prcs->GetIct() == 0) {
		if (ini_mode == 0) {
			if (prcs->GetTotalWaiting() != 0) data[6] += prcs->GetTotalWaiting();
			prcs->SetEndExistence(simt);
			data[1]++;
			data[7] += prcs->GetEndExistence() - prcs->GetStartExistence();
		}
		else if (simt > ini_time) {
			if (prcs->GetTotalWaiting() != 0) data[6] += prcs->GetTotalWaiting();
			prcs->SetEndExistence(simt);
			data[1]++;
			data[7] += prcs->GetEndExistence() - prcs->GetStartExistence();
		}
		/*
		ofstream stats;
		stats.open("awt140.txt", ios::app);		//determination of initial phase
		if (prcs->GetId() <= 1000) {
			stats << prcs->GetId() << "; " << prcs->GetTotalWaiting() << endl;
		}
		stats.close();
		*/
		/*
		if (prcs->GetId() <= 1000) {
			ofstream stats;										//determination of turnaround time
			stats.open("process_existence128.txt", ios::app);
			stats << prcs->GetId() << "; " << (prcs->GetEndExistence() - prcs->GetStartExistence()) << endl;
			stats.close();
		}
		*/
		/*
		if (prcs->GetId() == 200) {			//checking end time of initial phase
			printf("\n\n%i\n\n", simt);
		}
		*/
		delete prcs;
		terminated = true;
	}
	else {
		if (!cpus->GetIoDevice(prcs->GetIod())->IsBusy()) {
			cpus->GetIoDevice(prcs->GetIod())->ServeProcess(prcs);
			cpus->GetIoDevice(prcs->GetIod())->SetBusy();
			cpus->GetIoDevice(prcs->GetIod())->SetEndService(simt + prcs->GetIot());
			was_served = true;
			Event *process_end_io = new EndIo(simt + prcs->GetIot(), prcs->GetIod());
			fel->AddEv(process_end_io);			// dodaje zdarzenie do kalendarza
			//fel->PrintFel();
		}
		else {
			cpus->GetDeviceQueue(prcs->GetIod())->AddProcess(prcs);
		}
	}
	bool was_served2 = false;

	int prcs2_id_temp = -1;
	if (!cpus->GetReadyQueue()->IsEmpty()) {
		Process* prcs2;
		int random_pick = cpus->GetReadyQueue()->RandomPick();
		prcs2 = cpus->GetReadyQueue()->GetProcess(random_pick);
		cpus->GetReadyQueue()->RemoveProcess(random_pick);
		prcs2_id_temp = prcs2->GetId();
		was_served2 = true;
		int service_time;
		if (prcs2->GetIct() == 0) {
			service_time = simt + prcs2->GetCet();
			if (ini_mode == 0) {
				data[2 + cpu_id] += prcs2->GetCet();
				prcs2->SetEndWaiting(simt);
			}
			else if (simt > ini_time) {
				data[2 + cpu_id] += prcs2->GetCet();
				prcs2->SetEndWaiting(simt);
			}
		}
		else {
			service_time = simt + prcs2->GetIct();
			if (ini_mode == 0) {
				data[2 + cpu_id] += prcs2->GetIct();
				prcs2->SetEndWaiting(simt);
			}
			else if (simt > ini_time) {
				data[2 + cpu_id] += prcs2->GetIct();
				prcs2->SetEndWaiting(simt);
			}
		}
		cpus->GetCpu(cpu_id)->ServeProcess(prcs2);		//jeœli nie jest zajêty wpisuje na procesor
		cpus->GetCpu(cpu_id)->SetBusy();					//zajmuje procesor
		cpus->GetCpu(cpu_id)->SetEndService(service_time);
		Event* process_end_cpu = new EndCpu(service_time, cpu_id);
		fel->AddEv(process_end_cpu);		// dodaje zdarzenie do kalendarza
		/*		
		printf("\n\n");
		fel->PrintFel();	// printing Future Event List
		printf("\n\n");
		*/
	}
	
	if (sim_mode == 1) {		// detailed printing
		printf("\n------------------------------------------------------");
		printf("\nSimulation time = %i			>>>CPU END OF WORK<<<", simt);
		printf("\n------------------------------------------------------");
		printf("\nEnd of service at CPU %i of process %i", cpu_id, prcs_id_temp);
		if (was_served) {
			printf("\nProcess %i   is being served by Device %i", prcs->GetId(), prcs->GetIod());
			printf("   End of service at %i", cpus->GetIoDevice(prcs->GetIod())->GetEndService());
		}
		else if (!terminated){
			printf("\nProcess %i added to Device Queue( size = %i )",
				prcs->GetId(), cpus->GetDeviceQueue(prcs->GetIod())->GetSize());
		}
		else {
			printf("\nProcess %i terminated", prcs_id_temp);
		}
	
		if (was_served2) {
			printf("\nProcess %i   is being served by CPU %i", prcs2_id_temp, cpu_id);
			printf("	End of CPU service at %i", cpus->GetCpu(cpu_id)->GetEndService());
		}
		printf("");
		cin.ignore();
	}
};

EndCpu::~EndCpu()
{
};