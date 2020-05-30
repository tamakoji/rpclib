#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include "rpc/server.h"

std::atomic<bool> run_thread(true);

void end(){
    run_thread = false;
}

void thread1() {
    // Create a server that listens on port 8080,
    // or whatever the user selected
    rpc::server srv("0.0.0.0", rpc::constants::DEFAULT_PORT);

    // Binding a lambda function "foo"
    srv.bind("foo", []() { std::cout << "foo" << std::endl;});

    // Binding a lambda function "bar"
    srv.bind("bar", []() { std::cout << "bar" << std::endl;});

    // Binding a lambda function "end"
    srv.bind("end", &end);

    // no throw
    srv.suppress_exceptions(true);

    // loop
    while (run_thread) {
        srv.run_for(10u);
    }
}

void thread2() {
    uint32_t cnt = 0;
    while (run_thread) {
        std::cout << "thread2 cnt:" << cnt++ << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
}

int main() {
    
    // Run the thread
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    std::cout << "exited thread1" << std::endl;
    t2.join();
    std::cout << "exited thread2" << std::endl;
    return 0;
}
