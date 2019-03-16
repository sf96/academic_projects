#include <cstdlib>
#include <iostream>
#include <cstdio>

#include "end_io.h"
#include "end_cpu.h"
#include "cpu_scheduler.h"
#include "process.h"
#include "future_event_list.h"

EndIo::EndIo(int etime, int id) : Event(etime)
{
	device_id = id;
};

void EndIo::Execute(CpuScheduler * cpus, FutureEventList * fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data)
{
	Process* prcs;
	prcs = cpus->GetIoDevice(device_id)->GetProcess();
	int cpu_id_temp;
	cpus->GetIoDevice(device_id)->ResetBusy();
	bool was_served = false;
	cpus->SetUniICT(prcs);			// losowanie IO Call Time
	if (prcs->GetIct() > 0) {
		cpus->SetUniIOT(prcs);	// losowanie IO Execution Time jeœli pojawi siê wezwanie IO ( ict > 0)
	}
	for (int i = 0; i < cpus->GetNumberOfCpus(); i++) {
		if (!cpus->GetCpu(i)->IsBusy()) {
			was_served = true;
			cpu_id_temp = i;
			int service_time;
			if (prcs->GetIct() == 0) {
				service_time = simt + prcs->GetCet();
				if (ini_mode == 0) {
					data[2 + i] += prcs->GetCet();
				}
				else if (simt > ini_time) {
					data[2 + i] += prcs->GetCet();
				}
			}
			else {
				service_time = simt + prcs->GetIct();
				if (ini_mode == 0) {
					data[2 + i] += prcs->GetIct();
				}
				else if (simt > ini_time) {
					data[2 + i] += prcs->GetIct();
				}
			}
			cpus->GetCpu(i)->ServeProcess(prcs);
			cpus->GetCpu(i)->SetBusy();
			cpus->GetCpu(i)->SetEndService(service_time);
			Event *process_end_cpu = new EndCpu(service_time, i);
			fel->AddEv(process_end_cpu);		// wpisuje zdarzenie czasowe na kalendarz
			if (was_served) {
				break;
			}
		}
	} // end of going through CPU's
	if (!was_served) {
		cpus->GetReadyQueue()->AddProcess(prcs);
		if (ini_mode == 0) prcs->SetStartWaiting(simt);
		else if (simt > ini_time) prcs->SetStartWaiting(simt);
	}
	bool was_served2 = false;
	if (!cpus->GetDeviceQueue(device_id)->IsEmpty()) {
		Process* prcs2;
		prcs2 = cpus->GetDeviceQueue(device_id)->GetProcess();	//getting from queue
		cpus->GetDeviceQueue(device_id)->RemoveProcess();		//removing from Queue
		cpus->GetIoDevice(device_id)->ServeProcess(prcs2);
		cpus->GetIoDevice(device_id)->SetBusy();
		cpus->GetIoDevice(device_id)->SetEndService(simt + prcs2->GetIot());
		was_served2 = true;
		Event* process_end_io = new EndIo(simt + prcs2->GetIot(), device_id);
		fel->AddEv(process_end_io);		//wpisuje zdarzenie czasowe na kalendarz
		/*
		printf("\n\n");
		fel->PrintFel();  // printing Future Event List
		printf("\n\n");
		*/
	}

	if (sim_mode == 1) {		// detailed printing
		printf("\n------------------------------------------------------");
		printf("\nSimulation time = %i			>>>DEVICE END OF WORK<<<", simt);
		printf("\n------------------------------------------------------");
		printf("\nEnd of service at Device %i of process %i", device_id, prcs->GetId());
		if (was_served) {
			printf("\nProcess %i   is being served by CPU %i", prcs->GetId(), cpu_id_temp);
			printf("   End of CPU service at %i",
				cpus->GetCpu(cpu_id_temp)->GetEndService());
		}
		else {
			printf("\nProcess %i added to Ready Queue( size = %i )",
				prcs->GetId(), cpus->GetReadyQueue()->GetSize());
		}
	
		if (was_served2) {
			printf("\nProcess %i   is being served by Device %i",
				cpus->GetIoDevice(device_id)->GetProcess()->GetId(), device_id);
			printf("	End  of Device service at %i",
				cpus->GetIoDevice(device_id)->GetEndService());
		}
		printf("");
		cin.ignore();
	}
};

EndIo::~EndIo()
{
}
