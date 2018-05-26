#pragma once

#include <memory>

#include <opencv2/core/types.hpp>

#include <opencv-glib/rectangle.h>

GCVRectangle *gcv_rectangle_new_raw(std::shared_ptr<cv::Rect> *cv_rectangle);
std::shared_ptr<cv::Rect> gcv_rectangle_get_raw(GCVRectangle *rectangle);
