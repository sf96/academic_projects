#include "io_device.h"
#include "process.h"

IoDevice::IoDevice()
{
	//busy = false;
};

bool IoDevice::IsBusy()
{
	return busy;
};

void IoDevice::SetBusy()
{
	busy = true;
};

void IoDevice::ResetBusy()
{
	busy = false;
	process_served_io_ptr = nullptr;
};

void IoDevice::ServeProcess(Process *prcs)
{
	process_served_io_ptr = prcs;
};

Process * IoDevice::GetProcess()
{
	return process_served_io_ptr;
};

void IoDevice::SetEndService(int time)
{
	end_service = time;
};

int IoDevice::GetEndService()
{
	return end_service;
};

IoDevice::~IoDevice()
{
};
