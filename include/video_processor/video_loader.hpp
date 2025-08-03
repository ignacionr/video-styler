#pragma once

#include <string>
#include <opencv2/opencv.hpp>

namespace video_styler::video_processor
{

    /**
     * @brief VideoLoader class for loading and managing video files
     */
    class VideoLoader
    {
    public:
        VideoLoader() = default;
        ~VideoLoader() = default;

        // Non-copyable, movable
        VideoLoader(const VideoLoader &) = delete;
        VideoLoader &operator=(const VideoLoader &) = delete;
        VideoLoader(VideoLoader &&) = default;
        VideoLoader &operator=(VideoLoader &&) = default;

        /**
         * @brief Load a video file
         * @param filepath Path to the video file
         * @return true if successful, false otherwise
         */
        bool loadVideo(const std::string &filepath);

        /**
         * @brief Get the total number of frames in the video
         * @return Number of frames
         */
        int getFrameCount() const;

        /**
         * @brief Get the frames per second of the video
         * @return FPS value
         */
        double getFPS() const;

        /**
         * @brief Get the width of the video frames
         * @return Width in pixels
         */
        int getWidth() const;

        /**
         * @brief Get the height of the video frames
         * @return Height in pixels
         */
        int getHeight() const;

        /**
         * @brief Check if a video is currently loaded
         * @return true if video is loaded
         */
        bool isLoaded() const;

        /**
         * @brief Get the video capture object
         * @return Reference to the OpenCV VideoCapture object
         */
        cv::VideoCapture &getCapture();

    private:
        cv::VideoCapture video_capture_;
        bool is_loaded_{false};
        int frame_count_{0};
        double fps_{0.0};
        int width_{0};
        int height_{0};
    };

} // namespace video_styler::video_processor
