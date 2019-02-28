################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ data.cpp 

OBJS += \
./src/Vector\ -\ data.o 

CPP_DEPS += \
./src/Vector\ -\ data.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ data.o: ../src/Vector\ -\ data.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - data.d" -MT"src/Vector\ -\ data.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


