/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "zhiyuanLEDStub"

#include <hardware/hardware.h>

#include <fcntl.h>
#include <errno.h>

#include <cutils/log.h>
#include <cutils/atomic.h>

#include <led.h>

/*****************************************************************************/

int g_fd=0;

int led_device_close(struct hw_device_t* device)
{
	struct led_control_device_t* ctx = (struct led_control_device_t*)device;
	if (ctx) 
        {
		free(ctx);
	}

        close(g_fd);
	return 0;
}

int led_on(struct led_control_device_t *dev, int32_t led)
{
      if(led>=0 && led<=3)
       {

        LOGI("LED Stub: set %d on.", led);
        ioctl(g_fd, 0, led); //led on

       }
       else
       {
           LOGI("LED Stub: set led %d on error,no this led", led);
    
       }

	return 0;
}

int led_off(struct led_control_device_t *dev, int32_t led)
{
        
       if(led>=0 && led<=3)
       {

        LOGI("LED Stub: set %d off.", led);
        ioctl(g_fd, 1, led);//led off

       }
       else
       {
           LOGI("LED Stub: set led %d off error,no this led", led);
    
       }

	return 0;
}

static int led_device_open(const struct hw_module_t* module, const char* name,
        struct hw_device_t** device) 
{
	struct led_control_device_t *dev;

	dev = (struct led_control_device_t *)malloc(sizeof(*dev));
	memset(dev, 0, sizeof(*dev));

	dev->common.tag =  HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t*)module;
	dev->common.close = led_device_close;

	dev->set_on = led_on;
	dev->set_off = led_off;

	*device = &dev->common;
     
        g_fd = open("/dev/leds0", 0);
	if (g_fd < 0) 
        {
	   g_fd = open("/dev/leds", 0);
	}
 
       if(g_fd<0)
       {     
          LOGI("LED Stub: open /dev/leds  fail.");

       }else
       {
          LOGI("LED Stub: open /dev/leds success .");
       }

	return 0;
}

static struct hw_module_methods_t led_module_methods = {
    open: led_device_open
};

extern "C" const struct led_module_t HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 0,
        id: LED_HARDWARE_MODULE_ID,
        name: "Sample LED Stub",
        author: "The zhiyuan Open Source Project",
        methods: &led_module_methods,
    }
    /* supporting APIs go here */
};

