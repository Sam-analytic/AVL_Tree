#include <iostream>
#include<vector>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <fstream>
#include <iterator>

using namespace std;

vector<double> time_record;
vector<double>::iterator it;

void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    int i = 0;

    int j = 0;

    int k = l;
 
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 

void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;//returns recursively
    }
    int m =l+ (r-l)/2;
    mergeSort(arr,l,m);
    mergeSort(arr,m+1,r);
    merge(arr,l,m,r);
}
 
int main()
{
 
    struct timeval start, end;
    
    for(int i =1; i < 10000; ++i){
        
        int randomArray[i];
        for(int n = 0; n<i; ++n ){
            randomArray[n] = rand()%1000;
        }
        
        gettimeofday(&start, NULL);
        ios_base::sync_with_stdio(false);
    
        mergeSort(randomArray, 0, i - 1);
    
        gettimeofday(&end, NULL);
        double time_taken;
        time_taken = (end.tv_sec - start.tv_sec) * 1e6;
        time_taken = (time_taken + (end.tv_usec - start.tv_usec)) * 1e-6;
        time_record.push_back(time_taken);
        
    }
    for(it = time_record.begin(); it != time_record.end(); ++it){
            cout << *it << ",";
        }
    ofstream output_file("./time_record.csv");
    ostream_iterator<int> output_iterator(output_file, "\n");
    copy(time_record.begin(), time_record.end(), output_iterator);
    return 0;
}