#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "cpu_scheduler.h"
#include "future_event_list.h"
#include "simulation.h"
#include "kernels.h"
#include "generator.h"

using namespace std;

void main() {

	Kernels *kernel = new Kernels();
	//kernel->GenerateKernels("seed.txt");
	kernel->ReadKernels("seed.txt");
	/*											// STATISTIC GATHERING
	int uniform_gen[] = {0,0,0,0,0,0,0,0,0,0};
	UniformGenerator* UniGen = new UniformGenerator(kernel->GetKernel(kernel->TPW, 0));
	UniformGenerator* UniGenPGT = new UniformGenerator(kernel->GetKernel(kernel->TPG, 0));
	ExpGenerator* ExpGenPGT = new ExpGenerator(0.13, UniGenPGT);
	ofstream stats;
	stats.open("exponential_gen.txt");
	for (int i = 0; i < 1000000; i++) {
		int a = ExpGenPGT->Rand();
		stats << a << endl;
	}
	stats.close();
	stats.open("uniform_gen.txt");
	for (int i = 0; i < 1000000; i++) {
		int a = UniGen->Rand(1, 11);
		uniform_gen[a - 1]++;
		stats << uniform_gen[i] << endl;
	}
	stats.close();
	*/
	
	int initial_mode;
	int simulation_mode;
	int end_simulation_time;
	int initial_time = 0;
	double lambda;

	printf("Input end of simulation time: \n");
	cin >> end_simulation_time;
	printf("Input lambda (intensity of creating new process): \n");
	cin >> lambda;
	printf("Choose simulation mode\n '0' for continuous \n'1' for step by step \n");
	cin >> simulation_mode;
	printf("Choose: \n'0' to proceed \n'1' to skip initial phase \n");
	cin >> initial_mode;
	if (initial_mode == 1) {
		initial_time = 1800;
		//printf("Input initial phase time: \n");
		//cin >> initial_time;
	}

	for (int i = 0; i < 10; i++) {
		printf("\n_____________________________________________________________________\n");
		printf("\n		>>>  Simulation number %i  <<<", i);
		printf("\n_____________________________________________________________________\n");
		CpuScheduler* cpu_scheduler = new CpuScheduler(kernel, i, lambda);
		FutureEventList* future_event_list = new FutureEventList(kernel, i);
		Simulation* simulation = new Simulation(cpu_scheduler, end_simulation_time, initial_time, simulation_mode, initial_mode);
		simulation->Simulate(future_event_list);
	}
	printf("\n\n");
	system("PAUSE");
}