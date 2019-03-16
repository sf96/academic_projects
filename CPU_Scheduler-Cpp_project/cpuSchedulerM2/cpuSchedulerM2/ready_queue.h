#ifndef READY_QUEUE_H
#define READY_QUEUE_H

#include <vector>

class Process;
class Kernels;
class UniformGenerator;

using namespace std;

class ReadyQueue {
public:
	void AddProcess(Process * prcs);
	int RandomPick();
	Process* GetProcess(int random);
	void RemoveProcess(int random);
	bool IsEmpty();
	int GetSize();
	ReadyQueue(Kernels * kernel, int sim_number);
	~ReadyQueue();
private:
	bool empty;
	vector<Process *> process_ready_queue;
	UniformGenerator* UniGenRQ;
};

#endif // !READY_QUEUE_H