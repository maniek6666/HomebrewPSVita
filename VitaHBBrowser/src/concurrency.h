#pragma once

#include <string>
#include <psp2/kernel/threadmgr.h>

#include "debug.h"

class SceMutex {
public:
	explicit SceMutex(const std::string& name="unnamed_mutex");
	SceMutex(const SceMutex&) = delete;
	~SceMutex();
	void lock();
	void unlock();

private:
	SceUID id;
	std::string name;
};
