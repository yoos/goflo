#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/ocl/ocl.hpp>

#include "optical_flow_engine.hpp"

class GPUOpticalFlowEngine : public OpticalFlowEngine {
public:
  virtual std::vector<cv::Mat> process(cv::Mat& prevFrame, cv::Mat& nextFrame);
};
