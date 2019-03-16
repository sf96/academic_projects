#include <cstdio>
#include <iostream>
#include <fstream>

#include "simulation.h"
#include "event.h"
#include "new_process.h"
#include "future_event_list.h"
#include "cpu_scheduler.h"

Simulation::Simulation(CpuScheduler * cpus, int end_simulation_time, int initial_time, int simulation_mode, int initial_mode)
{
	//cpus_ptr = new CpuScheduler();
	cpus_ptr = cpus;
	sim_time = 0;
	end_sim_time = end_simulation_time;
	ini_time = initial_time;
	sim_mode = simulation_mode;
	ini_mode = initial_mode;
};

Simulation::~Simulation()
{
}
void Simulation::Simulate(FutureEventList* fel)
{
	data.push_back(0);	// Number of generated processes data[0]
	data.push_back(0);	// Number of terminated processes data[1]
	data.push_back(0);	// CPU1 utilization data[2]
	data.push_back(0);	// CPU2 utilization data[3]
	data.push_back(0);	// CPU3 utilization data[4]
	data.push_back(0);	// CPU4 utilization data[5]
	data.push_back(0);	// Ready Queue total waiting time data[6]
	data.push_back(0);	// Total turnaround time data[7]

	Event* process_new = new NewProcess(sim_time);
	fel->AddEv(process_new);
	while (sim_time < end_sim_time && fel->GetSize() > 0) {
		Event* e = fel->GetEv();
		sim_time = e->GetEventTime();
		e->Execute(cpus_ptr, fel, sim_time, sim_mode, ini_mode, ini_time, data);
		fel->RemoveEv();
	}

	cpus_ptr->GetCpu(0)->GetProcess()->ResetId();

	printf("\n Number of generated processes:		%i", data[0]);
	printf("\n Number of terminated processes:	%i ", data[1]);
	printf("\n_____________________________________________________________________\n");
	//printf("\nEfectiveness of system: %f %%", (((double) data[1]) / ((double) data[0])) * 100);
	printf("\n Throughput:				%f ", ((double)data[1]) / ((double)end_sim_time - ini_time));
	printf("\n_____________________________________________________________________\n");
	printf("\n Average turnaround time of process:	%f ms", (((double)data[7]) / ((double)data[1])));
	printf("\n_____________________________________________________________________\n");
	printf("\n Total waiting time in Ready Queue:	%i ms", data[6]);
	printf("\n Average waiting time of process:	%f ms ", (((double) data[6]) / ((double)data[1])));
	printf("\n_____________________________________________________________________\n");
	printf("\n CPU #1 Utilization:			%f %%", (((double)data[2]) / ((double)end_sim_time - ini_time)) * 100);
	printf("\n CPU #2 Utilization:			%f %%", (((double)data[3]) / ((double)end_sim_time - ini_time)) * 100);
	printf("\n CPU #3 Utilization:			%f %%", (((double)data[4]) / ((double)end_sim_time - ini_time)) * 100);
	printf("\n CPU #4 Utilization:			%f %%", (((double)data[5]) / ((double)end_sim_time - ini_time)) * 100);
	printf("\n_____________________________________________________________________\n");
	printf("\n/ / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /");
	/*
	ofstream stats;
	stats.open("average_waiting_ci_133.txt", ios::app);
	stats << (((double)data[6]) / ((double)data[1])) << "; " << data[1] << endl; // AWT AVG
	stats.close();
	*/
	
	for (int i = 0; i < data.size(); i++)
		data[i] = 0;
};

