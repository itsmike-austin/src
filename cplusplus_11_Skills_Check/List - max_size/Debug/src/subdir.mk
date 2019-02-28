################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ max_size.cpp 

OBJS += \
./src/List\ -\ max_size.o 

CPP_DEPS += \
./src/List\ -\ max_size.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ max_size.o: ../src/List\ -\ max_size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - max_size.d" -MT"src/List\ -\ max_size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


