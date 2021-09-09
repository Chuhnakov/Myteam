#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

using namespace std;

enum class Status {ready,busy};
Status rollcallStatus = Status::ready;
mutex rollcall_mutex;
condition_variable rollcall_condition;


void rollCall(int num)
{
    unique_lock<mutex> ul(rollcall_mutex);

    if (rollcallStatus == Status::busy)
    {
        rollcall_condition.wait(ul, [=]() { return rollcallStatus == Status::ready;});
    }

    rollcallStatus = Status::busy;
    cout << num << endl;

    rollcall_condition.notify_one();

    rollcallStatus = Status::ready;
}

int main()
{        
    cout << "Hello World!" << endl;

    thread t1(rollCall,1);
    thread t2(rollCall,2);
    t1.detach();
    t2.detach();

    system("pause");

    return 0;
}
