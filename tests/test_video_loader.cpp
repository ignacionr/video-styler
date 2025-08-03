#include <gtest/gtest.h>
#include "video_processor/video_loader.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

class VideoLoaderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a simple test video for testing
        test_video_path_ = "test_video.mp4";
        createTestVideo();
    }

    void TearDown() override
    {
        // Clean up test files
        if (fs::exists(test_video_path_))
        {
            fs::remove(test_video_path_);
        }
    }

    void createTestVideo()
    {
        // Create a simple test video with OpenCV
        cv::VideoWriter writer(
            test_video_path_,
            cv::VideoWriter::fourcc('M', 'P', '4', 'V'),
            30.0, // FPS
            cv::Size(640, 480));

        if (!writer.isOpened())
        {
            return; // Skip tests if we can't create test video
        }

        // Create 10 frames of test video
        for (int i = 0; i < 10; ++i)
        {
            cv::Mat frame(480, 640, CV_8UC3, cv::Scalar(i * 25, 100, 200));
            writer.write(frame);
        }
        writer.release();
    }

    std::string test_video_path_;
};

TEST_F(VideoLoaderTest, DefaultConstructor)
{
    video_styler::video_processor::VideoLoader loader;
    EXPECT_FALSE(loader.isLoaded());
    EXPECT_EQ(loader.getFrameCount(), 0);
    EXPECT_EQ(loader.getFPS(), 0.0);
    EXPECT_EQ(loader.getWidth(), 0);
    EXPECT_EQ(loader.getHeight(), 0);
}

TEST_F(VideoLoaderTest, LoadNonExistentVideo)
{
    video_styler::video_processor::VideoLoader loader;
    EXPECT_FALSE(loader.loadVideo("non_existent_video.mp4"));
    EXPECT_FALSE(loader.isLoaded());
}

TEST_F(VideoLoaderTest, LoadValidVideo)
{
    if (!fs::exists(test_video_path_))
    {
        GTEST_SKIP() << "Could not create test video file";
    }

    video_styler::video_processor::VideoLoader loader;
    EXPECT_TRUE(loader.loadVideo(test_video_path_));
    EXPECT_TRUE(loader.isLoaded());
    EXPECT_EQ(loader.getWidth(), 640);
    EXPECT_EQ(loader.getHeight(), 480);
    EXPECT_NEAR(loader.getFPS(), 30.0, 1.0);
    EXPECT_GT(loader.getFrameCount(), 0);
}

TEST_F(VideoLoaderTest, VideoProperties)
{
    if (!fs::exists(test_video_path_))
    {
        GTEST_SKIP() << "Could not create test video file";
    }

    video_styler::video_processor::VideoLoader loader;
    loader.loadVideo(test_video_path_);

    // Test that we can get the video capture object
    cv::VideoCapture &cap = loader.getCapture();
    EXPECT_TRUE(cap.isOpened());
}
