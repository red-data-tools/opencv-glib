#include <opencv-glib/camera.hpp>
#include <opencv-glib/camera-error.h>

G_BEGIN_DECLS

/**
 * SECTION: camera
 * @title: Camera class
 * @include: opencv-glib/opencv-glib.h
 *
 * #GCVCamera is a special video capture class for camera.
 *
 * Since: 1.0.0
 */

G_DEFINE_TYPE(GCVCamera, gcv_camera, GCV_TYPE_VIDEO_CAPTURE)

static void
gcv_camera_init(GCVCamera *object)
{
}

static void
gcv_camera_class_init(GCVCameraClass *klass)
{
}

/**
 * gcv_camera_new:
 * @error: (nullable): Return locatipcn for a #GError or %NULL.
 *
 * Create a #GCVCamera for the default camera device.
 * content, not by the extension of the filename.
 *
 * Returns: (nullable):
 *   A newly created #GCVCamera or %NULL on error.
 *
 * Since: 1.0.0
 */
GCVCamera *
gcv_camera_new(GError **error)
{
  auto cv_camera = std::make_shared<cv::VideoCapture>(0);
  if (!cv_camera->isOpened()) {
    g_set_error(error,
                GCV_CAMERA_ERROR,
                GCV_CAMERA_ERROR_OPEN,
                "Failed to open the default camera");
    return NULL;
  }
  return gcv_camera_new_raw(&cv_camera);
}

G_END_DECLS

GCVCamera *
gcv_camera_new_raw(std::shared_ptr<cv::VideoCapture> *cv_camera)
{
  auto camera = g_object_new(GCV_TYPE_CAMERA,
                             "video-capture", cv_camera,
                             NULL);
  return GCV_CAMERA(camera);
}
