################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ at.cpp 

OBJS += \
./src/Vector\ -\ at.o 

CPP_DEPS += \
./src/Vector\ -\ at.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ at.o: ../src/Vector\ -\ at.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - at.d" -MT"src/Vector\ -\ at.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


