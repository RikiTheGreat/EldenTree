//
// Created by mahdi on 7/17/24.
//

#include "logger.hpp"

#if HAS_SOURCE_LOCATION
void log(std::string const &message,
         const std::source_location location) {
#if HAS_STD_PRINT
    std::println("file: {} ({}:{}) in function {}, Error -> {}", location.file_name(),
                 location.line(), location.column(), location.function_name(), message);

#else
    std::clog << "file: "
              << location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';

#endif
}

#else
void log(std::string const &message,
         const char *file,
         int line,
         const char *function) {
    std::cout << "Log message: " << message << std::endl
              << "Location: " << file << ":" << line << " in function " << function << std::endl;
}

#endif