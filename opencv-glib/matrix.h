#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GCV_TYPE_MATRIX (gcv_matrix_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVMatrix,
                         gcv_matrix,
                         GCV,
                         MATRIX,
                         GObject)
struct _GCVMatrixClass
{
  GObjectClass parent_class;
};

GCVMatrix *gcv_matrix_new(void);
gboolean gcv_matrix_is_empty(GCVMatrix *matrix);
GBytes *gcv_matrix_get_bytes(GCVMatrix *matrix);
gsize gcv_matrix_get_element_size(GCVMatrix *matrix);
gsize gcv_matrix_get_channel_size(GCVMatrix *matrix);
gint gcv_matrix_get_n_channels(GCVMatrix *matrix);

G_END_DECLS
