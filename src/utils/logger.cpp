#include "utils/logger.hpp"

namespace video_styler::utils
{

    std::shared_ptr<Logger> Logger::instance_ = nullptr;

    std::shared_ptr<Logger> Logger::getInstance()
    {
        if (!instance_)
        {
            instance_ = std::shared_ptr<Logger>(new Logger());
        }
        return instance_;
    }

    void Logger::setLogLevel(LogLevel level)
    {
        min_level_ = level;
    }

    void Logger::debug(const std::string &message)
    {
        log(LogLevel::DEBUG, message);
    }

    void Logger::info(const std::string &message)
    {
        log(LogLevel::INFO, message);
    }

    void Logger::warning(const std::string &message)
    {
        log(LogLevel::WARNING, message);
    }

    void Logger::error(const std::string &message)
    {
        log(LogLevel::ERROR, message);
    }

    void Logger::setLogFile(const std::string &filename)
    {
        if (file_stream_.is_open())
        {
            file_stream_.close();
        }

        if (!filename.empty())
        {
            log_file_ = filename;
            file_stream_.open(log_file_, std::ios::app);
        }
    }

    void Logger::log(LogLevel level, const std::string &message)
    {
        if (level < min_level_)
        {
            return;
        }

        const std::string timestamp = getCurrentTimestamp();
        const std::string level_str = levelToString(level);
        const std::string log_message = "[" + timestamp + "] [" + level_str + "] " + message;

        // Output to console
        if (level >= LogLevel::ERROR)
        {
            std::cerr << log_message << std::endl;
        }
        else
        {
            std::cout << log_message << std::endl;
        }

        // Output to file if enabled
        if (file_stream_.is_open())
        {
            file_stream_ << log_message << std::endl;
            file_stream_.flush();
        }
    }

    std::string Logger::levelToString(LogLevel level) const
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARNING:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
        }
    }

    std::string Logger::getCurrentTimestamp() const
    {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) %
                  1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
        ss << '.' << std::setfill('0') << std::setw(3) << ms.count();

        return ss.str();
    }

} // namespace video_styler::utils
