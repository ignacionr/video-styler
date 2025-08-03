#include <iostream>
#include <string>
#include <filesystem>
#include <boost/program_options.hpp>
#include <opencv2/opencv.hpp>

#include "video_processor/video_loader.hpp"
#include "style_transfer/neural_style_transfer.hpp"
#include "utils/logger.hpp"

namespace po = boost::program_options;
namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    try
    {
        // Program options
        po::options_description desc("Video Styler - Neural Style Transfer for Videos");
        desc.add_options()("help,h", "Show help message")("input,i", po::value<std::string>(), "Input video file path")("output,o", po::value<std::string>(), "Output video file path")("style,s", po::value<std::string>(), "Style image file path")("verbose,v", "Enable verbose logging")("version", "Show version information");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // Handle help and version
        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm.count("version"))
        {
            std::cout << "Video Styler v0.1.0" << std::endl;
            std::cout << "Built with C++23 and OpenCV " << CV_VERSION << std::endl;
            return 0;
        }

        // Setup logger
        auto logger = video_styler::utils::Logger::getInstance();
        if (vm.count("verbose"))
        {
            logger->setLogLevel(video_styler::utils::LogLevel::DEBUG);
        }

        logger->info("Video Styler starting...");

        // Validate required arguments
        if (!vm.count("input") || !vm.count("output") || !vm.count("style"))
        {
            std::cerr << "Error: input, output, and style arguments are required." << std::endl;
            std::cerr << "Use --help for more information." << std::endl;
            return 1;
        }

        const std::string input_path = vm["input"].as<std::string>();
        const std::string output_path = vm["output"].as<std::string>();
        const std::string style_path = vm["style"].as<std::string>();

        // Validate input files exist
        if (!fs::exists(input_path))
        {
            logger->error("Input video file does not exist: " + input_path);
            return 1;
        }

        if (!fs::exists(style_path))
        {
            logger->error("Style image file does not exist: " + style_path);
            return 1;
        }

        logger->info("Input video: " + input_path);
        logger->info("Output video: " + output_path);
        logger->info("Style image: " + style_path);

        // Initialize components
        auto video_loader = video_styler::video_processor::VideoLoader();
        auto style_transfer = video_styler::style_transfer::NeuralStyleTransfer();

        // Load video
        if (!video_loader.loadVideo(input_path))
        {
            logger->error("Failed to load input video");
            return 1;
        }

        // Load style image
        if (!style_transfer.loadStyleImage(style_path))
        {
            logger->error("Failed to load style image");
            return 1;
        }

        logger->info("Successfully loaded video and style image");
        logger->info("Video properties:");
        logger->info("  - Frame count: " + std::to_string(video_loader.getFrameCount()));
        logger->info("  - FPS: " + std::to_string(video_loader.getFPS()));
        logger->info("  - Width: " + std::to_string(video_loader.getWidth()));
        logger->info("  - Height: " + std::to_string(video_loader.getHeight()));

        // Process video (placeholder for now)
        logger->info("Starting style transfer processing...");

        // TODO: Implement actual neural style transfer processing
        // For now, just demonstrate the framework is working
        logger->warning("Neural style transfer not yet implemented - this is a placeholder");

        // Copy input to output as demonstration
        cv::VideoCapture cap(input_path);
        cv::VideoWriter writer(
            output_path,
            cv::VideoWriter::fourcc('M', 'P', '4', 'V'),
            video_loader.getFPS(),
            cv::Size(video_loader.getWidth(), video_loader.getHeight()));

        cv::Mat frame;
        int frame_count = 0;
        while (cap.read(frame))
        {
            // TODO: Apply style transfer to frame
            writer.write(frame);
            frame_count++;

            if (frame_count % 30 == 0)
            {
                logger->info("Processed " + std::to_string(frame_count) + " frames");
            }
        }

        cap.release();
        writer.release();

        logger->info("Video processing completed successfully!");
        logger->info("Output saved to: " + output_path);

        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
}
