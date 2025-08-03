#include "video_processor/video_loader.hpp"
#include <iostream>

namespace video_styler::video_processor
{

    bool VideoLoader::loadVideo(const std::string &filepath)
    {
        video_capture_.open(filepath);

        if (!video_capture_.isOpened())
        {
            is_loaded_ = false;
            return false;
        }

        // Get video properties
        frame_count_ = static_cast<int>(video_capture_.get(cv::CAP_PROP_FRAME_COUNT));
        fps_ = video_capture_.get(cv::CAP_PROP_FPS);
        width_ = static_cast<int>(video_capture_.get(cv::CAP_PROP_FRAME_WIDTH));
        height_ = static_cast<int>(video_capture_.get(cv::CAP_PROP_FRAME_HEIGHT));

        is_loaded_ = true;
        return true;
    }

    int VideoLoader::getFrameCount() const
    {
        return frame_count_;
    }

    double VideoLoader::getFPS() const
    {
        return fps_;
    }

    int VideoLoader::getWidth() const
    {
        return width_;
    }

    int VideoLoader::getHeight() const
    {
        return height_;
    }

    bool VideoLoader::isLoaded() const
    {
        return is_loaded_;
    }

    cv::VideoCapture &VideoLoader::getCapture()
    {
        return video_capture_;
    }

} // namespace video_styler::video_processor
