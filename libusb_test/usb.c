#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <libusb-1.0/libusb.h>

#include "usb.h"


int do_send_ctrl_setup_trace( libusb_device_handle *dev, ctrl_setup *ctrl, unsigned char *data, const char *caller_name )
{
    fprintf( stdout, " tx (URB_CONTROL)  >   0x%02x  %02u (0x%02x)  0x%04x  0x%04x  0x%04x   |   %s()\n",
         ctrl->bmRequestType,
         ctrl->bRequest,
         ctrl->bRequest,
         ctrl->wValue,
         ctrl->wIndex,
         ctrl->wLength,
         caller_name
      );

    return do_send_ctrl_setup( dev, ctrl, data );
}


int do_send_ctrl_setup( libusb_device_handle *dev, ctrl_setup *ctrl, unsigned char *data )
{
	int rc = libusb_control_transfer(
			dev,
			ctrl->bmRequestType,
			ctrl->bRequest,
			ctrl->wValue,
			ctrl->wIndex,
			data,
			ctrl->wLength,
			0
		);

	if ( rc < 0 )
    {
		fprintf( stderr, "%s:%d in %s() : %s\n",
			 __FILE__,
			 __LINE__,
			 __func__,
			 libusb_error_name( rc ) );

		exit( rc );
	}

	return rc;
}


// #define send_ctrl_setup( de, ct, da ) send_ctrl_setup_trace( de, ct, da, __func__ )


int send_ctrl_setup_alt( libusb_device_handle *dev, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint16_t wLength, unsigned char *data )
{
	ctrl_setup ctrl;

	ctrl.bmRequestType = bmRequestType;
	ctrl.bRequest = bRequest;
	ctrl.wValue = wValue;
	ctrl.wIndex = wIndex;
	ctrl.wLength = wLength;

	return send_ctrl_setup( dev, &ctrl, data );
}
