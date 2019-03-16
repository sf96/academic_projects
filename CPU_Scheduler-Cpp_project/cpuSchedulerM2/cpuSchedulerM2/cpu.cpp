#include "cpu.h"
#include "process.h"

Cpu::Cpu()
{
};

bool Cpu::IsBusy()
{
	return busy;
};

void Cpu::SetBusy()
{
	busy = true;
};

void Cpu::ResetBusy()
{
	busy = false;
	process_served_cpu_ptr = nullptr;
};

void Cpu::ServeProcess(Process *prcs)
{
	process_served_cpu_ptr = prcs;
};

Process * Cpu::GetProcess()
{
	return process_served_cpu_ptr;
};

void Cpu::SetEndService(int time)
{
	end_service = time;
};

int Cpu::GetEndService()
{
	return end_service;
};

Cpu::~Cpu()
{
};
