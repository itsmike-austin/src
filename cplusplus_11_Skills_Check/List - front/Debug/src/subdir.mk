################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ front.cpp 

OBJS += \
./src/List\ -\ front.o 

CPP_DEPS += \
./src/List\ -\ front.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ front.o: ../src/List\ -\ front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - front.d" -MT"src/List\ -\ front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


