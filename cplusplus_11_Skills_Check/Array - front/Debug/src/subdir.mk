################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ front.cpp 

OBJS += \
./src/Array\ -\ front.o 

CPP_DEPS += \
./src/Array\ -\ front.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ front.o: ../src/Array\ -\ front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - front.d" -MT"src/Array\ -\ front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


