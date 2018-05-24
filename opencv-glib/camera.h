#pragma once

#include <opencv-glib/video-capture.h>

G_BEGIN_DECLS

#define GCV_TYPE_CAMERA (gcv_camera_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVCamera,
                         gcv_camera,
                         GCV,
                         CAMERA,
                         GCVVideoCapture)
struct _GCVCameraClass
{
  GCVVideoCaptureClass parent_class;
};

GCVCamera *gcv_camera_new(GError **error);

G_END_DECLS
