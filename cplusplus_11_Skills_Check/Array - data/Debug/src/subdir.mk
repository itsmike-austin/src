################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ data.cpp 

OBJS += \
./src/Array\ -\ data.o 

CPP_DEPS += \
./src/Array\ -\ data.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ data.o: ../src/Array\ -\ data.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - data.d" -MT"src/Array\ -\ data.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


