#include <cstdlib>

#include "future_event_list.h"
#include "event.h"
#include "new_process.h"
#include "end_io.h"
#include "kernels.h"
#include "generator.h"

FutureEventList::FutureEventList(Kernels * kernel, int sim_number)
{
	UniGenFEL = new UniformGenerator(kernel->GetKernel(kernel->FEL, sim_number));
};

void FutureEventList::AddEv(Event* ev)
{
	bool equal = false;
	bool was_served = false;
	if (future_event_list.size() == 0) {
		future_event_list.push_back(ev);
	}
	else {
		int i = 1;

		while (ev->GetEventTime() <= (future_event_list[future_event_list.size() - i])->GetEventTime()) {

			if (ev->GetEventTime() == (future_event_list[future_event_list.size() - i])->GetEventTime()) {
				equal = true;
			}
			if (i < int(future_event_list.size())) {
				i++;
			}
			else {
				break;
			}
		}
		if (equal == true) {
			//int random = rand() % 2 + 1;
			int random = UniGenFEL->Rand(1, 3);
			future_event_list.insert(future_event_list.end() - (i - random), ev);
			was_served = true;
			//if (was_served) {
			//	break;
			//}
		}
		else {
			future_event_list.insert(future_event_list.end() - (i - 1), ev);
			//break;
		}
	}
};

Event * FutureEventList::GetEv()
{
	return future_event_list[0];
};
void FutureEventList::RemoveEv()
{
	future_event_list.erase(future_event_list.begin());
}
int FutureEventList::GetSize()
{
	return future_event_list.size();
};
void FutureEventList::PrintFel()
{
	for (int i = 0; i < future_event_list.size(); i++) {
		printf("Event time: %i ",future_event_list[i]->GetEventTime());
	}
};

FutureEventList::~FutureEventList()
{
};
