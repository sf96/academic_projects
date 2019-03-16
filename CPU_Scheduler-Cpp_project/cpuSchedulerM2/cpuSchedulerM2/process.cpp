#include <cstdlib>

#include "process.h"

int Process::id_s = 1;

Process::Process() {
	//cet = -1; // CPU Execution Time
	//ict = -1; // IO Call Time
	//iot = -1;
	//if (ict > 0) {
	//	iot = rand() % 10 + 1;// IO Occupation Time
	//}
	sw = 0;
	ew = 0;
	tw = 0;
	se = 0;
	ee = 0;

	id=id_s++;
};

int Process::GetId()
{
	return id;
}

int Process::GetCet() {
	return cet;
};

int Process::GetIct() {
	return ict;
};

int Process::GetIot()
{
	return iot;
};

int Process::GetIod()
{
	return iod;
};

int Process::GetTotalWaiting()
{
	return tw;
};

int Process::GetStartExistence()
{
	return se;
};

int Process::GetEndExistence()
{
	return ee;
};

void Process::UpdateCet()
{
	cet = cet - ict;
};

void Process::SetCet(int cet_temp)
{
	cet = cet_temp;
};

void Process::SetIct(int ict_temp)
{
	ict = ict_temp;
};

void Process::SetIod(int iod_temp)
{
	iod = iod_temp;
};

void Process::SetIot(int iot_temp)
{
	iot = iot_temp;
};

void Process::SetStartWaiting(int start_waiting)
{
	sw = start_waiting;
}
void Process::SetEndWaiting(int end_waiting)
{
	ew = end_waiting;
	tw = tw + (ew - sw);
};

void Process::SetStartExistence(int start_existence)
{
	se = start_existence;
};

void Process::SetEndExistence(int end_existence)
{
	ee = end_existence;
}
void Process::ResetId()
{
	id_s = 1;
};

Process::~Process()
{
};
