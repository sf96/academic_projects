#ifndef END_CPU_H
#define END_CPU_H

#include <vector>

#include "event.h"

class FutureEventList;
class CpuScheduler;

using namespace std;

class EndCpu : public Event {
public:
	void Execute(CpuScheduler* cpus, FutureEventList* fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data);
	EndCpu(int etime, int id);
	~EndCpu();
private:
	int iod;
	int cpu_id;

};

#endif // !END_CPU_H
