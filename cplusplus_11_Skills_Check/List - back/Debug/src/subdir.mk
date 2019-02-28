################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ back.cpp 

OBJS += \
./src/List\ -\ back.o 

CPP_DEPS += \
./src/List\ -\ back.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ back.o: ../src/List\ -\ back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - back.d" -MT"src/List\ -\ back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


