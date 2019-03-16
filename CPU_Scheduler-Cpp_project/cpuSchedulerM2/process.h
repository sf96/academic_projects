#ifndef PROCESS_H
#define PROCESS_H

using namespace std;

class Process {
public:
	int GetId();
	int GetCet();
	int GetIct();
	int GetIot();
	int GetIod();
	int GetTotalWaiting();
	int GetStartExistence();
	int GetEndExistence();
	void UpdateCet();
	void SetCet(int cet_temp);
	void SetIct(int ict_temp);
	void SetIod(int iod_temp);
	void SetIot(int iot_temp);
	void SetStartWaiting(int start_waiting);
	void SetEndWaiting(int end_waiting);		//setting end of waiting in queue and summing up time
	void SetStartExistence(int start_existence);
	void SetEndExistence(int end_existence);
	void ResetId();
	Process();
	~Process();
private:
	int cet;	//CPU Execution Time
	int ict;	//IO Call Time
	int iot;	//IO Operation Time
	int iod;	//IO Device
	int id;
	static int id_s;
	int sw;	//start waiting time
	int ew;	//end waiting time
	int tw; //total waiting time
	int se;	//start of process's existence
	int ee; //end of prcess's existence
};

#endif // !PROCESS_H