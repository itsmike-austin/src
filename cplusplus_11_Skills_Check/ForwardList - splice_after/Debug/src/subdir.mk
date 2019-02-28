################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ForwardList\ -\ splice_after.cpp 

OBJS += \
./src/ForwardList\ -\ splice_after.o 

CPP_DEPS += \
./src/ForwardList\ -\ splice_after.d 


# Each subdirectory must supply rules for building sources it contributes
src/ForwardList\ -\ splice_after.o: ../src/ForwardList\ -\ splice_after.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/ForwardList - splice_after.d" -MT"src/ForwardList\ -\ splice_after.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


