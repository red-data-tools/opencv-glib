#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * GCVError:
 * @GCV_ERROR_IMAGE_READ: Image read error.
 * @GCV_ERROR_UNKNOWN: Unknown error.
 *
 * Since: 1.0.0
 */
typedef enum {
  GCV_ERROR_IMAGE_READ,
  GCV_ERROR_UNKNOWN,
} GCVError;

#define GCV_ERROR (gcv_error_quark())

GQuark gcv_error_quark(void);

G_END_DECLS
