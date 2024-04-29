#include<iostream>
#include<chrono>
#include<omp.h>
#include<vector>

using namespace std;
using namespace chrono;

int parallelMin(vector<int>& values){
    int minVal=values[0];
    #pragma omp parallel for reduction(min:minVal)
    for(int i=1;i<values.size();++i){
        if(values[i]<minVal){
            minVal=values[i];
        }
    }
    return minVal;
}

int SeqMin(vector<int>& values){
    int minVal=values[0];
    for(int i=1;i<values.size();++i){
        if(values[i]<minVal){
            minVal=values[i];
        }
    }
    return minVal;
}

int parallelMax(vector<int>& values){
    int maxVal=values[0];
    #pragma omp parallel for reduction(max:maxVal)
    for(int i=1;i<values.size();++i){
        if(values[i]>maxVal){
            maxVal=values[i];
        }
    }
    return maxVal;
}

int parallelSum(vector<int>& values){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=1;i<values.size();++i){
        sum+= values[i];
    }
    return sum;
}

int parallelAvg(vector<int>& values){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=1;i<values.size();++i){
        sum+= values[i];
    }
    return sum*1.0 / values.size();
}

int main(){
    vector<int> values;
    for(int i=0;i<50;i++){
        values.push_back(i);
    }

    auto start_time= high_resolution_clock::now();
    int min=parallelMin(values);
    auto end_time= high_resolution_clock::now();
    auto duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Min by Paralle is: "<<min<<endl;
    cout<<"Parallel min executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    start_time= high_resolution_clock::now();
    int smin=SeqMin(values);
    end_time= high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Min by Seq is: "<<smin<<endl;
    cout<<"Seq min executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    start_time= high_resolution_clock::now();
    int max=parallelMax(values);
    end_time= high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Max by Paralle is: "<<max<<endl;
    cout<<"Parallel max executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    start_time= high_resolution_clock::now();
    int s=parallelSum(values);
    end_time= high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Sum by Paralle is: "<<s<<endl;
    cout<<"Parallel sum executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    start_time= high_resolution_clock::now();
    int avg=parallelAvg(values);
    end_time= high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    cout<<"Avg by Paralle is: "<<avg<<endl;
    cout<<"Parallel avg executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    return 0;

}


