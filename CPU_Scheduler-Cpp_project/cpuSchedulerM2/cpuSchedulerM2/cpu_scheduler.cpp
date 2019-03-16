#include "cpu_scheduler.h"
/*#include "cpu.h"
#include "io_device.h"
#include "ready_queue.h"
#include "device_queue.h" */

CpuScheduler::CpuScheduler(Kernels* kernel, int sim_number, double lambda_pgt)
{
	UniGenPGT = new UniformGenerator(kernel->GetKernel(kernel->TPG, sim_number));	// 1 zamienic na i z fora 10 symulacji
	UniGenCET = new UniformGenerator(kernel->GetKernel(kernel->TPW, sim_number));
	UniGenIOT = new UniformGenerator(kernel->GetKernel(kernel->TPO, sim_number));
	UniGenICT = new UniformGenerator(kernel->GetKernel(kernel->TPIO, sim_number));
	UniGenIOD = new UniformGenerator(kernel->GetKernel(kernel->TPD, sim_number));
	ExpGen = new ExpGenerator(lambda_pgt, UniGenPGT);

	for (int i = 0; i < kNumberOfCpus; i++) {
		Cpu *cpu = new Cpu();
		cpu_list.push_back(cpu);
	}

	for (int i = 0; i < kNumberOfDevices; i++) {
		IoDevice *io_device = new IoDevice();
		io_device_list.push_back(io_device);

		DeviceQueue *device_queue = new DeviceQueue();
		device_queue_list.push_back(device_queue);
	}

	ready_queue = new ReadyQueue(kernel, sim_number);

};

int CpuScheduler::GetNumberOfCpus() 
{
	return kNumberOfCpus;
};

int CpuScheduler::GetNumberOfIoDevs()
{
	return kNumberOfDevices;
};

ReadyQueue * CpuScheduler::GetReadyQueue()
{
	return ready_queue;
};

DeviceQueue * CpuScheduler::GetDeviceQueue(int i)
{
	return device_queue_list[i];
};

IoDevice * CpuScheduler::GetIoDevice(int i)
{
	return io_device_list[i];
};

/*Kernels * CpuScheduler::GetKernelPtr()
{
	return kernel_temp;
};
*/

int CpuScheduler::GetExpPGT()
{
	return (int) ExpGen->Rand();
};

int CpuScheduler::GetUniCET()
{
	return (int) UniGenCET->Rand(1, 51);
};

void CpuScheduler::SetUniCET(Process * prcs)
{
	prcs->SetCet(UniGenCET->Rand(1, 51));
};

void CpuScheduler::SetUniICT(Process * prcs)
{
	prcs->SetIct(UniGenICT->Rand(0,prcs->GetCet()));
};

void CpuScheduler::SetUniIOT(Process * prcs)
{
	prcs->SetIot(UniGenIOT->Rand(1, 11));
};

void CpuScheduler::SetUniIOD(Process * prcs)
{
	prcs->SetIod(UniGenIOD->Rand(0, kNumberOfDevices));
};

Cpu * CpuScheduler::GetCpu(int i)
{
	return cpu_list[i];
};



CpuScheduler::~CpuScheduler() 
{

};