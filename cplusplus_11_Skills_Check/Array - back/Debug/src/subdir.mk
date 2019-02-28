################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ back.cpp 

OBJS += \
./src/Array\ -\ back.o 

CPP_DEPS += \
./src/Array\ -\ back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ back.o: ../src/Array\ -\ back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - back.d" -MT"src/Array\ -\ back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


