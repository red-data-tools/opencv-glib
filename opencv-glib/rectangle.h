#pragma once

#include <opencv-glib/point.h>

G_BEGIN_DECLS

#define GCV_TYPE_RECTANGLE (gcv_rectangle_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVRectangle,
                         gcv_rectangle,
                         GCV,
                         RECTANGLE,
                         GObject)
struct _GCVRectangleClass
{
  GObjectClass parent_class;
};

GCVRectangle *gcv_rectangle_new(gint x, gint y, gint width, gint height);
GCVRectangle *gcv_rectangle_new_empty(void);

gint gcv_rectangle_get_x(GCVRectangle *rectangle);
void gcv_rectangle_set_x(GCVRectangle *rectangle, gint x);
gint gcv_rectangle_get_y(GCVRectangle *rectangle);
void gcv_rectangle_set_y(GCVRectangle *rectangle, gint y);
gint gcv_rectangle_get_width(GCVRectangle *rectangle);
void gcv_rectangle_set_width(GCVRectangle *rectangle, gint width);
gint gcv_rectangle_get_height(GCVRectangle *rectangle);
void gcv_rectangle_set_height(GCVRectangle *rectangle, gint height);
gboolean gcv_rectangle_clip_line(GCVRectangle* rectangle, GCVPoint **point1, GCVPoint **point2);

G_END_DECLS
