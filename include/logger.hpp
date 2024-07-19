//
// Created by mahdi on 7/17/24.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

// Check if __has_include is supported
#ifdef __has_include
// Check for presence of <print> header
#if __has_include(<print>) && __cplusplus >= 202002L
#include <print>
#define HAS_STD_PRINT 1
#else
#include <iostream>
#define HAS_STD_PRINT 0
#endif
#else
// If __has_include is not supported, fall back to <iostream>
#include <iostream>
#define HAS_STD_PRINT 0
#endif

#ifdef __has_include
#if __has_include(<source_location>) && __cplusplus >= 202002L
#include <source_location>
#define HAS_SOURCE_LOCATION 1
#else
#define HAS_SOURCE_LOCATION 0
#endif
#else
#define HAS_SOURCE_LOCATION 0
#endif

#if HAS_SOURCE_LOCATION
void log(std::string const &message,
         const std::source_location location = std::source_location::current());

#else

void log(std::string const &message, const char *file, int line,
         const char *function);

#define LOG(message) log(message, __FILE__, __LINE__, __func__)

#endif

#endif // LOGGER_HPP
