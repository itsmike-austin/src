################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ unique.cpp 

OBJS += \
./src/ForwardList\ -\ unique.o 

CPP_DEPS += \
./src/ForwardList\ -\ unique.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ unique.o: ../src/ForwardList\ -\ unique.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - unique.d" -MT"src/ForwardList\ -\ unique.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


