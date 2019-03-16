#ifndef IO_DEVICE_H
#define IO_DEVICE_H

using namespace std;

class Process;

class IoDevice {
public:
	bool IsBusy();
	void SetBusy();
	void ResetBusy();
	void ServeProcess(Process *prcs);
	Process* GetProcess();
	void SetEndService(int time);
	int GetEndService();
	IoDevice();
	~IoDevice();
private:
	bool busy;
	Process *process_served_io_ptr;
	int end_service;
};

#endif // !IO_DEVICE_H