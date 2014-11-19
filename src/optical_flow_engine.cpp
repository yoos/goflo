#include "optical_flow_engine.hpp"

void OpticalFlowEngine::prepareFrame(cv::Mat& frame) {
  cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
}


