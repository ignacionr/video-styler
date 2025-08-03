#pragma once

#include <string>
#include <opencv2/opencv.hpp>

namespace video_styler::style_transfer
{

    /**
     * @brief NeuralStyleTransfer class for applying style transfer to images/frames
     */
    class NeuralStyleTransfer
    {
    public:
        NeuralStyleTransfer() = default;
        ~NeuralStyleTransfer() = default;

        // Non-copyable, movable
        NeuralStyleTransfer(const NeuralStyleTransfer &) = delete;
        NeuralStyleTransfer &operator=(const NeuralStyleTransfer &) = delete;
        NeuralStyleTransfer(NeuralStyleTransfer &&) = default;
        NeuralStyleTransfer &operator=(NeuralStyleTransfer &&) = default;

        /**
         * @brief Load a style image
         * @param filepath Path to the style image
         * @return true if successful, false otherwise
         */
        bool loadStyleImage(const std::string &filepath);

        /**
         * @brief Apply style transfer to a frame
         * @param input_frame The input frame to stylize
         * @param output_frame The output stylized frame
         * @return true if successful, false otherwise
         */
        bool applyStyleTransfer(const cv::Mat &input_frame, cv::Mat &output_frame);

        /**
         * @brief Check if a style image is loaded
         * @return true if style image is loaded
         */
        bool isStyleLoaded() const;

        /**
         * @brief Set style transfer parameters
         * @param iterations Number of optimization iterations
         * @param style_weight Weight for style loss
         * @param content_weight Weight for content loss
         */
        void setParameters(int iterations = 500, double style_weight = 1e6, double content_weight = 1.0);

    private:
        cv::Mat style_image_;
        bool style_loaded_{false};

        // Style transfer parameters
        int iterations_{500};
        double style_weight_{1e6};
        double content_weight_{1.0};

        /**
         * @brief Initialize the neural network for style transfer
         */
        void initializeNetwork();

        /**
         * @brief Preprocess image for neural network
         * @param image Input image
         * @return Preprocessed image
         */
        cv::Mat preprocessImage(const cv::Mat &image);

        /**
         * @brief Postprocess image from neural network output
         * @param image Network output
         * @return Postprocessed image
         */
        cv::Mat postprocessImage(const cv::Mat &image);
    };

} // namespace video_styler::style_transfer
