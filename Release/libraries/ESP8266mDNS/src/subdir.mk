################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/ESP8266mDNS.cpp \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS.cpp \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Control.cpp \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Helpers.cpp \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Structs.cpp \
/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Transfer.cpp 

LINK_OBJ += \
./libraries/ESP8266mDNS/src/ESP8266mDNS.cpp.o \
./libraries/ESP8266mDNS/src/LEAmDNS.cpp.o \
./libraries/ESP8266mDNS/src/LEAmDNS_Control.cpp.o \
./libraries/ESP8266mDNS/src/LEAmDNS_Helpers.cpp.o \
./libraries/ESP8266mDNS/src/LEAmDNS_Structs.cpp.o \
./libraries/ESP8266mDNS/src/LEAmDNS_Transfer.cpp.o 

CPP_DEPS += \
./libraries/ESP8266mDNS/src/ESP8266mDNS.cpp.d \
./libraries/ESP8266mDNS/src/LEAmDNS.cpp.d \
./libraries/ESP8266mDNS/src/LEAmDNS_Control.cpp.d \
./libraries/ESP8266mDNS/src/LEAmDNS_Helpers.cpp.d \
./libraries/ESP8266mDNS/src/LEAmDNS_Structs.cpp.d \
./libraries/ESP8266mDNS/src/LEAmDNS_Transfer.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/ESP8266mDNS/src/ESP8266mDNS.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/ESP8266mDNS.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/ESP8266mDNS/src/LEAmDNS.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/ESP8266mDNS/src/LEAmDNS_Control.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Control.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/ESP8266mDNS/src/LEAmDNS_Helpers.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Helpers.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/ESP8266mDNS/src/LEAmDNS_Structs.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Structs.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/ESP8266mDNS/src/LEAmDNS_Transfer.cpp.o: /home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src/LEAmDNS_Transfer.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-g++" -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -D_GNU_SOURCE "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lwip2/include" "-I/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/include" "-I/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/core" -c -w -Werror=return-type -fstack-protector -Os -g -free -fipa-pta -mlongcalls -mtext-section-literals -fno-rtti -falign-functions=4 -std=gnu++17 -MMD -ffunction-sections -fdata-sections -fexceptions -DBEARSSL_SSL_BASIC -DMMU_IRAM_SIZE=0xC000 -DMMU_ICACHE_SIZE=0x4000  -DNONOSDK22x_190703=1 -DF_CPU=80000000L -DLWIP_OPEN_SRC -DTCP_MSS=536 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DDEBUG_ESP_PORT=Serial  -DARDUINO=10812 -DARDUINO_ESP8266_WEMOS_D1MINI -DARDUINO_ARCH_ESP8266 "-DARDUINO_BOARD=\"ESP8266_WEMOS_D1MINI\""  -DFLASHMODE_DIO  -DESP8266   -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/cores/esp8266" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/variants/d1_mini" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/WiFiManager/2.0.4-beta" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WebServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266WiFi/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/DNSServer/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/ESP8266mDNS/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/FastLED/3.4.0/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/libraries/Wire" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/4.2.1/src" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/Adafruit_NeoPixel/1.8.7" -I"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/libraries/NTPClient/3.2.0" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"   -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


