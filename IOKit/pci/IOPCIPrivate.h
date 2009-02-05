/*
 * Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 * 
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */


#ifndef _IOKIT_IOPCIPRIVATE_H
#define _IOKIT_IOPCIPRIVATE_H

#include <IOKit/pci/IOPCIDevice.h>

enum
{
    kIOPCIConfigShadowSize	= 64 + 8,
    kIOPCIConfigShadowMSI	= kIOPCIConfigShadowSize - 8,
    kIOPCIConfigShadowRegs 	= 16,
    kIOPCIVolatileRegsMask 	= ((1 << kIOPCIConfigShadowRegs) - 1)
				& ~(1 << (kIOPCIConfigVendorID >> 2))
				& ~(1 << (kIOPCIConfigRevisionID >> 2))
				& ~(1 << (kIOPCIConfigSubSystemVendorID >> 2))
};

struct IOPCIConfigShadow
{
    UInt32	  savedConfig[kIOPCIConfigShadowSize];
    UInt32        flags;
    queue_chain_t link;
    IOPCIDevice * device;
};

#define configShadow(device)	((IOPCIConfigShadow *) &device->savedConfig[0])


// flags in kIOPCIConfigShadowFlags
enum
{
    kIOPCIConfigShadowValid    = 0x00000001,
    kIOPCIConfigShadowBridge   = 0x00000002
};

// whatToDo for setDevicePowerState()
enum
{
    kSaveDeviceState    = 0,
    kRestoreDeviceState = 1,
    kSaveBridgeState    = 2,
    kRestoreBridgeState = 3
};


#define kIOPCIEjectableKey  "IOPCIEjectable"
#define kIOPCIHotPlugKey    "IOPCIHotPlug"
#define kIOPCIOnlineKey	    "IOPCIOnline"
#define kIOPCIConfiguredKey "IOPCIConfigured"
#define kIOPCIResourcedKey  "IOPCIResourced"

#ifndef kACPIDevicePathKey
#define kACPIDevicePathKey             "acpi-path"
#endif

#ifndef kPCIInterruptRoutingTableKey
#define kPCIInterruptRoutingTableKey   "acpi-pci-routing-table"
#endif

extern const IORegistryPlane * gIOPCIACPIPlane;

enum
{
    kIOPCIProbeOptionEject = 0x00100000 
};

#endif /* ! _IOKIT_IOPCIPRIVATE_H */

