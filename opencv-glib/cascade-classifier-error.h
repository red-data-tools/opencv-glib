#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

/**
 * GCVCascadeClassifierError:
 * @GCV_CASCADE_CLASSIFIER_ERROR_LOAD: Load error.
 * @GCV_CASCADE_CLASSIFIER_ERROR_UNKNOWN: Unknown error.
 *
 * Cascade classifier related errors.
 *
 * Since: 1.0.0
 */
typedef enum {
  GCV_CASCADE_CLASSIFIER_ERROR_LOAD,
  GCV_CASCADE_CLASSIFIER_ERROR_UNKNOWN,
} GCVCascadeClassifierError;

#define GCV_CASCADE_CLASSIFIER_ERROR (gcv_cascade_classifier_error_quark())

GQuark gcv_cascade_classifier_error_quark(void);

G_END_DECLS
