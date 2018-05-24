#pragma once

#include <memory>

#include <opencv2/videoio.hpp>

#include <opencv-glib/video-capture.h>

GCVVideoCapture *
gcv_video_capture_new_raw(std::shared_ptr<cv::VideoCapture> *cv_video_capture);
std::shared_ptr<cv::VideoCapture>
gcv_video_capture_get_raw(GCVVideoCapture *video_capture);
