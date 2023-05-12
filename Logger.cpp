// LFInteractive LLC. - All Rights Reserved
#include "Logger.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
spdlog::logger Logger::log = Logger::make_logger();

spdlog::logger Logger::make_logger()
{
	// Setup console sink
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::info);
	console_sink->set_pattern("%^[Line Scanner] [%l]%$ %v");

	// Setup file sink
	auto default_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/latest.log", true);
	default_file_sink->set_level(spdlog::level::trace);
	default_file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [Line Scanner] [%l] %v");

	// Setup completed logger
	spdlog::sinks_init_list sink_list = { console_sink, default_file_sink };
	spdlog::logger logger("line_scanner_sink", sink_list.begin(), sink_list.end());
	logger.set_level(spdlog::level::trace);

	return logger;
}