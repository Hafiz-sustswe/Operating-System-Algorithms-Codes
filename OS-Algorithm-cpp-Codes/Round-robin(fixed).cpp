// Round Robin algorithm

#include<iostream>
#include <algorithm>
#include <queue>
#include<iomanip>
#include<climits>
using namespace std;

struct process{
    int pid, arrival_time, burst_time, priority, start_time, completion_time,
     turnaround_time, waiting_time;
}p[100];



bool comparatorAT(struct process a, struct process b){
    int x = a.arrival_time;
    int y = b.arrival_time;
    return x<y;
}

int main(){
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;

    int bt_remaining[100];
    queue<int> q;
    int current_time  = 0;
    int completed = 0, tq;
    int visited[100] = {false};

    int n, index;
    cout << "Enter the number of processes: ";
    cin >> n;

    for(int i = 0 ; i < n; i++){
        cout << "Enter arr ival time of the process " << i << ":";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of the process " << i << ":";
        cin >> p[i].burst_time;
        p[i].pid = i;
        cout << endl;
        bt_remaining[i] = p[i].burst_time;

    }
    cout << endl;
    cout << "Enter the time quanta: ";
    cin >> tq;

    sort(p, p+n, comparatorAT);

    q.push(0);
    visited[0] = true;

    while(completed != n){
        index = q.front();
        q.pop();
        if(bt_remaining[index] == p[index].burst_time){
            p[index].start_time = max(current_time, p[index].arrival_time);
            current_time = p[index].start_time;
        }
        if(bt_remaining[index]-tq > 0){
            bt_remaining[index]-=tq;
            current_time +=tq;
        }
        else{
            current_time += bt_remaining[index];
            bt_remaining[index] = 0;
            completed++;

            p[index].completion_time= current_time;
            p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;

            total_turnaround_time += p[index].turnaround_time;
            total_waiting_time +=p[index].waiting_time;

        }
        for(int i = 1; i < n; i++){
            if(bt_remaining[i] > 0 && p[i].arrival_time <= current_time && visited[i] == false){
                q.push(i);
                visited[i] = true;
            }
        }

        if(bt_remaining[index] > 0)
            q.push(index);

        if(q.empty()){
            for(int i = 1; i < n; i++){
                if(bt_remaining[i] > 0){
                    q.push(i);
                    visited[i] = true;
                    break;
                }
            }
        }
    }

    cout << "Process NO\tAT\tBrust Time\tCT\tTAT\tWT" << endl;
    for(int i = 0; i < n; i++){
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << endl;
    }

    cout << "Average turnaround time: " << (float)total_turnaround_time/n << endl;
    cout << "Average waiting time: " << (float)total_waiting_time/n << endl;
    return 0;

}
