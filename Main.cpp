// LFInteractive LLC. - All Rights Reserved

/// Default
#include <iostream>

/// SPD Logger
#include "Logger.h"

int main(int length, char* args[])
{
	spdlog::logger log = Logger::log;

	log.trace("Hello World");
	log.debug("Hello World");
	log.info("Hello World");
	log.warn("Hello World");
	log.error("Hello World");

	return 0;
}