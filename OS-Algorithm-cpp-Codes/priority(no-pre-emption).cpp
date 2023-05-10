//(priority_no_preemption)

#include <bits/stdc++.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int start_time;
    int end_time;
    bool isDone;
};


void calculate_priority_no_preemption(vector<Process>& processes) {
    int n = processes.size();
    int current_time = 0;
    int total_wait_time = 0;
    int total_turnaround_time = 0;
    int process_done = 0, cur_priority;

    //sort(processes.begin(), processes.end(), compare_arrival_time);

    for (int i = 0; process_done < n; i++) {
    	current_time = i;        
    	cur_priority = 99999;
    	int cur_process = -1;
        for(auto p : processes){        	
        	if(p.isDone == false && p.arrival_time <= current_time && cur_priority >= p.priority){
        		cur_priority = p.priority;
        		cur_process = p.id;        		
        	}
        	//cout << cur_proioru << endl;
        }

        if(cur_process == -1) continue;

        cout << processes[cur_process].id << " " << current_time << endl;

        process_done++;
        processes[cur_process].isDone = true;

        processes[cur_process].start_time = current_time;
        processes[cur_process].end_time = processes[cur_process].start_time + processes[cur_process].burst_time;
        total_turnaround_time += processes[cur_process].end_time - processes[cur_process].arrival_time;
        total_wait_time += current_time - processes[cur_process].arrival_time;
		i = processes[cur_process].end_time - 1;
    }

    double avg_wait_time = (double)total_wait_time / n;
    double avg_turnaround_time = (double)total_turnaround_time / n;

    cout << "Priority without preemption:" << endl;
    cout << "Average waiting time = " << avg_wait_time << endl;
    cout << "Average turnaround time = " << avg_turnaround_time << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the burst time, arrival time, and priority of process " << i + 1 << ": ";
        cin >> processes[i].burst_time >> processes[i].arrival_time >> processes[i].priority;
        processes[i].id = i;
        processes[i].isDone = false;
    }

    cout << "done" << endl;

    //sort(processes.begin(), processes.end(), compare_priority);

    calculate_priority_no_preemption(processes);

    return 0;
}
