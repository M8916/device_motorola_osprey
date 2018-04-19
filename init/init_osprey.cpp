/*
   Copyright (c) 2014, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <android-base/properties.h>
#include "vendor_init.h"
#include "property_service.h"
#include <sys/sysinfo.h>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;
using android::init::property_set;

void property_override(char const prop[], char const value[])
{
    prop_info *pi;
    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

int is2GB()
{
    struct sysinfo sys;
    sysinfo(&sys);
    return sys.totalram > 1024ull * 1024 * 1024;
}

void vendor_load_properties()
{

    std::string platform = GetProperty("ro.board.platform","");
    if (platform != ANDROID_TARGET)
        return;

    // Warning-less way of sprintf(var, "");
    std::string radio = GetProperty("ro.boot.radio","");
    std::string sku = GetProperty("ro.boot.hardware.sku","");
    std::string carrier = GetProperty("ro.boot.carrier","");

    if (is2GB()) {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");
        sprintf(gb, "_2gb");
    } else {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "96m");
        property_set("dalvik.vm.heapsize", "256m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
        gb[0] = 0;
    }

    property_set("ro.gsm.data_retry_config", "default_randomization=2000,max_retries=infinite,1000,1000,80000,125000,485000,905000");

    if (sku == "XT1540") {
        /* XT1540 */
        property_override("ro.product.model", "XT1540");
       if (is2GB){
	    property_override("ro.product.device", "osprey_u2");
        property_override("ro.build.description", "osprey_retus_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retus_2gb/osprey_u2:6.0.1/MPI24.107-55/33:user/release-keys");
                 }
       else{
          property_override("ro.product.device", "osprey_umts");
          property_override("ro.build.description", "osprey_retus-user 6.0.1 MPI24.107-55 33 release-keys");
		  property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retus/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
           }
        property_set("ro.mot.build.customerid", "retus");
        property_set("ro.com.google.clientidbase.am", "android-retus");
        property_set("ro.com.google.clientidbase.ms", "android-retus");
        property_set("ro.com.google.clientidbase.yt", "android-retus");
        property_set("ro.gsm.data_retry_config", "");
    } else if (sku == "XT1541") {
        /* XT1541 */
        property_override("ro.product.model", "XT1541");
       if (is2GB){
        property_override("ro.product.device", "osprey_u2");
        property_override("ro.build.description", "osprey_reteu_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_reteu_2gb/osprey_u2:6.0.1/MPI24.107-55/33:user/release-keys");
                 }
       else{
          property_override("ro.product.device", "osprey_umts");
          property_override("ro.build.description", "osprey_reteu-user 6.0.1 MPI24.107-55 33 release-keys");
		  property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_reteu/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
           }
        property_set("ro.mot.build.customerid", "reteu");
        property_set("ro.com.google.clientidbase.am", "android-reteu");
        property_set("ro.com.google.clientidbase.ms", "android-reteu");
        property_set("ro.com.google.clientidbase.yt", "android-reteu");
        property_set("ro.fsg-id", "emea");
        property_set("persist.radio.process_sups_ind", "0");
    } else if (sku == "XT1542") {
        /* XT1542 */
        property_override("ro.product.model", "XT1542");
       if (is2GB){
        property_override("ro.product.device", "osprey_u2");
        property_override("ro.build.description", "osprey_retla_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retla_2gb/osprey_u2:6.0.1/MPI24.107-55/33:user/release-keys");
                 }
       else{
          property_override("ro.product.device", "osprey_umts");
          property_override("ro.build.description", "osprey_retla-user 6.0.1 MPI24.107-55 33 release-keys");
		  property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retla/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
           }
        property_set("ro.mot.build.customerid", "retla");
        property_set("ro.com.google.clientidbase.am", "android-retla");
        property_set("ro.com.google.clientidbase.ms", "android-retla");
        property_set("ro.com.google.clientidbase.yt", "android-retla");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
    } else if (sku == "XT1543" || radio == "0x6") {
        /* XT1543 */
        property_override("ro.product.model", "XT1543");
       if (is2GB){
        property_override("ro.product.device", "osprey_u2");
        property_override("ro.build.description", "osprey_retla_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retla_ds_2gb/osprey_u2:6.0.1/MPI24.107-55/33:user/release-keys");
                 }
       else{
          property_override("ro.product.device", "osprey_umts");
          property_override("ro.build.description", "osprey_retla-user 6.0.1 MPI24.107-55 33 release-keys");
		  property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retla_ds/osprey_umts:6.0.1/MPI24.107-55/33:user/release-keys");
           }
        property_set("ro.mot.build.customerid", "retla");
        property_set("ro.com.google.clientidbase.am", "android-retla");
        property_set("ro.com.google.clientidbase.ms", "android-retla");
        property_set("ro.com.google.clientidbase.yt", "android-retla");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
        property_set("persist.radio.force_get_pref", "1");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("ro.telephony.ril.config", "simactivation");
    } else if (sku == "XT1544") {
        /* XT1544 */
        property_override("ro.product.model", "XT1544");
        property_override("ro.build.description", "osprey_retbr_tv_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retbr_tv_ds/osprey_udstv:6.0.1/MPI24.107-55/33:user/release-keys");
        property_override("ro.product.device", "osprey_udstv");
        property_set("ro.mot.build.customerid", "retbr");
        property_set("ro.com.google.clientidbase.am", "android-retbr");
        property_set("ro.com.google.clientidbase.ms", "android-retbr");
        property_set("ro.com.google.clientidbase.yt", "android-retbr");
        property_set("persist.radio.all_bc_msg", "all");
        property_set("persist.radio.process_sups_ind", "1");
        property_set("persist.radio.force_get_pref", "1");
        property_set("persist.radio.multisim.config", "dsds");
        property_set("ro.telephony.ril.config", "simactivation");
    } else if (sku == "XT1548") {
        /* XT1548 */
        if (carrier == "sprint") {
            property_set("ro.mot.build.customerid", "sprint");
			property_override("ro.build.description", "osprey_sprint-user 6.0.1 MPI24.107-55 33 release-keys");
			property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_sprint/osprey_cdma:6.0.1/MPI24.107-55/33:user/release-keys");
            property_set("ro.com.google.clientidbase.am", "android-sprint");
            property_set("ro.com.google.clientidbase.ms", "android-sprint");
            property_set("ro.com.google.clientidbase.yt", "android-sprint");
            property_set("ro.cdma.home.operator.alpha", "Sprint");
            property_set("ro.cdma.home.operator.numeric", "310120");
            property_set("ro.fsg-id", "sprint");
        } else /*if (carrier == "usc")*/ {
            property_set("ro.mot.build.customerid", "usc");
			property_override("ro.build.description", "osprey_usc-user 6.0.1 MPI24.107-55 33 release-keys");
			property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_usc/osprey_cdma:6.0.1/MPI24.107-55/33:user/release-keys");
            property_set("ro.com.google.clientidbase.am", "android-usc");
            property_set("ro.com.google.clientidbase.ms", "android-usc");
            property_set("ro.com.google.clientidbase.yt", "android-usc");
            property_set("ro.cdma.home.operator.alpha", "U.S. Cellular");
            property_set("ro.cdma.home.operator.numeric", "311580");
            property_set("ro.fsg-id", "usc");
        }
		property_override("ro.product.model", "XT1548");
        property_override("ro.product.device", "osprey_cdma");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,10000,10000,100000,10000,10000,10000,10000,140000,540000,960000");
        property_set("ro.product.locale.region", "US");
        property_set("gsm.sim.operator.iso-country", "US");
        property_set("gsm.operator.iso-country", "US");
        property_set("ril.subscription.types", "NV,RUIM");
        property_set("ro.telephony.default_cdma_sub", "0");
        property_set("ro.telephony.default_network", "8");
        property_set("ro.telephony.get_imsi_from_sim", "true");
        property_set("telephony.lteOnCdmaDevice", "1");
    } else if (sku == "XT1550") {
        /* XT1550 */
        property_override("ro.product.model", "XT1550");
        if (is2GB){
        property_override("ro.product.device", "osprey_ud2");
		property_override("ro.build.description", "osprey_retasia_ds-user 6.0.1 MPI24.107-55 33 release-keys");
		property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retasia_ds_2gb/osprey_ud2:6.0.1/MPI24.107-55/33:user/release-keys");
                 }
       else{
          property_override("ro.product.device", "osprey_uds");
		  property_override("ro.build.description", "osprey_retasia-user 6.0.1 MPI24.107-55 33 release-keys");
		  property_override_dual("ro.build.fingerprint", "ro.vendor.build.fingerprint", "motorola/osprey_retasia_ds/osprey_uds:6.0.1/MPI24.107-55/33:user/release-keys");
           }
        property_set("ro.mot.build.customerid", "retasia");
        property_set("ro.com.google.clientidbase.am", "android-retasia");
        property_set("ro.com.google.clientidbase.ms", "android-retasia");
        property_set("ro.com.google.clientidbase.yt", "android-retasia");
        property_set("ro.fsg-id", "apac");
        property_set("persist.radio.process_sups_ind", "0");
    }
        if (GetProperty("ro.telephony.default_network", "").empty()) {
        property_set("ro.telephony.default_network", "9");
    }
}
