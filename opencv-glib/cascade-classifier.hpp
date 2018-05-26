#pragma once

#include <memory>

#include <opencv2/objdetect.hpp>

#include <opencv-glib/cascade-classifier.h>

GCVCascadeClassifier *
gcv_cascade_classifier_new_raw(std::shared_ptr<cv::CascadeClassifier> *cv_classifier);
std::shared_ptr<cv::CascadeClassifier>
gcv_cascade_classifier_get_raw(GCVCascadeClassifier *classifier);
