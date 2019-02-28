################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ pop_front\ -\ push_front.cpp 

OBJS += \
./src/ForwardList\ -\ pop_front\ -\ push_front.o 

CPP_DEPS += \
./src/ForwardList\ -\ pop_front\ -\ push_front.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ pop_front\ -\ push_front.o: ../src/ForwardList\ -\ pop_front\ -\ push_front.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - pop_front - push_front.d" -MT"src/ForwardList\ -\ pop_front\ -\ push_front.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


