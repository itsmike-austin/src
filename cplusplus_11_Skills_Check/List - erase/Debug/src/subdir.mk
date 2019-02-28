################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ erase.cpp 

OBJS += \
./src/List\ -\ erase.o 

CPP_DEPS += \
./src/List\ -\ erase.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ erase.o: ../src/List\ -\ erase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - erase.d" -MT"src/List\ -\ erase.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


