#include<iostream>
#include<chrono>
#include<vector>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;
using namespace chrono;

void parallelBubbleSort(vector<int>& arr){
    int n=arr.size();
    
    #pragma omp parallel for
    for(int i=0;i<n-1;++i){
        for(int j=0;j<n-i-1;++j){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void SeqBubbleSort(vector<int>& arr){
    int n=arr.size();

    for(int i=0;i<n-1;++i){
        for(int j=0;j<n-i-1;++j){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid-left+1;
    int n2 = right-mid;

    vector<int>L(n1),R(n2);
    for(int i=0;i<n1;++i){
        L[i]=arr[left+i];
    }
    for(int j=0;j<n2;++j){
        R[j]=arr[mid+j+1];
    }

    int i=0,j=0,k=left;
    while(i<n1 && j<n2){
        if(L[i] <= R[j]){
            arr[k]=L[i];
            ++i;
        }
        else{
            arr[k]=R[j];
            ++j;
        }
        ++k;
    }

    while(i<n1){
        arr[k]=L[i];
            ++i;
            ++k;
    }
    while(j<n2){
        arr[k]=R[j];
            ++j;
            ++k;
    }
}

void parallelMergeSort(vector<int>& arr, int left, int right){
    if(left < right){
        int mid = left+(right-left)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr,left,mid);
            #pragma omp section
            parallelMergeSort(arr,mid+1,right);
        }
        merge(arr,left,mid,right);
    }
}

void SeqMergeSort(vector<int>& arr, int left, int right){
    if(left < right){
        int mid = left+(right-left)/2;
        {
            parallelMergeSort(arr,left,mid);
            parallelMergeSort(arr,mid+1,right);
        }
        merge(arr,left,mid,right);
    }
}

void isSorted(vector<int>& arr1, vector<int>& arr2){
    sort(arr2.begin(),arr2.end());
    if(arr1 == arr2){
        cout<<"Array is Sorted. "<<endl;
    }
    else{
        cout<<"Array is Not Sorted. "<<endl;
    }
}

void showarray(vector<int> &arr){
    for(auto val : arr){
        cout<<val<<" ";
    }
    cout<<endl;
}

int main(){

    vector<int> arr;

    for(int i=15;i>=0;i--){
        arr.push_back(i);
    }
    int n=arr.size();

    vector<int> arr1=arr;
    auto start_time=high_resolution_clock::now();
    parallelBubbleSort(arr1);
    auto end_time=high_resolution_clock::now();
    auto duration=duration_cast<milliseconds>(end_time-start_time);
    showarray(arr1);
    isSorted(arr1,arr);
    cout<<"Parallel Bubble Sort executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    vector<int> arr2=arr;
    start_time=high_resolution_clock::now();
    parallelMergeSort(arr2,0,n-1);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    showarray(arr2);
    isSorted(arr2,arr);
    cout<<"Parallel Merge Sort executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    vector<int> arr3=arr;
    start_time=high_resolution_clock::now();
    SeqBubbleSort(arr3);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    showarray(arr3);
    isSorted(arr3,arr);
    cout<<"Sequential Bubble Sort executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;

    vector<int> arr4=arr;
    start_time=high_resolution_clock::now();
    SeqMergeSort(arr2,0,n-1);
    end_time=high_resolution_clock::now();
    duration=duration_cast<milliseconds>(end_time-start_time);
    showarray(arr4);
    isSorted(arr4,arr);
    cout<<"Sequential Merge Sort executed in "<<duration.count()<<" milliseconds."<<endl;
    cout<<endl;


    return 0;
}