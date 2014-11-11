#include <cstdlib>
#include <vector>

#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
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
    cv::Mat drawnFrame = curFrame.clone();

    // Convert the frame to grayscale
    cv::cvtColor(curFrame, curFrame, cv::COLOR_BGR2GRAY);

    cv::Mat flow;
    cv::calcOpticalFlowFarneback(prevFrame, curFrame, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

    for(int y = 0; y < flow.rows; y += 10) {
      for(int x = 0; x < flow.cols; x += 10) {
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
