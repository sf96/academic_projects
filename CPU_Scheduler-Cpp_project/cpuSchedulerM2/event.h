#ifndef EVENT_H
#define EVENT_H

#include <vector>

using namespace std;

class FutureEventList;
class CpuScheduler;

class Event {
public:
	virtual void Execute(CpuScheduler* cpus, FutureEventList* fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data) = 0;
	int GetEventTime();
	Event(int etime);			// konstruktor z parametrem 
	~Event();
protected:
	int event_time;
};

#endif // !EVENT_H
