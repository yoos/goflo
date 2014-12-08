#include <cstdlib>
#include <chrono>
#include <memory>

#include <opencv2/opencv.hpp>

#include "benchmarker.hpp"
#include "optical_flow_engine.hpp"
#include "cpu_optical_flow_engine.hpp"
#include "gpu_optical_flow_engine.hpp"

void usage() {
  std::cerr << "Usage: goflo --cpu|--gpu <winsize>" << std::endl;
}

int main(int argc, char **argv) {
  if(argc < 3) {
    usage();
    return EXIT_FAILURE;
  }

  int winsize = atoi(argv[2]);

  std::unique_ptr<OpticalFlowEngine> engine;
  if(strcmp(argv[1], "--cpu") == 0) {
    engine = std::make_unique<CPUOpticalFlowEngine>(winsize);
    std::cout << "CPU blocksize " << winsize << ": ";
  } else if(strcmp(argv[1], "--gpu") == 0) {
    engine = std::make_unique<GPUOpticalFlowEngine>(winsize);
    std::cout << "GPU blocksize " << winsize << ": ";
  } else {
    usage();
    return EXIT_FAILURE;
  }

  Benchmarker benchmarker(std::move(engine));
  cv::VideoCapture capture("vid.mp4");
  //capture.set(CV_CAP_PROP_FRAME_WIDTH, 640 );
  //capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480 );

  if(!capture.isOpened()) {
    std::cerr << "Failed to open capture device" << std::endl;
    return EXIT_FAILURE;
  }

  cv::namedWindow("frame");

  // Grab the initial frame
  cv::Mat prevFrame;

  capture >> prevFrame;
  cv::cvtColor(prevFrame, prevFrame, cv::COLOR_BGR2GRAY);

  for (int loop=0; loop<50; loop++) {
    // Grab the current frame
    cv::Mat curFrame;
    capture >> curFrame;

    // Copy the frame to a "debug" image so we don't draw over the original
    cv::Mat drawnFrame; // = curFrame.clone();
    drawnFrame = cv::Mat::zeros(curFrame.size(), curFrame.type());

    auto pair = benchmarker.benchFrame(prevFrame, curFrame);
    auto duration = pair.first;
    auto flow = pair.second;

    //std::cout << "Frame completed in " << duration.count() << "ms." << std::endl;
    std::cout << duration.count() << ", ";

    for(int y = 0; y < flow[0].rows; y += 5) {
      for(int x = 0; x < flow[0].cols; x += 5) {
        //const cv::Point2f& dxdy = flow.at<cv::Point2f>(y, x);

        const cv::Point2f p1 = flow[0].at<cv::Point2f>(y, x);
        const cv::Point2f p2 = flow[1].at<cv::Point2f>(y, x);
        int sumSquare = std::pow((p2.x-p1.x), 2) + std::pow((p2.y-p1.y), 2);
        cv::line(drawnFrame, cv::Point(x, y), cv::Point(x+p1.x, y+p1.y), cv::Scalar(255, 0, 0));   // TODO(yoos): This doesn't draw correctly.

        //const cv::Point2f dxdy(flow[1](y,x), flow[0](y,x));
        //int sumSquare = std::pow(dxdy.x, 2) + std::pow(dxdy.y, 2);
        // cv::circle(drawnFrame, cv::Point(x, y), std::sqrt(sumSquare) / 2, cv::Scalar(0, 0, sumSquare, 100), -1);
        //cv::line(drawnFrame, cv::Point(x, y), cv::Point(x + dxdy.x, y + dxdy.y), cv::Scalar(255, 0, 0));
      }
    }

    imshow("frame", drawnFrame);
    if(cv::waitKey(30) >= 0) {
      break;
    }

    // Current frame is now the previous frame
    prevFrame = curFrame;
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
