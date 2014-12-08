#include "optical_flow_engine.hpp"

OpticalFlowEngine::OpticalFlowEngine(int winsize) : winsize(winsize) {
}

void OpticalFlowEngine::prepareFrame(cv::Mat& frame) {
  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
}


