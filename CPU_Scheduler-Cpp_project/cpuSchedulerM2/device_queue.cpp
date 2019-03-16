#include "device_queue.h"
#include "process.h"

DeviceQueue::DeviceQueue()
{
	//empty = true;
};

void DeviceQueue::AddProcess(Process *prcs) 
{
	process_device_queue.push(prcs);
};

Process* DeviceQueue::GetProcess() 
{
	return process_device_queue.front();
};

void DeviceQueue::RemoveProcess()
{
	process_device_queue.pop();
};

bool DeviceQueue::IsEmpty()
{
	if (process_device_queue.size() > 0) {
		return false;
	}
	else {
		return true;
	}
};

int DeviceQueue::GetSize()
{
	return process_device_queue.size();
};

DeviceQueue::~DeviceQueue() 
{
};
