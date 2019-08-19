#pragma once

#include <memory>

#include <opencv2/core/types.hpp>

#include <opencv-glib/point.h>

GCVPoint *gcv_point_new_raw(std::shared_ptr<cv::Point> *cv_point);
std::shared_ptr<cv::Point> gcv_point_get_raw(GCVPoint *point);
