// Banker's Algorithm 
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 100;
const int MAXM = 100;

int n, m;  // n = number of processes, m = number of resources

int available[MAXM];  // available resources
int max_need[MAXN][MAXM];  // max need of each process
int allocated_resources[MAXN][MAXM];  // allocated resources of each process
int need[MAXN][MAXM];  // need of each process

bool finish[MAXN];  // indicates if a process has finished or not
vector<int> safe_sequence; // safe sequence of processes

void initialize() {
    memset(finish, false, sizeof(finish));
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> m;
    cout << "Enter the available resources: ";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }
    cout << "Enter the max need of each process: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> max_need[i][j];
        }
    }
    cout << "Enter the allocated resources of each process: ";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocated_resources[i][j];
            need[i][j] = max_need[i][j] - allocated_resources[i][j];
        }
    }
}

bool isSafe() {
    int work[MAXM];
    memcpy(work, available, sizeof(available));
    memset(finish, false, sizeof(finish));

    // Find an i such that both finish[i] == false and need_i <= work
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool need_le_work = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        need_le_work = false;
                        break;
                    }
                }
                if (need_le_work) {
                    // Finish process i and release its resources
                    finish[i] = true;
                    for (int j = 0; j < m; j++) {
                        work[j] += allocated_resources[i][j];
                    }
                    safe_sequence.push_back(i);
                }
            }
        }
    }

    // If all processes are finished, the system is in a safe state
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            return false;
        }
    }
    return true;
}

bool isRequestValid(int pid, int request[]) {
    // Check if request is greater than need
    for (int j = 0; j < m; j++) {
        if (request[j] > need[pid][j]) {
            return false;
        }
    }

    // Check if request is greater than available
    for (int j = 0; j < m; j++) {
        if (request[j] > available[j]) {
            return false;
        }
    }

    return true;
}

void grantRequest(int pid, int request[]) {
    if (!isRequestValid(pid, request)) {
        cout << "Request is not valid!" << endl;
        return;
    }
    // Pretend to
    // allocate resources to the process
    for (int j = 0; j < m; j++) {
        available[j] -= request[j];
        allocated_resources[pid][j] += request[j];
        need[pid][j] -= request[j];
    }

    // Check if the system is still in a safe state after granting the request
    if (isSafe()) {
        cout << "Request is granted. The safe sequence is:" << endl;
        for(auto x:safe_sequence)cout<<x<<" " ;
        cout<<endl ;
    } else {
        // If not, undo the allocation and deny the request
        for (int j = 0; j < m; j++) {
            available[j] += request[j];
            allocated_resources[pid][j] -= request[j];
            need[pid][j] += request[j];
        }
        cout << "Request is denied to avoid unsafe state." << endl;
    }
}

int main() {
    initialize();
    while (true) {
        int choice;
        cout << "Enter 1 to request resources or 2 to exit: ";
        cin >> choice;
        if (choice == 1) {
            int pid;
            cout << "Enter the process id: ";
            cin >> pid;
            int request[MAXM];
            cout << "Enter the request: ";
            for (int j = 0; j < m; j++) {
                cin >> request[j];
            }
            grantRequest(pid, request);
            
        } else if (choice == 2) {
            break;
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}



