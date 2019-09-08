/* Generated by wayland-scanner 1.17.0 */

#ifndef GTK_PRIMARY_SELECTION_SERVER_PROTOCOL_H
#define GTK_PRIMARY_SELECTION_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_gtk_primary_selection The gtk_primary_selection protocol
 * Primary selection protocol
 *
 * @section page_desc_gtk_primary_selection Description
 *
 * This protocol provides the ability to have a primary selection device to
 * match that of the X server. This primary selection is a shortcut to the
 * common clipboard selection, where text just needs to be selected in order
 * to allow copying it elsewhere. The de facto way to perform this action
 * is the middle mouse button, although it is not limited to this one.
 *
 * Clients wishing to honor primary selection should create a primary
 * selection source and set it as the selection through
 * wp_primary_selection_device.set_selection whenever the text selection
 * changes. In order to minimize calls in pointer-driven text selection,
 * it should happen only once after the operation finished. Similarly,
 * a NULL source should be set when text is unselected.
 *
 * wp_primary_selection_offer objects are first announced through the
 * wp_primary_selection_device.data_offer event. Immediately after this event,
 * the primary data offer will emit wp_primary_selection_offer.offer events
 * to let know of the mime types being offered.
 *
 * When the primary selection changes, the client with the keyboard focus
 * will receive wp_primary_selection_device.selection events. Only the client
 * with the keyboard focus will receive such events with a non-NULL
 * wp_primary_selection_offer. Across keyboard focus changes, previously
 * focused clients will receive wp_primary_selection_device.events with a
 * NULL wp_primary_selection_offer.
 *
 * In order to request the primary selection data, the client must pass
 * a recent serial pertaining to the press event that is triggering the
 * operation, if the compositor deems the serial valid and recent, the
 * wp_primary_selection_source.send event will happen in the other end
 * to let the transfer begin. The client owning the primary selection
 * should write the requested data, and close the file descriptor
 * immediately.
 *
 * If the primary selection owner client disappeared during the transfer,
 * the client reading the data will receive a
 * wp_primary_selection_device.selection event with a NULL
 * wp_primary_selection_offer, the client should take this as a hint
 * to finish the reads related to the no longer existing offer.
 *
 * The primary selection owner should be checking for errors during
 * writes, merely cancelling the ongoing transfer if any happened.
 *
 * @section page_ifaces_gtk_primary_selection Interfaces
 * - @subpage page_iface_gtk_primary_selection_device_manager - X primary selection emulation
 * - @subpage page_iface_gtk_primary_selection_device - 
 * - @subpage page_iface_gtk_primary_selection_offer - offer to transfer primary selection contents
 * - @subpage page_iface_gtk_primary_selection_source - offer to replace the contents of the primary selection
 * @section page_copyright_gtk_primary_selection Copyright
 * <pre>
 *
 * Copyright © 2015, 2016 Red Hat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * </pre>
 */
struct gtk_primary_selection_device;
struct gtk_primary_selection_device_manager;
struct gtk_primary_selection_offer;
struct gtk_primary_selection_source;
struct wl_seat;

/**
 * @page page_iface_gtk_primary_selection_device_manager gtk_primary_selection_device_manager
 * @section page_iface_gtk_primary_selection_device_manager_desc Description
 *
 * The primary selection device manager is a singleton global object that
 * provides access to the primary selection. It allows to create
 * wp_primary_selection_source objects, as well as retrieving the per-seat
 * wp_primary_selection_device objects.
 * @section page_iface_gtk_primary_selection_device_manager_api API
 * See @ref iface_gtk_primary_selection_device_manager.
 */
/**
 * @defgroup iface_gtk_primary_selection_device_manager The gtk_primary_selection_device_manager interface
 *
 * The primary selection device manager is a singleton global object that
 * provides access to the primary selection. It allows to create
 * wp_primary_selection_source objects, as well as retrieving the per-seat
 * wp_primary_selection_device objects.
 */
extern const struct wl_interface gtk_primary_selection_device_manager_interface;
/**
 * @page page_iface_gtk_primary_selection_device gtk_primary_selection_device
 * @section page_iface_gtk_primary_selection_device_api API
 * See @ref iface_gtk_primary_selection_device.
 */
/**
 * @defgroup iface_gtk_primary_selection_device The gtk_primary_selection_device interface
 */
extern const struct wl_interface gtk_primary_selection_device_interface;
/**
 * @page page_iface_gtk_primary_selection_offer gtk_primary_selection_offer
 * @section page_iface_gtk_primary_selection_offer_desc Description
 *
 * A wp_primary_selection_offer represents an offer to transfer the contents
 * of the primary selection clipboard to the client. Similar to
 * wl_data_offer, the offer also describes the mime types that the source
 * will transferthat the
 * data can be converted to and provides the mechanisms for transferring the
 * data directly to the client.
 * @section page_iface_gtk_primary_selection_offer_api API
 * See @ref iface_gtk_primary_selection_offer.
 */
/**
 * @defgroup iface_gtk_primary_selection_offer The gtk_primary_selection_offer interface
 *
 * A wp_primary_selection_offer represents an offer to transfer the contents
 * of the primary selection clipboard to the client. Similar to
 * wl_data_offer, the offer also describes the mime types that the source
 * will transferthat the
 * data can be converted to and provides the mechanisms for transferring the
 * data directly to the client.
 */
extern const struct wl_interface gtk_primary_selection_offer_interface;
/**
 * @page page_iface_gtk_primary_selection_source gtk_primary_selection_source
 * @section page_iface_gtk_primary_selection_source_desc Description
 *
 * The source side of a wp_primary_selection_offer, it provides a way to
 * describe the offered data and respond to requests to transfer the
 * requested contents of the primary selection clipboard.
 * @section page_iface_gtk_primary_selection_source_api API
 * See @ref iface_gtk_primary_selection_source.
 */
/**
 * @defgroup iface_gtk_primary_selection_source The gtk_primary_selection_source interface
 *
 * The source side of a wp_primary_selection_offer, it provides a way to
 * describe the offered data and respond to requests to transfer the
 * requested contents of the primary selection clipboard.
 */
extern const struct wl_interface gtk_primary_selection_source_interface;

/**
 * @ingroup iface_gtk_primary_selection_device_manager
 * @struct gtk_primary_selection_device_manager_interface
 */
struct gtk_primary_selection_device_manager_interface {
	/**
	 * create a new primary selection source
	 *
	 * Create a new primary selection source.
	 */
	void (*create_source)(struct wl_client *client,
			      struct wl_resource *resource,
			      uint32_t id);
	/**
	 * create a new primary selection device
	 *
	 * Create a new data device for a given seat.
	 */
	void (*get_device)(struct wl_client *client,
			   struct wl_resource *resource,
			   uint32_t id,
			   struct wl_resource *seat);
	/**
	 * destroy the primary selection device manager
	 *
	 * Destroy the primary selection device manager.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
};


/**
 * @ingroup iface_gtk_primary_selection_device_manager
 */
#define GTK_PRIMARY_SELECTION_DEVICE_MANAGER_CREATE_SOURCE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_device_manager
 */
#define GTK_PRIMARY_SELECTION_DEVICE_MANAGER_GET_DEVICE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_device_manager
 */
#define GTK_PRIMARY_SELECTION_DEVICE_MANAGER_DESTROY_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_device
 * @struct gtk_primary_selection_device_interface
 */
struct gtk_primary_selection_device_interface {
	/**
	 * set the primary selection
	 *
	 * Replaces the current selection. The previous owner of the
	 * primary selection will receive a
	 * wp_primary_selection_source.cancelled event.
	 *
	 * To unset the selection, set the source to NULL.
	 * @param serial serial of the event that triggered this request
	 */
	void (*set_selection)(struct wl_client *client,
			      struct wl_resource *resource,
			      struct wl_resource *source,
			      uint32_t serial);
	/**
	 * destroy the primary selection device
	 *
	 * Destroy the primary selection device.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
};

#define GTK_PRIMARY_SELECTION_DEVICE_DATA_OFFER 0
#define GTK_PRIMARY_SELECTION_DEVICE_SELECTION 1

/**
 * @ingroup iface_gtk_primary_selection_device
 */
#define GTK_PRIMARY_SELECTION_DEVICE_DATA_OFFER_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_device
 */
#define GTK_PRIMARY_SELECTION_DEVICE_SELECTION_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_device
 */
#define GTK_PRIMARY_SELECTION_DEVICE_SET_SELECTION_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_device
 */
#define GTK_PRIMARY_SELECTION_DEVICE_DESTROY_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_device
 * Sends an data_offer event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
gtk_primary_selection_device_send_data_offer(struct wl_resource *resource_, struct wl_resource *offer)
{
	wl_resource_post_event(resource_, GTK_PRIMARY_SELECTION_DEVICE_DATA_OFFER, offer);
}

/**
 * @ingroup iface_gtk_primary_selection_device
 * Sends an selection event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
gtk_primary_selection_device_send_selection(struct wl_resource *resource_, struct wl_resource *id)
{
	wl_resource_post_event(resource_, GTK_PRIMARY_SELECTION_DEVICE_SELECTION, id);
}

/**
 * @ingroup iface_gtk_primary_selection_offer
 * @struct gtk_primary_selection_offer_interface
 */
struct gtk_primary_selection_offer_interface {
	/**
	 * request that the data is transferred
	 *
	 * To transfer the contents of the primary selection clipboard,
	 * the client issues this request and indicates the mime type that
	 * it wants to receive. The transfer happens through the passed
	 * file descriptor (typically created with the pipe system call).
	 * The source client writes the data in the mime type
	 * representation requested and then closes the file descriptor.
	 *
	 * The receiving client reads from the read end of the pipe until
	 * EOF and closes its end, at which point the transfer is complete.
	 */
	void (*receive)(struct wl_client *client,
			struct wl_resource *resource,
			const char *mime_type,
			int32_t fd);
	/**
	 * destroy the primary selection offer
	 *
	 * Destroy the primary selection offer.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
};

#define GTK_PRIMARY_SELECTION_OFFER_OFFER 0

/**
 * @ingroup iface_gtk_primary_selection_offer
 */
#define GTK_PRIMARY_SELECTION_OFFER_OFFER_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_offer
 */
#define GTK_PRIMARY_SELECTION_OFFER_RECEIVE_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_offer
 */
#define GTK_PRIMARY_SELECTION_OFFER_DESTROY_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_offer
 * Sends an offer event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
gtk_primary_selection_offer_send_offer(struct wl_resource *resource_, const char *mime_type)
{
	wl_resource_post_event(resource_, GTK_PRIMARY_SELECTION_OFFER_OFFER, mime_type);
}

/**
 * @ingroup iface_gtk_primary_selection_source
 * @struct gtk_primary_selection_source_interface
 */
struct gtk_primary_selection_source_interface {
	/**
	 * add an offered mime type
	 *
	 * This request adds a mime type to the set of mime types
	 * advertised to targets. Can be called several times to offer
	 * multiple types.
	 */
	void (*offer)(struct wl_client *client,
		      struct wl_resource *resource,
		      const char *mime_type);
	/**
	 * destroy the primary selection source
	 *
	 * Destroy the primary selection source.
	 */
	void (*destroy)(struct wl_client *client,
			struct wl_resource *resource);
};

#define GTK_PRIMARY_SELECTION_SOURCE_SEND 0
#define GTK_PRIMARY_SELECTION_SOURCE_CANCELLED 1

/**
 * @ingroup iface_gtk_primary_selection_source
 */
#define GTK_PRIMARY_SELECTION_SOURCE_SEND_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_source
 */
#define GTK_PRIMARY_SELECTION_SOURCE_CANCELLED_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_source
 */
#define GTK_PRIMARY_SELECTION_SOURCE_OFFER_SINCE_VERSION 1
/**
 * @ingroup iface_gtk_primary_selection_source
 */
#define GTK_PRIMARY_SELECTION_SOURCE_DESTROY_SINCE_VERSION 1

/**
 * @ingroup iface_gtk_primary_selection_source
 * Sends an send event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
gtk_primary_selection_source_send_send(struct wl_resource *resource_, const char *mime_type, int32_t fd)
{
	wl_resource_post_event(resource_, GTK_PRIMARY_SELECTION_SOURCE_SEND, mime_type, fd);
}

/**
 * @ingroup iface_gtk_primary_selection_source
 * Sends an cancelled event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
gtk_primary_selection_source_send_cancelled(struct wl_resource *resource_)
{
	wl_resource_post_event(resource_, GTK_PRIMARY_SELECTION_SOURCE_CANCELLED);
}

#ifdef  __cplusplus
}
#endif

#endif
