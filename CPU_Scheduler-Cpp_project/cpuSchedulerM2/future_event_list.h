#ifndef FUTURE_EVENT_LIST_H
#define FUTURE_EVENT_LIST_H

#include <vector>

class Event;
class Kernels;
class UniformGenerator;

using namespace std;

class FutureEventList {
public:
	void AddEv(Event* ev);
	Event* GetEv();
	void RemoveEv();
	int GetSize();
	void PrintFel();
	FutureEventList(Kernels * kernel, int sim_number);
	~FutureEventList();
private:
	vector<Event *> future_event_list;
	UniformGenerator* UniGenFEL;
};

#endif // !FUTURE_EVENT_LIST_H