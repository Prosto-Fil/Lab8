#include <iostream>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex myMutex;

vector<int> thmaxelem(3);

void max(vector<int>::iterator iter1, vector<int>::iterator iter2) 
{
    int localmax = *std::max_element(iter1, iter2);
    thmaxelem.push_back(localmax);
    myMutex.lock();
    cout << localmax << endl;
    cout << "Id of this thread " << this_thread::get_id() << endl;
    myMutex.unlock();
}


int main() 
{
    int n;
    cin >> n;

    vector<int> findmax;
    for (int i = 0; i < n; i++)
        findmax.push_back(rand());

    int num_elem = int(n / 3);

    size_t index1 = 0;
    size_t index2 = num_elem;

    chrono::system_clock::time_point start = chrono::system_clock::now();

    thread* mythreads[3];
    mythreads[0] = new thread(max, findmax.begin(), findmax.begin() + num_elem);
    mythreads[1] = new thread(max, findmax.begin() + num_elem, findmax.begin() + 2 * num_elem);
    mythreads[2] = new thread(max, findmax.begin() + 2 * num_elem, findmax.end());

    for (int i = 0; i < 3; i++)
        mythreads[i]->join();

    cout << endl << endl << endl << endl << endl;
    chrono::system_clock::time_point finish = chrono::system_clock::now();
    chrono::duration<double> def = finish - start;
    cout << "3 threads: " << endl;
    cout << "Max element is: " << *max_element(thmaxelem.begin(), thmaxelem.end()) << endl;
    cout << "Time used: " << def.count() << endl;


    cout << endl << endl << endl << endl << endl;
    cout << "1 thread: " << endl;
    chrono::system_clock::time_point start1 = chrono::system_clock::now();
    cout << "Max element is: " << *max_element(findmax.begin(), findmax.end()) << endl;
    chrono::system_clock::time_point finish1 = chrono::system_clock::now();
    chrono::duration<double> def1 = finish1 - start1;
    cout << "Time used: " << def1.count() << endl;
    
    return 0;
}