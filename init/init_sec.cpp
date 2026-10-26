/*
 * Copyright (c) 2016, Android Open Source Project. All rights reserved.
 * Ported to Android 9 (LineageOS 16.0) init API.
 * Licensed under the same BSD-style terms as the original file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/logging.h>
#include <android-base/properties.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;

static void property_override(char const prop[], char const value[])
{
    prop_info *pi = (prop_info *) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

enum device_variant {
    G360H,
    J200H,
};

static device_variant find_device_variant()
{
    std::string bootloader = GetProperty("ro.bootloader", "");
    if (bootloader.find("G360H") != std::string::npos) {
        return G360H;
    }
    return J200H;
}

void vendor_load_properties()
{
    device_variant variant = find_device_variant();

    switch (variant) {
    case G360H:
        /* core33gdd */
        property_override("ro.product.model", "SM-G360H");
        property_override("ro.product.device", "core33g");
        break;
    case J200H:
    default:
        /* j23gdd */
        property_override("ro.product.model", "SM-J200H");
        property_override("ro.product.device", "j23g");
        break;
    }

    /* Single SIM variant detection */
    const char *simslot_count_path = "/proc/simslot_count";
    FILE *file = fopen(simslot_count_path, "r");

    if (file != NULL) {
        char simslot_count[2] = { 0, 0 };
        simslot_count[0] = fgetc(file);
        fclose(file);

        property_override("ro.multisim.simslotcount", simslot_count);

        if (!strcmp(simslot_count, "0") || !strcmp(simslot_count, "1")) {
            /* Only one SIM slot: treat as single-SIM device */
            property_set("persist.dsds.enabled", "false");
            property_set("persist.radio.multisim.config", "none");
        } else {
            /* Dual-SIM device */
            property_set("persist.dsds.enabled", "true");
            property_set("persist.radio.multisim.config", "dsds");
        }
    } else {
        LOG(ERROR) << "Could not open '" << simslot_count_path << "'";
    }

    std::string device = GetProperty("ro.product.device", "");
    LOG(ERROR) << "Found bootloader id " << GetProperty("ro.bootloader", "")
               << " setting build properties for " << device << " device";
}

