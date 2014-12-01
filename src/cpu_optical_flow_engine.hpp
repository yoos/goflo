#pragma once

#include <opencv2/opencv.hpp>

#include "optical_flow_engine.hpp"

class CPUOpticalFlowEngine : public OpticalFlowEngine {
public:
  virtual std::vector<cv::Mat> process(cv::Mat& prevFrame, cv::Mat& nextFrame);
};
