################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ max_size.cpp 

OBJS += \
./src/Vector\ -\ max_size.o 

CPP_DEPS += \
./src/Vector\ -\ max_size.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ max_size.o: ../src/Vector\ -\ max_size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - max_size.d" -MT"src/Vector\ -\ max_size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


