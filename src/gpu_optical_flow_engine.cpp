#include "gpu_optical_flow_engine.hpp"

cv::Mat GPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::gpu::GpuMat gpuPrevFrame;
  cv::gpu::GpuMat gpuNextFrame;

  gpuPrevFrame.upload(prevFrame);
  gpuNextFrame.upload(nextFrame);

  cv::gpu::GpuMat gpuFlowX;
  cv::gpu::GpuMat gpuFlowY;

  cv::gpu::FarnebackOpticalFlow opticalFlow;
  
  opticalFlow.operator()(gpuPrevFrame, gpuNextFrame, gpuFlowX, gpuFlowY);

  cv::Mat flow;
  gpuFlowX.download(flow); // TODO(kyle): Use both X and Y directions

  return flow;
}
