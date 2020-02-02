#pragma once

#include <memory>

#include <opencv2/core/types.hpp>

#include <opencv-glib/size.h>

GCVSize *gcv_size_new_raw(std::shared_ptr<cv::Size> *cv_size);
std::shared_ptr<cv::Size> gcv_size_get_raw(GCVSize *size);
