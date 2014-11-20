#include "gpu_optical_flow_engine.hpp"

cv::Mat GPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::ocl::oclMat gpuPrevFrame(prevFrame);
  cv::ocl::oclMat gpuNextFrame(nextFrame);

  cv::ocl::oclMat gpuFlowX;
  cv::ocl::oclMat gpuFlowY;

  cv::ocl::FarnebackOpticalFlow opticalFlow;
  
  opticalFlow(gpuPrevFrame, gpuNextFrame, gpuFlowX, gpuFlowY);

  cv::Mat flow;
  gpuFlowX.download(flow); // TODO(kyle): Use both X and Y directions

  return flow;
}
