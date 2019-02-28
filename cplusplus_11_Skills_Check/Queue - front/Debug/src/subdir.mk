################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ front.cpp 

OBJS += \
./src/Queue\ -\ front.o 

CPP_DEPS += \
./src/Queue\ -\ front.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ front.o: ../src/Queue\ -\ front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - front.d" -MT"src/Queue\ -\ front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


