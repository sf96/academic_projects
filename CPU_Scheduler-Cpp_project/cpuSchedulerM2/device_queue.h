#ifndef DEVICE_QUEUE_H
#define DEVICE_QUEUE_H

#include <queue>

class Process;

using namespace std;

class DeviceQueue {
public:
	void AddProcess(Process *prcs);
	Process* GetProcess();
	void RemoveProcess();
	bool IsEmpty();
	int GetSize();
	DeviceQueue();
	~DeviceQueue();
private:
	bool empty;
	queue<Process *> process_device_queue;
};

#endif // !DEVICE_QUEUE_H