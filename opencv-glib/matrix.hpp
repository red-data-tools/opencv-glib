#pragma once

#include <memory>

#include <opencv2/core/mat.hpp>

#include <opencv-glib/matrix.h>

GCVMatrix *gcv_matrix_new_raw(std::shared_ptr<cv::Mat> *cv_matrix);
std::shared_ptr<cv::Mat> gcv_matrix_get_raw(GCVMatrix *matrix);
