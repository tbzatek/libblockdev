#include <glib.h>
#include <glib-object.h>
#include <blockdev/utils.h>

#ifndef BD_NVME_PRIVATE
#define BD_NVME_PRIVATE

/* TODO: move to a common libblockdev header */
#ifdef __clang__
#define ZERO_INIT {}
#else
#define ZERO_INIT {0}
#endif

/* "C" locale to get the locale-agnostic error messages */
#define _C_LOCALE (locale_t) 0

#ifdef HAVE_LIBNVME3
typedef struct libnvme_transport_handle *bd_nvme_dev_t;
#define BD_NVME_DEV_INVALID        NULL
#define BD_NVME_DEV_IS_VALID(dev)  ((dev) != NULL)
#define _libnvme_close(dev)        libnvme_close (dev)
#define nvme_status_to_string      libnvme_status_to_string
#define nvme_errno_to_string       libnvme_errno_to_string
#define nvme_uuid_to_string        libnvme_uuid_to_string
#define NVME_SANITIZE_SSTAT_STATUS_IN_PROGESS  NVME_SANITIZE_SSTAT_STATUS_IN_PROGRESS
#else
typedef int bd_nvme_dev_t;
#define BD_NVME_DEV_INVALID        -1
#define BD_NVME_DEV_IS_VALID(dev)  ((dev) >= 0)
#define _libnvme_close(dev)        close (dev)
#endif

/* nvme-error.c */
G_GNUC_INTERNAL
void _nvme_status_to_error (gint status, gboolean fabrics, GError **error);
G_GNUC_INTERNAL
void _nvme_fabrics_errno_to_gerror (int result, int _errno, GError **error);

/* nvme-info.c */
G_GNUC_INTERNAL
bd_nvme_dev_t _open_dev (const gchar *device, GError **error);
G_GNUC_INTERNAL
void *_nvme_alloc (size_t len, GError **error);

#endif  /* BD_NVME_PRIVATE */
