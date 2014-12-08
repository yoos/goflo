#include "gpu_optical_flow_engine.hpp"

std::vector<cv::Mat> GPUOpticalFlowEngine::process(cv::Mat& prevFrame, cv::Mat& nextFrame) {
  cv::gpu::GpuMat gpuPrevFrame(prevFrame);
  cv::gpu::GpuMat gpuNextFrame(nextFrame);

  cv::gpu::GpuMat gpuFlowX;
  cv::gpu::GpuMat gpuFlowY;
  
  opticalFlow(gpuPrevFrame, gpuNextFrame, gpuFlowX, gpuFlowY);
  cv::calcOpticalFlowFarneback(gpuPrevFrame, gpuNextFrame, gpuFlowX, 0.5, 5, 13, 10, 5, 1.1, 0);

  std::vector<cv::Mat> flow(2);
  gpuFlowX.download(flow[0]); // TODO(kyle): Use both X and Y directions
  gpuFlowY.download(flow[1]);

  return flow;
}
