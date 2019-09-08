/* Generated by wayland-scanner 1.17.0 */

#ifndef IDLE_SERVER_PROTOCOL_H
#define IDLE_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_idle The idle protocol
 * @section page_ifaces_idle Interfaces
 * - @subpage page_iface_org_kde_kwin_idle - User idle time manager
 * - @subpage page_iface_org_kde_kwin_idle_timeout - 
 * @section page_copyright_idle Copyright
 * <pre>
 *
 * Copyright (C) 2015 Martin Gräßlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * </pre>
 */
struct org_kde_kwin_idle;
struct org_kde_kwin_idle_timeout;
struct wl_seat;

/**
 * @page page_iface_org_kde_kwin_idle org_kde_kwin_idle
 * @section page_iface_org_kde_kwin_idle_desc Description
 *
 * This interface allows to monitor user idle time on a given seat. The interface
 * allows to register timers which trigger after no user activity was registered
 * on the seat for a given interval. It notifies when user activity resumes.
 *
 * This is useful for applications wanting to perform actions when the user is not
 * interacting with the system, e.g. chat applications setting the user as away, power
 * management features to dim screen, etc..
 * @section page_iface_org_kde_kwin_idle_api API
 * See @ref iface_org_kde_kwin_idle.
 */
/**
 * @defgroup iface_org_kde_kwin_idle The org_kde_kwin_idle interface
 *
 * This interface allows to monitor user idle time on a given seat. The interface
 * allows to register timers which trigger after no user activity was registered
 * on the seat for a given interval. It notifies when user activity resumes.
 *
 * This is useful for applications wanting to perform actions when the user is not
 * interacting with the system, e.g. chat applications setting the user as away, power
 * management features to dim screen, etc..
 */
extern const struct wl_interface org_kde_kwin_idle_interface;
/**
 * @page page_iface_org_kde_kwin_idle_timeout org_kde_kwin_idle_timeout
 * @section page_iface_org_kde_kwin_idle_timeout_api API
 * See @ref iface_org_kde_kwin_idle_timeout.
 */
/**
 * @defgroup iface_org_kde_kwin_idle_timeout The org_kde_kwin_idle_timeout interface
 */
extern const struct wl_interface org_kde_kwin_idle_timeout_interface;

/**
 * @ingroup iface_org_kde_kwin_idle
 * @struct org_kde_kwin_idle_interface
 */
struct org_kde_kwin_idle_interface {
	/**
	 * @param timeout The idle timeout in msec
	 */
	void (*get_idle_timeout)(struct wl_client *client,
				 struct wl_resource *resource,
				 uint32_t id,
				 struct wl_resource *seat,
				 uint32_t timeout);
};


/**
 * @ingroup iface_org_kde_kwin_idle
 */
#define ORG_KDE_KWIN_IDLE_GET_IDLE_TIMEOUT_SINCE_VERSION 1

/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 * @struct org_kde_kwin_idle_timeout_interface
 */
struct org_kde_kwin_idle_timeout_interface {
	/**
	 * release the timeout object
	 *
	 * 
	 */
	void (*release)(struct wl_client *client,
			struct wl_resource *resource);
	/**
	 * Simulates user activity for this timeout, behaves just like real user activity on the seat
	 *
	 * 
	 */
	void (*simulate_user_activity)(struct wl_client *client,
				       struct wl_resource *resource);
};

#define ORG_KDE_KWIN_IDLE_TIMEOUT_IDLE 0
#define ORG_KDE_KWIN_IDLE_TIMEOUT_RESUMED 1

/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 */
#define ORG_KDE_KWIN_IDLE_TIMEOUT_IDLE_SINCE_VERSION 1
/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 */
#define ORG_KDE_KWIN_IDLE_TIMEOUT_RESUMED_SINCE_VERSION 1

/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 */
#define ORG_KDE_KWIN_IDLE_TIMEOUT_RELEASE_SINCE_VERSION 1
/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 */
#define ORG_KDE_KWIN_IDLE_TIMEOUT_SIMULATE_USER_ACTIVITY_SINCE_VERSION 1

/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 * Sends an idle event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
org_kde_kwin_idle_timeout_send_idle(struct wl_resource *resource_)
{
	wl_resource_post_event(resource_, ORG_KDE_KWIN_IDLE_TIMEOUT_IDLE);
}

/**
 * @ingroup iface_org_kde_kwin_idle_timeout
 * Sends an resumed event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
org_kde_kwin_idle_timeout_send_resumed(struct wl_resource *resource_)
{
	wl_resource_post_event(resource_, ORG_KDE_KWIN_IDLE_TIMEOUT_RESUMED);
}

#ifdef  __cplusplus
}
#endif

#endif
