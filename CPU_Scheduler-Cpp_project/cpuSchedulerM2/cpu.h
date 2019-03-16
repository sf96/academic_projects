#ifndef CPU_H
#define CPU_H

class Process;

class Cpu {
public:
	bool IsBusy();
	void SetBusy();
	void ResetBusy();
	void ServeProcess(Process *prcs);
	Process* GetProcess();
	void SetEndService(int time);
	int GetEndService();
	Cpu();
	~Cpu();
private:
	bool busy;
	Process *process_served_cpu_ptr;
	int end_service;
};

#endif // !CPU_H