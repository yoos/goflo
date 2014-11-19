#include "cpu_optical_flow_engine.hpp"

cv::Mat CPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::Mat flow;
  cv::calcOpticalFlowFarneback(prevFrame, nextFrame, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

  return flow;
}
