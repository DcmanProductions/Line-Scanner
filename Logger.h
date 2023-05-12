// LFInteractive LLC. - All Rights Reserved
#pragma once

#include <stdio.h>
#include "spdlog/spdlog.h"

class Logger
{
public:
	static spdlog::logger log;
private:
	static spdlog::logger make_logger();
	Logger() { log = make_logger(); }
	Logger(const spdlog::logger&) = delete;
	Logger& operator=(const spdlog::logger&) = delete;
};
