#include "Threads.h"

Threads::Threads()
{
}

Threads::~Threads()
{
}

void Threads::thread(int tnum, std::string m_text)
{

    int maxwidth = 20; //size predefined by Aufgabe 7
    for (size_t x = 0; x < maxwidth - m_text.length(); x++)
    {
        mute.lock(); //mutex is locked, everyting will be written to Output-Buffer
        outBuff = "";
        for (size_t j = 0; j < x; j++)
        {
            outBuff += "___";
        }
        outBuff += m_text;
        for (size_t j = x + m_text.length() + 1; j < maxwidth; j++)
        {
            outBuff += "___";
        }
        outBuff += "\n";

        std::cout << outBuff; //Output-Buffer is written to console
        mute.unlock(); //mutex gehts unlocked again

        // wait for 100ms
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return;
}
