#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * GCVImageError:
 * @GCV_IMAGE_ERROR_READ: Read error.
 * @GCV_IMAGE_ERROR_WRITE: Write error.
 * @GCV_IMAGE_ERROR_UNKNOWN: Unknown error.
 *
 * Image related errors.
 *
 * Since: 1.0.0
 */
typedef enum {
  GCV_IMAGE_ERROR_READ,
  GCV_IMAGE_ERROR_WRITE,
  GCV_IMAGE_ERROR_UNKNOWN,
  GCV_IMAGE_ERROR_FILTER,
} GCVImageError;

#define GCV_IMAGE_ERROR (gcv_image_error_quark())

GQuark gcv_image_error_quark(void);

G_END_DECLS
