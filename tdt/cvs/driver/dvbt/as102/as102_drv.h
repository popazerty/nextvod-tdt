/*
 * Abilis Systems Single DVB-T Receiver
 * Copyright (C) 2008 Pierrick Hascoet <pierrick.hascoet@abilis.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#if defined(CONFIG_AS102_USB)
#include <linux/usb.h>
extern struct usb_driver as102_usb_driver;
#endif

#if defined(CONFIG_AS102_SPI)
#include <linux/platform_device.h>
#include <linux/spi/spi.h>
#include <linux/cdev.h>

extern struct spi_driver as102_spi_driver;
#endif

#include "dvb_demux.h"
#include "dvb_frontend.h"
#include "dmxdev.h"

#define DRIVER_FULL_NAME "Abilis Systems as10x usb driver"
#define DRIVER_NAME "as10x_usb"

extern int debug;
/*
#define dprintk(debug, args...) \
	do { if (debug) {	\
		printk(KERN_DEBUG "%s: ",__FUNCTION__);	\
		printk(args);	\
	} } while (0)
*/

#define DEBUG

#ifdef DEBUG
#define dprintk(debug,args...) printk(args)
#else
#define dprintk(debug,args...)
#endif

//#define TRACE

#ifdef TRACE
#define ENTER()                 printk(">> enter %s\n", __FUNCTION__)
#define LEAVE()                 printk("<< leave %s\n", __FUNCTION__)
#else
#define ENTER()
#define LEAVE()
#endif

#define AS102_DEVICE_MAJOR	192

#define AS102_USB_BUF_SIZE	512
#define MAX_STREAM_URB		32
//#define MAX_STREAM_URB		1

#include "as10x_cmd.h"

#if defined(CONFIG_AS102_USB)
#include "as102_usb_drv.h"
#endif

#if defined(CONFIG_AS102_SPI)
#include "as10x_spi_drv.h"
#endif


struct as102_bus_adapter_t {
#if defined(CONFIG_AS102_USB)
	struct usb_device *usb_dev;
#elif defined(CONFIG_AS102_SPI)
	struct spi_device *spi_dev;
	struct cdev cdev; /* spidev raw device */

	struct timer_list timer;
	struct completion xfer_done;
#endif
	/* bus token lock */
	struct mutex lock;
	/* low level interface for bus adapter */
	union as10x_bus_token_t {
#if defined(CONFIG_AS102_USB)
		/* usb token */
		struct as10x_usb_token_cmd_t usb;
#endif
#if defined(CONFIG_AS102_SPI)
		/* spi token */
		struct as10x_spi_token_cmd_t spi;
#endif
	} token;

	/* token cmd xfer id */
	uint16_t cmd_xid;

	/* as10x command and response for dvb interface*/
	struct as10x_cmd_t *cmd, *rsp;

	/* bus adapter private ops callback */
	struct as102_priv_ops_t *ops;
};

struct as102_dev_t {
	const char *name;
	struct as102_bus_adapter_t bus_adap;
	struct list_head device_entry;
	struct kref kref;
	unsigned long minor;

	struct dvb_adapter dvb_adap;
	struct dvb_frontend dvb_fe;
	struct dvb_demux dvb_dmx;
	struct dmxdev dvb_dmxdev;

	/* demodulator stats */
	struct as10x_demod_stats demod_stats;
	/* signal strength */
	uint16_t signal_strength;
	/* bit error rate */
	uint32_t ber;

	/* timer handle to trig ts stream download */
	struct timer_list timer_handle;

	struct mutex sem;
	dma_addr_t dma_addr;
	void *stream;
	int streaming;
	struct urb *stream_urb[MAX_STREAM_URB];
};

int as102_dvb_register(struct as102_dev_t *dev);
void as102_dvb_unregister(struct as102_dev_t *dev);

int as102_dvb_register_fe(struct as102_dev_t *dev, struct dvb_frontend *fe);
int as102_dvb_unregister_fe(struct dvb_frontend *dev);

/* EOF - vim: set textwidth=80 ts=8 sw=8 sts=8 noet: */
