# RPIPicoFreeRTOSSMPExp

This is a [FreeRTOS Kernel SMP](https://www.freertos.org/symmetric-multiprocessing-introduction.html) example for the [Raspberry PI Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/). This example project is used on my [video tutorial on YouTube](https://youtu.be/nD8XeWjn-2w).

## Dependencies
+ (FreeRTOS Kernel)[https://github.com/FreeRTOS/FreeRTOS-Kernel] Version *V202110.00-SMP*
+ Pico SDK

## Schematic
A schematic for the project and components can be found in the Schematic folder.
+ 1x Green LED
+ 1x Blue LED
+ 4x Red LED
+ 6x 75Ohm Resistors
+ RPI Pico
+ Breadboard
+ Micro USB Cable


## Cloning Repository
```
$ git clone --recurse-submodules https://github.com/jondurrant/RPIPicoFreeRTOSSMPExp
```

## Build process
```
$ cd RPIPicoFreeRTOSSMPExp
$ mkdir build
$ cd build
$ cmake ..
$ make
```
Copy binary to the pico


## Further FreeRTOS Kernel Examples
Udemy course: [FreeRTOS on Raspberry PI Pico](https://www.udemy.com/course/freertos-on-rpi-pico/?referralCode=C5A9A19C93919A9DA294)