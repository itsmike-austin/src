################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ first.cpp 

OBJS += \
./src/Vector\ -\ first.o 

CPP_DEPS += \
./src/Vector\ -\ first.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ first.o: ../src/Vector\ -\ first.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - first.d" -MT"src/Vector\ -\ first.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


