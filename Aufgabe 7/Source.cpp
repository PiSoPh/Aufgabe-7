#include "Threads.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <conio.h>

std::mutex mute;
std::string outBuff; //output-Buffer

void start(int tnum, std::string m_text)
{

    int maxwidth = 20; //size predefined by Aufgabe 7
    for (size_t x = 0; x < maxwidth - m_text.length(); x++)
    {
        mute.lock(); //mutex is locked, everyting will be written to Output-Buffer
        outBuff = "";
        for (size_t j = 0; j < x; j++)
        {
            outBuff += "__"; //left side of word
        }
        outBuff += m_text;
        for (size_t j = x + m_text.length() + 1; j < maxwidth; j++)
        {
            outBuff += "__"; // right side
        }
        outBuff += "\n";

        std::cout << outBuff; //Output-Buffer is written to console
        mute.unlock(); //mutex gehts unlocked again

        // wait for 100ms (slow down or speed up the animation)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return;
}



int main()
{
    int num_threads = 20;
    bool running = true;
    std::string input = "";

    Threads* t = new Threads();

    while (running) {

        // add data from Inputbuffer to string
        while (_kbhit()) {
            char c = _getch();
            if (c == 'q')
                running = false;
            else
                input += c;
        }

        // create threads (20)
        std::vector<std::thread> v;
        for (int i = 0; i < num_threads; i++) {
            std::string text = "Foo" + std::to_string(i) + input;
            v.push_back(std::thread(start, i, text));
        }

        // wait for threads (otherwise this will crash)
        for (int i = 0; i < num_threads; i++) {
            v.at(i).join();
        }

        //break once all threads have finished
        system("cls");
    }

    return 0;
}