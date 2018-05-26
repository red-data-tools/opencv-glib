#pragma once

#include <opencv-glib/image.h>

G_BEGIN_DECLS

#define GCV_TYPE_CASCADE_CLASSIFIER (gcv_cascade_classifier_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVCascadeClassifier,
                         gcv_cascade_classifier,
                         GCV,
                         CASCADE_CLASSIFIER,
                         GObject)
struct _GCVCascadeClassifierClass
{
  GObjectClass parent_class;
};

GCVCascadeClassifier *gcv_cascade_classifier_new(const gchar *path,
                                                 GError **error);

GList *
gcv_cascade_classifier_detect(GCVCascadeClassifier *classifier,
                              GCVImage *image);

G_END_DECLS
