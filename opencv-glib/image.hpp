#pragma once

#include <opencv2/imgcodecs.hpp>

#include <opencv-glib/image.h>
#include <opencv-glib/matrix.hpp>

GCVImage *gcv_image_new_raw(std::shared_ptr<cv::Mat> *cv_matrix);
