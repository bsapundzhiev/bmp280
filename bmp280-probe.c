// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * bmp280-probe.c bmp i2c device detection 
 * 
 * Copyright (c) 2022  Borislav Sapundzhiev <bsapunjiev@gmail.com>
 */
 
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>

#include "bmp280.h"

/* module for explicit detect i2c device by bus id */
#define	I2C_ADAPTERS_MAX			  (24)

/* device probing addreses */
/**\name I2C addresses */
#define BME280_I2C_ADDR_PRIM                      (0x76)
#define BME280_I2C_ADDR_SEC                       (0x77)

static const unsigned short probe_i2c_addrs[] = 
	I2C_ADDRS(BME280_I2C_ADDR_PRIM, BME280_I2C_ADDR_SEC);

static struct i2c_board_info bmp280_i2c_info[] = {
	{ 
	  I2C_BOARD_INFO("bmp280", BMP280_CHIP_ID), 
	  I2C_BOARD_INFO("bmp180", BMP180_CHIP_ID),
	  I2C_BOARD_INFO("bmp085", BMP180_CHIP_ID),
	  I2C_BOARD_INFO("bme280", BME280_CHIP_ID), 
	},
};

static int bmp280_i2c_device_probe(void)
{
	unsigned short adapters_nr = 0;
	pr_info("Probing i2c adapters: [%d-%d]\n", 
				adapters_nr, I2C_ADAPTERS_MAX);

	for (adapters_nr = adapters_nr; adapters_nr <= I2C_ADAPTERS_MAX; adapters_nr++) {
		struct i2c_adapter *i2c_adapter = i2c_get_adapter(adapters_nr);
		if (i2c_adapter) {
			struct i2c_client *i2c_device = 
				i2c_new_scanned_device(i2c_adapter, 
					bmp280_i2c_info, probe_i2c_addrs, NULL);
			if (!IS_ERR(i2c_device)) {
				pr_info("Found device: %s @ i2c-%d addr: 0x%x\n", 
					i2c_device->name, adapters_nr, i2c_device->addr);
			}
		}

	}
	return 0;
}

static int __init bmp280_probe_init(void)
{
	return bmp280_i2c_device_probe();
}

static void __exit bmp280_probe_exit(void)
{
	pr_info("%s\n", __FUNCTION__);
}

module_init(bmp280_probe_init);
module_exit(bmp280_probe_exit);

MODULE_AUTHOR("Borislav Sapundzhiev <BSapundzhiev@gmail.com>");
MODULE_DESCRIPTION("bmpXXX, bme280 device detection");
MODULE_LICENSE("GPL");
