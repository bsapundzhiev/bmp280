# *bmp280 device detection Linux module*

bmp085, bmp180, bmp280 and bme280 i2c device detection module used alongside
with latest Linux kernel driver in `drivers/iio/pressure/bmp280`

It may be usefull when bmp sensor is connected to diffrent i2c busses
for example via i2c-tiny-usb driver or just to avoid manual detection and 
initialization.

### *Build*
```
$ make 
$ sudo make install
$ sudo depmod -a
```

### *Configuration*
```
$ sudo modprobe bmp280-probe
```
To detect sensor on startup add line "bmp280-probe" in /etc/modules 
or use the command:
```
$ echo "bmp280-probe" | sudo tee -a /etc/modules
```
### *Check device*
```
$ dmesg | grep bmp280_probe
[    4.437764] bmp280_probe: Probing i2c adapters: [0-24]
[    4.440370] bmp280_probe: Found device: bme280 @ i2c-1 addr: 0x76

ls -l /sys/bus/iio/devices/

$ cat /sys/bus/i2c/devices/1-0076/iio:device0/name
$ cat /sys/bus/i2c/devices/1-0076/iio:device0/in_temp_input
$ cat /sys/bus/i2c/devices/1-0076/iio:device0/in_pressure_input
$ cat /sys/bus/i2c/devices/1-0076/iio:device0/in_humidityrelative_input 
```
