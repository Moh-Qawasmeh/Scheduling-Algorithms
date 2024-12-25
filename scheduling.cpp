/*
 *    author:  Mohammad Qawasmeh
 *    created: 23.12.2024 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define endl '\n'
 
 struct Process{
  int processing;
  int arrival;
  int order;
  string name;
 };
 
 bool so(const Process &a, const Process &b){
   if(a.arrival == b.arrival){
     if(a.processing == b.processing){
        return a.order < b.order;
     }
     return a.processing < b.processing;
   }
   return a.arrival < b.arrival;
 }

 vector<Process> p;
 map<pair<string, int>, pair<int, int>> mp;
 int num_of_processes, time_quantum;

 void input(){
   cout << "The number of processes: "; 
   cin >> num_of_processes;
   p.resize(num_of_processes);
   cout << endl;
   for(int i = 0; i < num_of_processes; i++ ){
     string name;
     int processing, arrival;
     cin >> name >> arrival >> processing;
     p[i].name = name;
     p[i].processing = processing;
     p[i].arrival = arrival;
     p[i].order = i;
   } 
   sort(p.begin(), p.end(), so);
 }

 void SRT(){
   using alies = pair<int, pair<int, pair<int, string>>>;
   priority_queue<alies, vector<alies>, greater<alies>> pq;
   int index = 0, Time = p[0].arrival;
   while(!pq.empty() || index < num_of_processes){
    while (index < num_of_processes && p[index].arrival <= Time) {
      pq.push({p[index].processing, {p[index].arrival, {p[index].order, p[index].name}}});
        index++;
    }
    if (pq.empty()) {
      Time = p[index].arrival;
      continue;
    }
    int arrival = pq.top().second.first;
    int processing = pq.top().first, order = pq.top().second.second.first;
    string name = pq.top().second.second.second;
    pq.pop();
    processing--;
    if (mp.find({name, order}) == mp.end()){ 
        mp[{name, order}] = {-1, -1};
    }
    if (mp[{name, order}].first == -1){ 
        mp[{name, order}].first = Time;
    }
    if (processing > 0){
        pq.push({processing, {arrival, {order, name}}});
    }
    else{ 
        mp[{name, order}].second = Time + 1;
    }
    Time++;
   }
 }

 void RR(){
   cout << "Enter the time quantum: ";
   cin >> time_quantum;
   int Time = p[0].arrival, index = 1, j = 0, size = 0, cur;
   using alies = pair<int, pair<int, pair<int, string>>>;
   queue<alies> q; 
   q.push({p[0].processing, {p[0].arrival, {p[0].order, p[0].name}}});
   while(index < num_of_processes || !q.empty()){
       int processing = q.front().first, arrival = q.front().second.first, order = q.front().second.second.first;
       string name = q.front().second.second.second;
       q.pop();
       int T = min(time_quantum, processing);
       Time += T; 
       while(index < num_of_processes && p[index].arrival <= Time){
           q.push({p[index].processing, {p[index].arrival, {p[index].order, p[index].name}}});
           index++;
       }
       processing -= min(time_quantum, processing);
       if (mp.find({name, order}) == mp.end()){ 
       mp[{name, order}] = {-1, -1};
       }
       if (mp[{name, order}].first == -1){ 
       mp[{name, order}].first = Time - T;
       }
       if (processing == 0){ 
       mp[{name, order}].second = Time;
        }
       else {
          q.push({processing, {arrival, {order, name}}}); 
       }
       if(q.empty() && index < num_of_processes){
            q.push({p[index].processing, {p[index].arrival, {p[index].order, p[index].name}}});
            Time = p[index].arrival;
       }
   }
 }

 void SJF(){
   using alies = pair<int, pair<int, pair<int, string>>>;
   priority_queue<alies, vector<alies>, greater<alies>> pq; // processing then arrival then order
   int index = 0, Time = 0;
   vector<string> ans;
   while(!pq.empty() || index < num_of_processes){
     while (index < num_of_processes && p[index].arrival <= Time) {
        pq.push({p[index].processing, {p[index].arrival, {p[index].order, p[index].name}}});
        index++;
     }
     if (pq.empty()) {
        Time = p[index].arrival;
        continue;
     }
     int arrival = pq.top().second.first;
     int processing = pq.top().first;
     string name = pq.top().second.second.second;
     int order = pq.top().second.second.first;
     pq.pop();
     mp[{name, order}].first = Time;
     mp[{name, order}].second = Time + processing;
     Time += processing;
     ans.push_back(name);
   }
 }

 void FIFO(){
    vector<string> ans; 
    int Time = p[0].arrival;
    for(int i = 0; i < num_of_processes; i++ ){
       int arrival = p[i].arrival;
       int processing = p[i].processing;
       string name = p[i].name;
       int order = p[i].order;
       mp[{name, order}].first = Time;
       mp[{name, order}].second = Time + processing;
       Time += processing;
       ans.push_back(name);
    }
 }
 
 void output(){
    cout << "Process  Start  End  Turnaround  Delay" << endl;
    for(auto i: mp){
        cout << i.first.first << "      " << i.second.first << "      " << i.second.second ;
        int index = i.first.second;
        int turnaround =  i.second.second - p[index].arrival;
        int delay = turnaround - p[index].processing;
        cout << "       " << turnaround << "     " << delay << endl;
    }
 }
 
int main() {
    ios_base::sync_with_stdio(0);
    cout << "Enter 1 if you want to use First-Come, First-Served algorihm." << endl;
    cout << "Enter 2 if you want to use Shortest Job First algorihm." << endl;
    cout << "Enter 3 if you want to use Shortest Remaining Time algorihm."<< endl;
    cout << "Enter 4 if you want to use Round-Robin algorihm." << endl;
    int algorihm; cin >> algorihm; 
    switch(algorihm){
        case 1: input(); FIFO();
        break;
        case 2: input(); SJF();
        break;
        case 3: input(); SRT();
        break;
        case 4: input(); RR();
        break;
    }
    cout << endl;
    output();
    return 0;
} 