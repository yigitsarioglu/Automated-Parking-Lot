################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adcinit.c \
../Src/extiinit.c \
../Src/gpioinit.c \
../Src/lpuartinit.c \
../Src/main.c \
../Src/sevensegment.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/timerinit.c 

OBJS += \
./Src/adcinit.o \
./Src/extiinit.o \
./Src/gpioinit.o \
./Src/lpuartinit.o \
./Src/main.o \
./Src/sevensegment.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/timerinit.o 

C_DEPS += \
./Src/adcinit.d \
./Src/extiinit.d \
./Src/gpioinit.d \
./Src/lpuartinit.d \
./Src/main.d \
./Src/sevensegment.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/timerinit.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DNUCLEO_L552ZE_Q -DSTM32 -DSTM32L5 -DSTM32L552ZETxQ -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adcinit.cyclo ./Src/adcinit.d ./Src/adcinit.o ./Src/adcinit.su ./Src/extiinit.cyclo ./Src/extiinit.d ./Src/extiinit.o ./Src/extiinit.su ./Src/gpioinit.cyclo ./Src/gpioinit.d ./Src/gpioinit.o ./Src/gpioinit.su ./Src/lpuartinit.cyclo ./Src/lpuartinit.d ./Src/lpuartinit.o ./Src/lpuartinit.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/sevensegment.cyclo ./Src/sevensegment.d ./Src/sevensegment.o ./Src/sevensegment.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/timerinit.cyclo ./Src/timerinit.d ./Src/timerinit.o ./Src/timerinit.su

.PHONY: clean-Src

