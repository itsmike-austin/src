################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ erase.cpp 

OBJS += \
./src/Vector\ -\ erase.o 

CPP_DEPS += \
./src/Vector\ -\ erase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ erase.o: ../src/Vector\ -\ erase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - erase.d" -MT"src/Vector\ -\ erase.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


