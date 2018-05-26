#pragma once

#include <memory>

#include <opencv2/core/types.hpp>

#include <opencv-glib/color.h>

GCVColor *gcv_color_new_raw(std::shared_ptr<cv::Scalar> *cv_color);
std::shared_ptr<cv::Scalar> gcv_color_get_raw(GCVColor *color);
