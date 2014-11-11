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

  // Find interesting features
  std::vector<cv::Point2f> originalPoints;
  cv::goodFeaturesToTrack(prevFrame, originalPoints, 500, 0.01, 1.0);

  while(true) {
    // Grab the current frame
    cv::Mat curFrame;
    capture >> curFrame;

    // Copy the frame to a "debug" image so we don't draw over the original
    cv::Mat drawnFrame = curFrame.clone();

    // Convert the frame to grayscale
    cv::cvtColor(curFrame, curFrame, cv::COLOR_BGR2GRAY);

    // Find the interesting points in the current frame
    std::vector<cv::Point2f> newPoints;
    cv::goodFeaturesToTrack(curFrame, newPoints, 100, 0.3, 7.0);

    // Draw the points to the debug frame
    for(auto k : originalPoints) {
      cv::circle(drawnFrame, k, 3, cv::Scalar(0, 0, 255));
    }

    // Calculate the optical flow using Lucas-Kanade method
    std::vector<unsigned char> statuses;
    std::vector<float> errors;
    cv::calcOpticalFlowPyrLK(prevFrame, curFrame, originalPoints, newPoints,
        statuses, errors, cv::Size(15, 15), 2,
        cv::TermCriteria(cv::TermCriteria::COUNT | cv::TermCriteria::EPS, 10, 0.03));

    // Draw arrows from all of the original points to their new locations
    for(int i = 0; i < newPoints.size(); i++) {
      // std::cout << "Error is " << errors[i] << std::endl;

      if(statuses[i] == 1) {
        cv::Point from(std::round(originalPoints[i].x), std::round(originalPoints[i].y));
        cv::Point to(std::round(newPoints[i].x), std::round(newPoints[i].y));

        cv::line(drawnFrame, from, to, cv::Scalar(255, 0, 0));
      }
    }

    imshow("frame", drawnFrame);
    if(cv::waitKey(30) >= 0) {
      break;
    }

    // // Current frame is now the previous frame
    // prevFrame = curFrame;
  }

  return EXIT_SUCCESS;
}
