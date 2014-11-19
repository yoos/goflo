#include "benchmarker.hpp"

Benchmarker::Benchmarker(std::unique_ptr<OpticalFlowEngine> engine)
  : engine(std::move(engine)) {
}

std::pair<std::chrono::milliseconds, cv::Mat> Benchmarker::benchFrame(cv::Mat& prevFrame, cv::Mat &nextFrame) {
  auto start = std::chrono::system_clock::now();

  engine->prepareFrame(nextFrame);
  cv::Mat flow = engine->process(prevFrame, nextFrame);

  auto end = std::chrono::system_clock::now();
  auto elapsed = end - start;

  return std::make_pair(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed), flow);
}
