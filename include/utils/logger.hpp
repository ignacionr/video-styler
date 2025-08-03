#pragma once

#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace video_styler::utils
{

    /**
     * @brief Log levels for the logger
     */
    enum class LogLevel
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    /**
     * @brief Simple logger class with singleton pattern
     */
    class Logger
    {
    public:
        /**
         * @brief Get the singleton instance of the logger
         * @return Shared pointer to the logger instance
         */
        static std::shared_ptr<Logger> getInstance();

        // Non-copyable, non-movable
        Logger(const Logger &) = delete;
        Logger &operator=(const Logger &) = delete;
        Logger(Logger &&) = delete;
        Logger &operator=(Logger &&) = delete;

        /**
         * @brief Set the minimum log level
         * @param level Minimum log level to display
         */
        void setLogLevel(LogLevel level);

        /**
         * @brief Log a debug message
         * @param message The message to log
         */
        void debug(const std::string &message);

        /**
         * @brief Log an info message
         * @param message The message to log
         */
        void info(const std::string &message);

        /**
         * @brief Log a warning message
         * @param message The message to log
         */
        void warning(const std::string &message);

        /**
         * @brief Log an error message
         * @param message The message to log
         */
        void error(const std::string &message);

        /**
         * @brief Enable/disable file logging
         * @param filename Log file path (empty string disables file logging)
         */
        void setLogFile(const std::string &filename = "");

    private:
        // Helper struct to allow make_shared to access private constructor
        struct CreateLogger
        {
        };

    public:
        Logger(CreateLogger) : min_level_(LogLevel::INFO) {}

    private:
        static std::shared_ptr<Logger> instance_;
        LogLevel min_level_{LogLevel::INFO};
        std::string log_file_;
        std::ofstream file_stream_;

        /**
         * @brief Internal logging method
         * @param level Log level
         * @param message Message to log
         */
        void log(LogLevel level, const std::string &message);

        /**
         * @brief Get string representation of log level
         * @param level Log level
         * @return String representation
         */
        std::string levelToString(LogLevel level) const;

        /**
         * @brief Get current timestamp string
         * @return Formatted timestamp
         */
        std::string getCurrentTimestamp() const;
    };

} // namespace video_styler::utils
