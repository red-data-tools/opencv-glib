#pragma once

#include <opencv-glib/image.h>

G_BEGIN_DECLS

#define GCV_TYPE_VIDEO_CAPTURE (gcv_video_capture_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVVideoCapture,
                         gcv_video_capture,
                         GCV,
                         VIDEO_CAPTURE,
                         GObject)
struct _GCVVideoCaptureClass
{
  GObjectClass parent_class;
};

GCVImage *gcv_video_capture_read(GCVVideoCapture *capture);

G_END_DECLS
