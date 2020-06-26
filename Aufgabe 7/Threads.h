#pragma once
#include <iostream>
#include <mutex>
class Threads
{
public:
	Threads();
	~Threads();

	void thread(int tnum, std::string m_text);

	std::mutex mute;
	std::string outBuff; //output-Buffer

};

