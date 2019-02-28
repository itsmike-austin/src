################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ insert_after.cpp 

OBJS += \
./src/ForwardList\ -\ insert_after.o 

CPP_DEPS += \
./src/ForwardList\ -\ insert_after.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ insert_after.o: ../src/ForwardList\ -\ insert_after.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - insert_after.d" -MT"src/ForwardList\ -\ insert_after.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


