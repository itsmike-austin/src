################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ splice.cpp 

OBJS += \
./src/List\ -\ splice.o 

CPP_DEPS += \
./src/List\ -\ splice.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ splice.o: ../src/List\ -\ splice.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - splice.d" -MT"src/List\ -\ splice.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


