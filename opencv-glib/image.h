#pragma once

#include <opencv-glib/color.h>
#include <opencv-glib/matrix.h>
#include <opencv-glib/point.h>
#include <opencv-glib/rectangle.h>

G_BEGIN_DECLS

/**
 * GCVLineType:
 * @GCV_LINE_TYPE_FILLED: See `cv::LineTypes::FILLED`.
 * @GCV_LINE_TYPE_LINE_4: See `cv::LineTypes::LINE_4`.
 * @GCV_LINE_TYPE_LINE_8: See `cv::LineTypes::LINE_8`.
 * @GCV_LINE_TYPE_LINE_AA: See `cv::LineTypes::LINE_AA`.
 *
 * Line type for drawing functions corresponding to `cv::LineTypes`.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::LineTypes` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::LineTypes`](https://docs.opencv.org/3.4.1/d0/de1/group__core.html#gaf076ef45de481ac96e0ab3dc2c29a777).
 *
 * Since 1.0.1
 */
typedef enum {
  GCV_LINE_TYPE_FILLED = -1,
  GCV_LINE_TYPE_LINE_4 = 4,
  GCV_LINE_TYPE_LINE_8 = 8,
  GCV_LINE_TYPE_LINE_AA = 16
} GCVLineType;

#define GCV_TYPE_DRAWING_OPTIONS (gcv_drawing_options_get_type())
G_DECLARE_DERIVABLE_TYPE(GCVDrawingOptions,
                         gcv_drawing_options,
                         GCV,
                         DRAWING_OPTIONS,
                         GObject)

struct _GCVDrawingOptionsClass
{
  GObjectClass parent_class;
};

GCVDrawingOptions *gcv_drawing_options_new(void);

/**
 * GCVImageReadFlags:
 * @GCV_IMAGE_READ_FLAG_UNCHANGED: See `cv::IMREAD_UNCHANGED`.
 * @GCV_IMAGE_READ_FLAG_GRAYSCALE: See `cv::IMREAD_GREAYSCALE`.
 * @GCV_IMAGE_READ_FLAG_COLOR: See `cv::IMREAD_COLOR`.
 * @GCV_IMAGE_READ_FLAG_ANY_DEPTH: See `cv::IMREAD_ANYDEPTH`.
 * @GCV_IMAGE_READ_FLAG_ANY_COLOR: See `cv::IMREAD_ANYCOLOR`.
 * @GCV_IMAGE_READ_FLAG_LOAD_GDAL: See `cv::IMREAD_LOAD_GDAL`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_2:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_2`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_2:
 *   See `cv::IMREAD_REDUCED_COLOR_2`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_4:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_4`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_4:
 *   See `cv::IMREAD_REDUCED_COLOR_4`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_8:
 *   See `cv::IMREAD_REDUCED_GRAYSCALE_8`.
 * @GCV_IMAGE_READ_FLAG_REDUCED_COLOR_8:
 *   See `cv::IMREAD_REDUCED_COLOR_8`.
 * @GCV_IMAGE_READ_FLAG_IGNORE_ORIENTATION:
 *   See `cv::IMREAD_IGNORE_ORIENTATION`.
 *
 * They are for gcv_image_read(). You can combine one or more them.
 *
 * They are corresponding to `cv::ImreadModes` values.
 *
 * See also [OpenCV documents](https://docs.opencv.org/).
 *
 * We don't have a link to the latest `cv::ImreadModes` document.
 * But we can link to a specific version:
 * [OpenCV 3.4.1's `cv::ImreadModes`](https://docs.opencv.org/3.4.1/d4/da8/group__imgcodecs.html#ga61d9b0126a3e57d9277ac48327799c80).
 *
 * Since: 1.0.0
 */
typedef enum { /*< flags >*/
  GCV_IMAGE_READ_FLAG_UNCHANGED = -1,
  GCV_IMAGE_READ_FLAG_GRAYSCALE = 0,
  GCV_IMAGE_READ_FLAG_COLOR = 1,
  GCV_IMAGE_READ_FLAG_ANY_DEPTH = 2,
  GCV_IMAGE_READ_FLAG_ANY_COLOR = 4,
  GCV_IMAGE_READ_FLAG_LOAD_GDAL = 8,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_2 = 16,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_2 = 17,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_4 = 32,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_4 = 33,
  GCV_IMAGE_READ_FLAG_REDUCED_GRAYSCALE_8 = 64,
  GCV_IMAGE_READ_FLAG_REDUCED_COLOR_8 = 65,
  GCV_IMAGE_READ_FLAG_IGNORE_ORIENTATION = 128,
} GCVImageReadFlags;

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
                         GCVImageReadFlags flags,
                         GError **error);
gboolean gcv_image_write(GCVImage *image,
                         const gchar *filename,
                         GError **error);

GCVImage *gcv_image_convert_color(GCVImage *image,
                                  GCVColorConversionCode code);
void gcv_image_draw_circle(GCVImage *image,
                           GCVPoint *center,
                           gint radius,
                           GCVColor *color,
                           GCVDrawingOptions *drawing_options);
void gcv_image_draw_rectangle(GCVImage *image,
                              GCVRectangle *rectangle,
                              GCVColor *color,
                              GCVDrawingOptions *drawing_options);

G_END_DECLS
