################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ resize.cpp 

OBJS += \
./src/List\ -\ resize.o 

CPP_DEPS += \
./src/List\ -\ resize.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ resize.o: ../src/List\ -\ resize.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - resize.d" -MT"src/List\ -\ resize.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


