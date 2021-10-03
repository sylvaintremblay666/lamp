################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries/Wire/subdir.mk
-include libraries/WiFiManager/subdir.mk
-include libraries/NTPClient/subdir.mk
-include libraries/FastLED/src/platforms/esp/32/subdir.mk
-include libraries/FastLED/src/subdir.mk
-include libraries/ESP8266mDNS/src/subdir.mk
-include libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/src/subdir.mk
-include libraries/ESP8266WiFi/src/subdir.mk
-include libraries/ESP8266WebServer/src/detail/subdir.mk
-include libraries/DNSServer/src/subdir.mk
-include libraries/Adafruit_NeoPixel/subdir.mk
-include core/core/umm_malloc/subdir.mk
-include core/core/spiffs/subdir.mk
-include core/core/libb64/subdir.mk
-include core/core/subdir.mk
-include Release.old/libraries/Wire/subdir.mk
-include Release.old/libraries/WiFiManager/subdir.mk
-include Release.old/libraries/NTPClient/subdir.mk
-include Release.old/libraries/FastLED/src/platforms/esp/32/subdir.mk
-include Release.old/libraries/FastLED/src/subdir.mk
-include Release.old/libraries/ESP8266mDNS/src/subdir.mk
-include Release.old/libraries/ESP8266_and_ESP32_OLED_driver_for_SSD1306_displays/src/subdir.mk
-include Release.old/libraries/ESP8266WiFi/src/subdir.mk
-include Release.old/libraries/ESP8266WebServer/src/detail/subdir.mk
-include Release.old/libraries/DNSServer/src/subdir.mk
-include Release.old/libraries/Adafruit_NeoPixel/subdir.mk
-include Release.old/core/core/umm_malloc/subdir.mk
-include Release.old/core/core/spiffs/subdir.mk
-include Release.old/core/core/libb64/subdir.mk
-include Release.old/core/core/subdir.mk
-include Release.old/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/arduino.ar \

ELF += \
lamp.elf \

HEX += \
lamp.hex \


# All Target
all: lamp

# Tool invocations
lamp: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-size" -A "/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/lamp.elf"
	@echo 'Finished building target: $@'
	@echo ' '

/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-ar" cru     /home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

lamp.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	${recipe.hooks.linking.prelink.1.pattern}
	${recipe.hooks.linking.prelink.2.pattern}
	${recipe.hooks.linking.prelink.3.pattern}
	${recipe.hooks.linking.prelink.4.pattern}
	"/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/tools/xtensa-lx106-elf-gcc/3.0.4-gcc10.3-1757bed/bin/xtensa-lx106-elf-gcc" -fexceptions -Wl,-Map "-Wl,/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/lamp.map" -g -w -Werror=return-type -Os -nostdlib -Wl,--no-check-sections -u app_entry -u _printf_float -u _scanf_float -Wl,-static "-L/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lib" "-L/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/lib/NONOSDK22x_190703" "-L/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release" "-L/home/stremblay/devel/arduino/Sloeber-V440/arduinoPlugin/packages/esp8266/hardware/esp8266/3.0.2/tools/sdk/libc/xtensa-lx106-elf/lib" "-Tlocal.eagle.flash.ld" -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,spi_flash_read  -o "/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/lamp.elf" -Wl,--start-group   $(LINK_OBJ)   /home/stremblay/devel/arduino/sloeber-workspace/lamp/Release/arduino.ar  -lhal -lphy -lpp -lnet80211 -llwip2-536-feat -lwpa -lcrypto -lmain -lwps -lbearssl -lespnow -lsmartconfig -lairkiss -lwpa2 -lstdc++-exc -lm -lc -lgcc -Wl,--end-group "-L/home/stremblay/devel/arduino/sloeber-workspace/lamp/Release"
	@echo 'Finished building: $@'
	@echo ' '

lamp.hex: $(ELF)
	@echo 'Do all objcopy commands'
	${recipe.objcopy.hex.1.pattern}
	${recipe.objcopy.hex.2.pattern}
	${recipe.objcopy.hex.3.pattern}
	${recipe.objcopy.hex.pattern}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
