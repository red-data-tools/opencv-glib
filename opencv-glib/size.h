#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GCV_TYPE_SIZE (gcv_size_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVSize,
                         gcv_size,
                         GCV,
                         SIZE,
                         GObject)
struct _GCVSizeClass
{
  GObjectClass parent_class;
};

GCVSize *gcv_size_new(gint width, gint height);
GCVSize *gcv_size_new_empty(void);

gint gcv_size_get_width(GCVSize *size);
void gcv_size_set_width(GCVSize *size, gint width);
gint gcv_size_get_height(GCVSize *size);
void gcv_size_set_height(GCVSize *size, gint height);

G_END_DECLS
