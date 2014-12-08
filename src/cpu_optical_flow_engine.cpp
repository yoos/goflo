#include "cpu_optical_flow_engine.hpp"

CPUOpticalFlowEngine::CPUOpticalFlowEngine(int winsize) : OpticalFlowEngine(winsize) {
}

std::vector<cv::Mat> CPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  std::vector<cv::Mat> flow;
  cv::Mat tempflow;
  cv::calcOpticalFlowFarneback(prevFrame, nextFrame, tempflow, 0.5, 5, winsize, 10, 5, 1.1, 0);
  cv::split(tempflow, flow);

  return flow;
}
