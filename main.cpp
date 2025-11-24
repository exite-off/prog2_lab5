#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <syncstream>

void simulate(const std::string& name, int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    std::osyncstream(std::cout) << name << " (" << duration << "s) completed" << std::endl;
}

void slow(const std::string& name) {
    simulate(name, 7);
}

void quick(const std::string& name) {
    simulate(name, 1);
}

void work() {
    auto start = std::chrono::steady_clock::now();

    std::promise<void> p_a1, p_a4;
    std::shared_future<void> f_a1 = p_a1.get_future();
    std::shared_future<void> f_a4 = p_a4.get_future();

    auto branch1 = std::async(std::launch::async, [f_a1]() {
        slow("A2");
        f_a1.wait();
        quick("B");
        quick("D");
    });

    auto branch2 = std::async(std::launch::async, [f_a4]() {
        slow("A3");
        f_a4.wait();
        quick("C");
    });

    quick("A1");
    p_a1.set_value();

    quick("A4");
    p_a4.set_value();

    branch1.get();
    branch2.get();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    std::cout << "Running time: " << time.count() << "s" << std::endl;
    std::cout << "Work is done!" << std::endl;
}

int main() {
    work();
    return 0;
}