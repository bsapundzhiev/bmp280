#!/bin/bash
sudo make install
sudo depmod
sudo rmmod bmp280_probe
sudo modprobe bmp280-probe
