################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ cbegin.cpp 

OBJS += \
./src/Array\ -\ cbegin.o 

CPP_DEPS += \
./src/Array\ -\ cbegin.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ cbegin.o: ../src/Array\ -\ cbegin.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - cbegin.d" -MT"src/Array\ -\ cbegin.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


