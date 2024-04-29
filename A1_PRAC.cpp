#include<iostream>
#include<chrono>
#include<stack>
#include<queue>
#include<omp.h>
#include<vector>

using namespace std;
using namespace chrono;

void parallelBFS(const vector<vector<int>>& graph, vector<bool>& visited, int source){
    queue<int>q;
    q.push(source);
    visited[source]=true;

    while(!q.empty()){
        int curr=q.front();
        q.pop();
        cout<<curr<<" ";

        #pragma omp parallel for shared(graph,visited,q)
        for(int i=0;i<graph[curr].size();++i){
            int neighbour=graph[curr][i];
            if(!visited[neighbour]){
                visited[neighbour]=true;
                q.push(neighbour);
            }
        }
    }
}

void SeqBFS(const vector<vector<int>>& graph, vector<bool>& visited, int source){
    queue<int>q;
    q.push(source);
    visited[source]=true;

    while(!q.empty()){
        int curr=q.front();
        q.pop();
        cout<<curr<<" ";

        for(int i=0;i<graph[curr].size();++i){
            int neighbour=graph[curr][i];
            if(!visited[neighbour]){
                visited[neighbour]=true;
                q.push(neighbour);
            }
        }
    }
}

void parallelDFS(const vector<vector<int>>& graph, vector<bool>& visited, int source){
    stack<int>s;
    s.push(source);
    visited[source]=true;

    while(!s.empty()){
        int curr=s.top();
        s.pop();
        cout<<curr<<" ";

        #pragma omp parallel for shared(graph,visited,s)
        for(int i=0;i<graph[curr].size();++i){
            int neighbour=graph[curr][i];
            if(!visited[neighbour]){
                visited[neighbour]=true;
                s.push(neighbour);
            }
        }
    }
}

void SeqDFS(const vector<vector<int>>& graph, vector<bool>& visited, int source){
    stack<int>s;
    s.push(source);
    visited[source]=true;

    while(!s.empty()){
        int curr=s.top();
        s.pop();
        cout<<curr<<" ";

        for(int i=0;i<graph[curr].size();++i){
            int neighbour=graph[curr][i];
            if(!visited[neighbour]){
                visited[neighbour]=true;
                s.push(neighbour);
            }
        }
    }
}

int main(){
    int numNodes=6;
    vector<vector<int>> graph(numNodes);
    graph[0]={1,2};
    graph[1]={0,3};
    graph[2]={0,4,5};
    graph[3]={1};
    graph[4]={2};
    graph[5]={2};

    int source=0;
    vector<bool> ParallelBFSVisited(numNodes,false);
    vector<bool> SeqBFSVisited(numNodes,false);
    vector<bool> ParallelDFSVisited(numNodes,false);
    vector<bool> SeqDFSVisited(numNodes,false);

    auto start_time=high_resolution_clock::now();
    parallelBFS(graph,ParallelBFSVisited,source);
    auto end_time=high_resolution_clock::now();
    auto duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Parallel BFS executed in "<<duration.count()<<" millseconds."<<endl;

    start_time=high_resolution_clock::now();
    SeqBFS(graph,SeqBFSVisited,source);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Sequential BFS executed in "<<duration.count()<<" millseconds."<<endl;

    start_time=high_resolution_clock::now();
    parallelDFS(graph,ParallelDFSVisited,source);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Parallel DFS executed in "<<duration.count()<<" millseconds."<<endl;

    start_time=high_resolution_clock::now();
    SeqDFS(graph,SeqDFSVisited,source);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Parallel DFS executed in "<<duration.count()<<" millseconds."<<endl;

    return 0;

}