################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HKPD_Program.c \
../LCD_Program.c \
../MDIO_Program.c \
../main.c \
../stack_fun.c 

OBJS += \
./HKPD_Program.o \
./LCD_Program.o \
./MDIO_Program.o \
./main.o \
./stack_fun.o 

C_DEPS += \
./HKPD_Program.d \
./LCD_Program.d \
./MDIO_Program.d \
./main.d \
./stack_fun.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


