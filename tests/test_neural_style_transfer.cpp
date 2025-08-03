#include <gtest/gtest.h>
#include "style_transfer/neural_style_transfer.hpp"
#include <opencv2/opencv.hpp>
#include <filesystem>

namespace fs = std::filesystem;

class NeuralStyleTransferTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Create a simple test style image
        test_style_path_ = "test_style.jpg";
        createTestStyleImage();
    }

    void TearDown() override
    {
        // Clean up test files
        if (fs::exists(test_style_path_))
        {
            fs::remove(test_style_path_);
        }
    }

    void createTestStyleImage()
    {
        // Create a simple test style image
        cv::Mat style_image(256, 256, CV_8UC3, cv::Scalar(50, 100, 150));

        // Add some pattern to make it more interesting
        cv::rectangle(style_image, cv::Rect(50, 50, 156, 156), cv::Scalar(200, 50, 100), -1);
        cv::circle(style_image, cv::Point(128, 128), 50, cv::Scalar(100, 200, 50), -1);

        cv::imwrite(test_style_path_, style_image);
    }

    std::string test_style_path_;
};

TEST_F(NeuralStyleTransferTest, DefaultConstructor)
{
    video_styler::style_transfer::NeuralStyleTransfer nst;
    EXPECT_FALSE(nst.isStyleLoaded());
}

TEST_F(NeuralStyleTransferTest, LoadNonExistentStyleImage)
{
    video_styler::style_transfer::NeuralStyleTransfer nst;
    EXPECT_FALSE(nst.loadStyleImage("non_existent_style.jpg"));
    EXPECT_FALSE(nst.isStyleLoaded());
}

TEST_F(NeuralStyleTransferTest, LoadValidStyleImage)
{
    if (!fs::exists(test_style_path_))
    {
        GTEST_SKIP() << "Could not create test style image";
    }

    video_styler::style_transfer::NeuralStyleTransfer nst;
    EXPECT_TRUE(nst.loadStyleImage(test_style_path_));
    EXPECT_TRUE(nst.isStyleLoaded());
}

TEST_F(NeuralStyleTransferTest, SetParameters)
{
    video_styler::style_transfer::NeuralStyleTransfer nst;

    // Test setting parameters (no direct way to verify, but should not crash)
    EXPECT_NO_THROW(nst.setParameters(1000, 2e6, 2.0));
}

TEST_F(NeuralStyleTransferTest, ApplyStyleTransferWithoutStyle)
{
    video_styler::style_transfer::NeuralStyleTransfer nst;

    cv::Mat input_frame(480, 640, CV_8UC3, cv::Scalar(128, 128, 128));
    cv::Mat output_frame;

    // Should fail without loaded style
    EXPECT_FALSE(nst.applyStyleTransfer(input_frame, output_frame));
}

TEST_F(NeuralStyleTransferTest, ApplyStyleTransferWithStyle)
{
    if (!fs::exists(test_style_path_))
    {
        GTEST_SKIP() << "Could not create test style image";
    }

    video_styler::style_transfer::NeuralStyleTransfer nst;
    nst.loadStyleImage(test_style_path_);

    cv::Mat input_frame(480, 640, CV_8UC3, cv::Scalar(128, 128, 128));
    cv::Mat output_frame;

    // Should succeed with loaded style
    EXPECT_TRUE(nst.applyStyleTransfer(input_frame, output_frame));
    EXPECT_FALSE(output_frame.empty());
    EXPECT_EQ(output_frame.size(), input_frame.size());
}
