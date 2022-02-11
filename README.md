*bmp280 device detection Linux module*

bmp085, bmp180, bmp280 and bme280 i2c device detection module used alongside
with latest Linux kernel driver in `drivers/iio/pressure/bmp280`

It may be usefull when bmp sensor is connected to diffrent i2c busses
for example via i2c-tiny-usb driver or just to avoid manual detection and 
initialization.


*Build*

$ make 
$ sudo make install 
$ sudo depmod -a

*Configuration*

$ sudo modprobe bmp280-probe

To detect sensor on startup add line "bmp280-probe" in /etc/modules 
or use the command:

$ echo "bmp280-probe" | sudo tee -a /etc/modules
