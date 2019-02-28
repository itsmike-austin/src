################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ back.cpp 

OBJS += \
./src/Vector\ -\ back.o 

CPP_DEPS += \
./src/Vector\ -\ back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ back.o: ../src/Vector\ -\ back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - back.d" -MT"src/Vector\ -\ back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


