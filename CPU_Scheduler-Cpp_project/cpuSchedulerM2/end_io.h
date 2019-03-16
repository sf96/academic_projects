#ifndef END_IO_H
#define END_IO_H

#include <vector>

#include "event.h"

class FutureEventList;
class CpuScheduler;

using namespace std;

class EndIo : public Event {
public:
	void Execute(CpuScheduler * cpus, FutureEventList * fel, int simt, int sim_mode, int ini_mode, int ini_time, vector<int>& data);
	EndIo(int etime, int id);
	~EndIo();
private:
	int device_id;
};

#endif // !END_IO_H