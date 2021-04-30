#include<iostream>
#include<vector>
#include <bits/stdc++.h>
#include <sys/time.h>
#include <fstream>
#include <iterator>

using namespace std;

vector<int> v(10000,2);
vector<int> v_push_front(100000, 2);
vector<int> test;
vector<int> test_push_front;
vector<int>::iterator it;
vector<double> push_back_time;
vector<double> pop_back_time;
vector<double> push_front_time;
vector<double>::iterator algo_it; //same iterator used everywhere to iterate over times for push_back into the time container
struct timeval start, end;

//overloading std vector with push_front

int main()
{   
    struct timeval start_push_back, end_push_back;
    for(it = v.begin(); it != v.end(); ++it){

        gettimeofday(&start_push_back, NULL);
        ios_base::sync_with_stdio(false);

        test.push_back(*it); //cycles of insertions

        gettimeofday(&end_push_back, NULL);
        double time_taken;
        time_taken = (end_push_back.tv_sec - start_push_back.tv_sec) * 1e6;
        time_taken = (time_taken + (end_push_back.tv_usec - start_push_back.tv_usec)) * 1e-6;
        push_back_time.push_back(time_taken);
    }

    ofstream output_file_back("./push_back.csv");
    ostream_iterator<double> output_back_iterator(output_file_back, "\n");
    copy(push_back_time.begin(), push_back_time.end(), output_back_iterator);

    struct timeval start_pop_back, end_pop_back;
    while(!test.empty()){

        gettimeofday(&start_pop_back, NULL);
        ios_base::sync_with_stdio(false);

        test.pop_back(); //cycles of insertions

        gettimeofday(&end_pop_back, NULL);
        double time_taken;
        time_taken = (end_pop_back.tv_sec - start_pop_back.tv_sec) * 1e6;
        time_taken = (time_taken + (end_pop_back.tv_usec - start_pop_back.tv_usec)) * 1e-6;
        pop_back_time.push_back(time_taken);
    }

    ofstream output_file_pop("./pop_back.csv");
    ostream_iterator<double> output_pop_iterator(output_file_pop, "\n");
    copy(pop_back_time.begin(), pop_back_time.end(), output_pop_iterator);

    struct timeval start_push_front, end_push_front;
    for(it = v_push_front.begin(); it != v_push_front.end(); ++it){

        gettimeofday(&start_push_front, NULL);
        ios_base::sync_with_stdio(false);

        test_push_front.insert(test_push_front.begin(), 1, *it); //cycles of insertions

        gettimeofday(&end_push_front, NULL);
        double time_taken;
        time_taken = (end_push_front.tv_sec - start_push_front.tv_sec) * 1e6;
        time_taken = (time_taken + (end_push_front.tv_usec - start_push_front.tv_usec)) * 1e-6;
        push_front_time.push_back(time_taken);
    }

    for(algo_it = push_front_time.begin(); algo_it != push_front_time.end(); ++algo_it){
        cout << *algo_it << ",";
    }

    ofstream output_file_front("./push_front.csv");
    ostream_iterator<double> output_front_iterator(output_file_front, "\n");
    copy(push_front_time.begin(), push_front_time.end(), output_front_iterator);

    return 0;
}