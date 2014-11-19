#include <cstdlib>
#include <chrono>
#include <memory>

#include <opencv2/opencv.hpp>

#include "benchmarker.hpp"
#include "optical_flow_engine.hpp"
#include "cpu_optical_flow_engine.hpp"
#include "gpu_optical_flow_engine.hpp"

void usage() {
  std::cerr << "Usage: goflo --cpu|--gpu" << std::endl;
}

int main(int argc, char **argv) {
  if(argc < 2) {
    usage();
    return EXIT_FAILURE;
  }

  std::unique_ptr<OpticalFlowEngine> engine;
  if(strcmp(argv[1], "--cpu") == 0) {
    engine = std::make_unique<CPUOpticalFlowEngine>();
  } else if(strcmp(argv[1], "--gpu") == 0) {
    engine = std::make_unique<GPUOpticalFlowEngine>();
  } else {
    usage();
    return EXIT_FAILURE;
  }

  Benchmarker benchmarker(std::move(engine));
  cv::VideoCapture capture(0);

  if(!capture.isOpened()) {
    std::cerr << "Failed to open capture device" << std::endl;
    return EXIT_FAILURE;
  }

  cv::namedWindow("frame");

  // Grab the initial frame
  cv::Mat prevFrame;

  capture >> prevFrame;
  cv::cvtColor(prevFrame, prevFrame, cv::COLOR_BGR2GRAY);

  while(true) {
    // Grab the current frame
    cv::Mat curFrame;
    capture >> curFrame;

    // Copy the frame to a "debug" image so we don't draw over the original
    cv::Mat drawnFrame; // = curFrame.clone();
    drawnFrame = cv::Mat::zeros(curFrame.size(), curFrame.type());

    auto pair = benchmarker.benchFrame(prevFrame, curFrame);
    auto duration = pair.first;
    auto flow = pair.second;

    std::cout << "Frame completed in " << duration.count() << "ms." << std::endl;

    for(int y = 0; y < flow.rows; y += 5) {
      for(int x = 0; x < flow.cols; x += 5) {
        const cv::Point2f& dxdy = flow.at<cv::Point2f>(y, x);

        int sumSquare = std::pow(dxdy.x, 2) + std::pow(dxdy.y, 2);
        // cv::circle(drawnFrame, cv::Point(x, y), std::sqrt(sumSquare) / 2, cv::Scalar(0, 0, sumSquare, 100), -1);
        cv::line(drawnFrame, cv::Point(x, y), cv::Point(x + dxdy.x, y + dxdy.y), cv::Scalar(255, 0, 0));
      }
    }

    imshow("frame", drawnFrame);
    if(cv::waitKey(30) >= 0) {
      break;
    }

    // Current frame is now the previous frame
    prevFrame = curFrame;
  }

  return EXIT_SUCCESS;
}
