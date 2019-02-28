################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Numeric\ -\ Iota.cpp 

OBJS += \
./src/Numeric\ -\ Iota.o 

CPP_DEPS += \
./src/Numeric\ -\ Iota.d 


# Each subdirectory must supply rules for building sources it contributes
src/Numeric\ -\ Iota.o: ../src/Numeric\ -\ Iota.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Numeric - Iota.d" -MT"src/Numeric\ -\ Iota.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


