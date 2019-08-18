#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define GCV_TYPE_POINT (gcv_point_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVPoint,
                         gcv_point,
                         GCV,
                         POINT,
                         GObject)
struct _GCVPointClass
{
  GObjectClass parent_class;
};

GCVPoint *gcv_point_new(gint x, gint y);
GCVPoint *gcv_point_new_empty(void);

gint gcv_point_get_x(GCVPoint *point);
void gcv_point_set_x(GCVPoint *point, gint x);
gint gcv_point_get_y(GCVPoint *point);
void gcv_point_set_y(GCVPoint *point, gint y);

G_END_DECLS
