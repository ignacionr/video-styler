#include <gtest/gtest.h>
#include "utils/logger.hpp"
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

class LoggerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        test_log_file_ = "test_log.txt";
        // Clean up any existing test log file
        if (fs::exists(test_log_file_))
        {
            fs::remove(test_log_file_);
        }
    }

    void TearDown() override
    {
        // Clean up test files
        if (fs::exists(test_log_file_))
        {
            fs::remove(test_log_file_);
        }
    }

    std::string test_log_file_;
};

TEST_F(LoggerTest, SingletonPattern)
{
    auto logger1 = video_styler::utils::Logger::getInstance();
    auto logger2 = video_styler::utils::Logger::getInstance();

    // Should return the same instance
    EXPECT_EQ(logger1.get(), logger2.get());
}

TEST_F(LoggerTest, LogLevels)
{
    auto logger = video_styler::utils::Logger::getInstance();

    // Test setting different log levels (should not crash)
    EXPECT_NO_THROW(logger->setLogLevel(video_styler::utils::LogLevel::DEBUG));
    EXPECT_NO_THROW(logger->setLogLevel(video_styler::utils::LogLevel::INFO));
    EXPECT_NO_THROW(logger->setLogLevel(video_styler::utils::LogLevel::WARNING));
    EXPECT_NO_THROW(logger->setLogLevel(video_styler::utils::LogLevel::ERROR));
}

TEST_F(LoggerTest, LogMessages)
{
    auto logger = video_styler::utils::Logger::getInstance();
    logger->setLogLevel(video_styler::utils::LogLevel::DEBUG);

    // Test logging different types of messages (should not crash)
    EXPECT_NO_THROW(logger->debug("Debug message"));
    EXPECT_NO_THROW(logger->info("Info message"));
    EXPECT_NO_THROW(logger->warning("Warning message"));
    EXPECT_NO_THROW(logger->error("Error message"));
}

TEST_F(LoggerTest, FileLogging)
{
    auto logger = video_styler::utils::Logger::getInstance();
    logger->setLogFile(test_log_file_);

    const std::string test_message = "Test log message";
    logger->info(test_message);

    // Disable file logging to flush and close the file
    logger->setLogFile("");

    // Check if the log file was created and contains the message
    EXPECT_TRUE(fs::exists(test_log_file_));

    std::ifstream log_file(test_log_file_);
    EXPECT_TRUE(log_file.is_open());

    std::string line;
    bool found_message = false;
    while (std::getline(log_file, line))
    {
        if (line.find(test_message) != std::string::npos)
        {
            found_message = true;
            break;
        }
    }

    EXPECT_TRUE(found_message);
}

TEST_F(LoggerTest, LogLevelFiltering)
{
    auto logger = video_styler::utils::Logger::getInstance();
    logger->setLogFile(test_log_file_);
    logger->setLogLevel(video_styler::utils::LogLevel::WARNING);

    // Log messages at different levels
    logger->debug("Debug message - should not appear");
    logger->info("Info message - should not appear");
    logger->warning("Warning message - should appear");
    logger->error("Error message - should appear");

    // Disable file logging to flush and close the file
    logger->setLogFile("");

    // Check log file contents
    std::ifstream log_file(test_log_file_);
    std::string content((std::istreambuf_iterator<char>(log_file)),
                        std::istreambuf_iterator<char>());

    // Should not contain debug or info messages
    EXPECT_EQ(content.find("Debug message"), std::string::npos);
    EXPECT_EQ(content.find("Info message"), std::string::npos);

    // Should contain warning and error messages
    EXPECT_NE(content.find("Warning message"), std::string::npos);
    EXPECT_NE(content.find("Error message"), std::string::npos);
}
