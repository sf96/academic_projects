#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

class FutureEventList;
class CpuScheduler;

using namespace std;

class Simulation {
public:
	void Simulate(FutureEventList* fel);
	Simulation(CpuScheduler * cpus, int end_simulation_time, int initial_time, int simulation_mode, int initial_mode);  // w tym ca³a pêtla symulacyjna czy osobna metoda "start / loop " \ 
	~Simulation();  //pêtla
private:
	int sim_time;
	int end_sim_time;	// end of simulation
	int ini_time;
	CpuScheduler * cpus_ptr;
	int sim_mode;
	int ini_mode;
	vector<int> data;
};


#endif // !SIMULATION_H
