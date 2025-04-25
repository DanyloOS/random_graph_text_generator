#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

#include "input.h"
#include "RandomGraphText.h"
#include "threadpool.h"

using namespace std;


void generateRandomGraph_singlethread(const Input &i) {
    std::string fileName = i.file_name;
    fileName += "__randomgraphtext_new.txt";
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Error! Cannot open file for writing: " << fileName << std::endl;
        return;
    }

    RandomGraphText::generateRandomGraph_new(i.nv, i.ne, std::move(file));
}
void generateRandomGraph_multithread() {
    ThreadPool pool(6);

    for (int i = 0; i < input_vector.size(); ++i) {
        pool.enqueue([i] {
            try {
                std::this_thread::sleep_for(std::chrono::milliseconds(500*i)); // sleep for 0.5 second
                std::cout << "Processing task " << i << " on thread "
                          << std::this_thread::get_id() << std::endl;
                generateRandomGraph_singlethread(input_vector[i]);
            } catch (const std::exception& e) {
                std::cerr << "Caught exception in thread: " << e.what() << '\n';
            } catch (...) {
                std::cerr << "Caught unknown exception in thread\n";
            }
        });
    }

    std::cout << "Finished giving all the jobs!" << std::endl;
}

// Example usage
void generateRandomGraph_multithread_helper() {
    std::cout << "Started giving all the jobs!" << std::endl;
    generateRandomGraph_multithread();
    std::cout << "Executed all the jobs!" << std::endl;
}

void generateRandomGraphText() {
    if (!input_vector.empty()) {
        try {
            // std::thread task_producer([]() {
            //     try {
            //         generateRandomGraph_multithread_helper();
            //     } catch (const std::exception& e) {
            //         std::cerr << "Caught exception in thread: " << e.what() << '\n';
            //     } catch (...) {
            //         std::cerr << "Caught unknown exception in thread\n";
            //     }
            //     // QMessageBox::information(this, "Success", "Started generating files");
            // });
            generateRandomGraph_multithread_helper();
        } catch (const std::exception& e) {
            std::cerr << "Caught exception in thread: " << e.what() << '\n';
        } catch (...) {
            std::cerr << "Caught unknown exception in thread\n";
        }
    }
}




int main()
{
    cout << "Hello World!" << endl;
    generateRandomGraphText();
    return 0;
}
