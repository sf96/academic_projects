#include <cstdlib>

#include "ready_queue.h"
#include "process.h"
#include "generator.h"
#include "kernels.h"

using namespace std;

ReadyQueue::ReadyQueue(Kernels * kernel, int sim_number)
{
	UniGenRQ = new UniformGenerator(kernel->GetKernel(kernel->RQP, sim_number));
	//empty = true;
};

int ReadyQueue::RandomPick()
{
	int random_pick = UniGenRQ->Rand(0,process_ready_queue.size());
	return random_pick;
}
Process * ReadyQueue::GetProcess(int random)
{
	return process_ready_queue[random];
};

void ReadyQueue::RemoveProcess(int random)
{
	process_ready_queue.erase(process_ready_queue.begin() + random);
};

bool ReadyQueue::IsEmpty()
{
	if (process_ready_queue.size() > 0) {
		return false;
	}
	else {
		return true;
	}
}
int ReadyQueue::GetSize()
{
	return process_ready_queue.size();
};

void ReadyQueue::AddProcess(Process * prcs)
{
	process_ready_queue.push_back(prcs);
};

ReadyQueue::~ReadyQueue()
{

};
