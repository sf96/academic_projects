#ifndef CPU_SCHEDULER_H
#define CPU_SCHEDULER_H

#include <vector>
#include <queue>

#include "cpu.h"
#include "io_device.h"
#include "ready_queue.h"
#include "device_queue.h"
#include "event.h"
#include "process.h"

#include "kernels.h"
#include "generator.h"

/*
class DeviceQueue;
class ReadyQueue;
class IoDevice;
class Process;
class Cpu;*/

using namespace std;

class CpuScheduler {
public:
	Cpu* GetCpu(int i);
	int GetNumberOfCpus();
	int GetNumberOfIoDevs();
	ReadyQueue* GetReadyQueue();
	DeviceQueue* GetDeviceQueue(int i);
	IoDevice* GetIoDevice(int i);
	//void SetKernel(Kernels* kernel);		//proba kernela
	//Kernels* GetKernelPtr();
	int GetExpPGT();
	int GetUniCET();				// sam CET do procesu, potem po ENDCPU updateICT z przekazanym procesem
	void SetUniCET(Process* prcs);
	void SetUniICT(Process* prcs);
	void SetUniIOT(Process* prcs);
	void SetUniIOD(Process* prcs);
	CpuScheduler(Kernels* kernel, int sim_number, double lambda_pgt);
	~CpuScheduler();
private:
	const int kNumberOfCpus = 4;
	const int kNumberOfDevices = 5;
	vector<Cpu *> cpu_list;
	vector<IoDevice *> io_device_list;
	ReadyQueue *ready_queue ;
	//queue<Process *> device_queue;
	vector<DeviceQueue *> device_queue_list;
	UniformGenerator* UniGenPGT;
	UniformGenerator* UniGenCET;
	UniformGenerator* UniGenIOT;
	UniformGenerator* UniGenICT;
	UniformGenerator* UniGenIOD;
	ExpGenerator* ExpGen;
};

#endif // !CPU_SCHEDULER_H