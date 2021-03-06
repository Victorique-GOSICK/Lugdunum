#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <lug/System/Export.hpp>

namespace lug {
namespace System {
namespace Logger {

class Logger;
class Handler;

class LUG_SYSTEM_API LoggingFacility {
public:
    LoggingFacility() = delete;
    ~LoggingFacility() = delete;

public:
    static void registerLogger(const std::string& loggerName, std::unique_ptr<Logger> logger);
    static Logger* getLogger(const std::string& loggerName);

    static void registerHandler(const std::string& handlerName, std::unique_ptr<Handler> handler);
    static Handler* getHandler(const std::string& handlerName);

    static void clear();
};

} // Logger
} // System
} // lug
