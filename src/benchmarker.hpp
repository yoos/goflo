#pragma once

#include <chrono>
#include <memory>
#include <utility>

#include "optical_flow_engine.hpp"

class Benchmarker {
public:
  Benchmarker(std::unique_ptr<OpticalFlowEngine> engine);
  std::pair<std::chrono::milliseconds, cv::Mat> benchFrame(cv::Mat& prevFrame, cv::Mat &nextFrame);

private:
  std::unique_ptr<OpticalFlowEngine> engine;
};
