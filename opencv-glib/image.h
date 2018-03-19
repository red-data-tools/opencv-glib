#pragma once

#include <opencv-glib/matrix.h>

G_BEGIN_DECLS

#define GCV_TYPE_IMAGE (gcv_image_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVImage,
                         gcv_image,
                         GCV,
                         IMAGE,
                         GCVMatrix)
struct _GCVImageClass
{
  GCVMatrixClass parent_class;
};

GCVImage *gcv_image_read(const gchar *filename,
                         GError **error);
gboolean gcv_image_write(GCVImage *image,
                         const gchar *filename,
                         GError **error);

G_END_DECLS
