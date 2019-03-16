#ifndef NEW_PROCESS_H
#define NEW_PROCESS_H

#include <vector>

#include "event.h"

class FutureEventList;
class CpuScheduler;

using namespace std;

class NewProcess: public Event {
public:
	void Execute(CpuScheduler* cpus, FutureEventList* fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data);
	NewProcess(int etime);
	~NewProcess();
private:
	int pgt;
};

#endif // !NEW_PROCESS_H
