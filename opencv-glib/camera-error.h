#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * GCVCameraError:
 * @GCV_CAMERA_ERROR_OPEN: Open error.
 * @GCV_CAMERA_ERROR_UNKNOWN: Unknown error.
 *
 * Camera related errors.
 *
 * Since: 1.0.0
 */
typedef enum {
  GCV_CAMERA_ERROR_OPEN,
  GCV_CAMERA_ERROR_UNKNOWN,
} GCVCameraError;

#define GCV_CAMERA_ERROR (gcv_camera_error_quark())

GQuark gcv_camera_error_quark(void);

G_END_DECLS
