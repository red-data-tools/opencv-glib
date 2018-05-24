#pragma once

#include <opencv-glib/camera.h>
#include <opencv-glib/video-capture.hpp>

GCVCamera *gcv_camera_new_raw(std::shared_ptr<cv::VideoCapture> *cv_camera);
