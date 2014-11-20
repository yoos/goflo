#include "gpu_optical_flow_engine.hpp"

cv::Mat GPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::gpu::GpuMat gpuPrevFrame(prevFrame);
  cv::gpu::GpuMat gpuNextFrame(nextFrame);

  cv::gpu::GpuMat gpuFlowX;
  cv::gpu::GpuMat gpuFlowY;
  
  opticalFlow(gpuPrevFrame, gpuNextFrame, gpuFlowX, gpuFlowY);

  cv::Mat flow;
  gpuFlowX.download(flow); // TODO(kyle): Use both X and Y directions

  return flow;
}
