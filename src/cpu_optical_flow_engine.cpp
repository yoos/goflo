#include "cpu_optical_flow_engine.hpp"

cv::Mat CPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::Mat flow;
  cv::calcOpticalFlowFarneback(prevFrame, nextFrame, flow, 0.5, 5, 13, 10, 5, 1.1, 0);

  return flow;
}
