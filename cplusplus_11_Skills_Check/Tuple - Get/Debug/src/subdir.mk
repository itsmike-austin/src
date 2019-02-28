################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tuple\ -\ Get.cpp 

OBJS += \
./src/Tuple\ -\ Get.o 

CPP_DEPS += \
./src/Tuple\ -\ Get.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tuple\ -\ Get.o: ../src/Tuple\ -\ Get.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Tuple - Get.d" -MT"src/Tuple\ -\ Get.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


