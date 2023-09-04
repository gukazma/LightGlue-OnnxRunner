/*********************************
    Copyright: OroChippw
    Author: OroChippw
    Date: 2023.08.31
    Description:
*********************************/
#pragma once
#pragma warning(disable:4819) 

#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
// #include <cuda_provider_factory.h>  // 若在GPU环境下运行可以使用cuda进行加速

#include "Configuration.h"

class LightGlueOnnxRunner
{
private:
	const unsigned int num_threads;

    Ort::Env env;
    Ort::SessionOptions session_options;
    std::unique_ptr<Ort::Session> session;
    Ort::AllocatorWithDefaultOptions allocator;

    std::vector<char*> InputNodeNames;
    std::vector<std::vector<int64_t>> InputNodeShapes;

    std::vector<char*> OutputNodeNames;
    std::vector<std::vector<int64_t>> OutputNodeShapes;

    float matchThresh = 0.0f;
    float scale = 1.0f;

    float scales0 = 1.0f;
    float scales1 = 1.0f;

    std::vector<Ort::Value> output_tensors;

private:
    cv::Mat PreProcess(Configuration cfg , const cv::Mat& srcImage);
    int Inference(Configuration cfg , const cv::Mat& src , const cv::Mat& dest);
    std::pair<std::vector<float_t>, std::vector<float_t>> PostProcess(Configuration cfg);

public:
    explicit LightGlueOnnxRunner(unsigned int num_threads = 1);
    ~LightGlueOnnxRunner();

    float GetMatchThresh();
    void SetMatchThresh(float thresh);

    int InitOrtEnv(Configuration cfg);
    
    cv::Mat InferenceImage(Configuration cfg , \
            const cv::Mat& srcImage, const cv::Mat& destImage);

};