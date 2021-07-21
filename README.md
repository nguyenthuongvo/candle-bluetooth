# ESP32 BLE (Canble Bluetooth Server)

Candle Bluetooth Codelab
========================

See https://codelabs.developers.google.com/codelabs/candle-bluetooth/ for codelab instructions.  
Final working version of the codelab can be found at https://googlecodelabs.github.io/candle-bluetooth/.  


# Firmware
Device Name: DEVIT V1 ESP32-WROOM-32  
![alt text](https://m.media-amazon.com/images/I/61q+EATbqCL._AC_SY355_.jpg)  

# Software
[1] Visual Code  
[2] PlatformIO Extension  

# How to run the Demo
[1] Webbluetooth works well on Chrome Browser (Windows, Android), Bluefly (iOS)  

# How to upload firmware
[PlatformIO] Check out this topic https://randomnerdtutorials.com/vs-code-platformio-ide-esp32-esp8266-arduino/  

[Arduino IDE] Copy the whole codes inside **ESP32 PlatformIO > src** folder to Arduino IDE then REMOVE 
```cpp
#include <Arduino.h>
```  
Uploading the code.  

# Reference
[1] https://github.com/jasoncoon/esp32-fastled-ble  
[2] https://github.com/googlecodelabs/candle-bluetooth  
[3] https://github.com/kpatel122/ESP32-Web-Bluetooth-Terminal  
