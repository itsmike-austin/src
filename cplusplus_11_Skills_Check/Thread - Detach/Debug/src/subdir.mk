################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Thread\ -\ Detach.cpp 

OBJS += \
./src/Thread\ -\ Detach.o 

CPP_DEPS += \
./src/Thread\ -\ Detach.d 


# Each subdirectory must supply rules for building sources it contributes
src/Thread\ -\ Detach.o: ../src/Thread\ -\ Detach.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Thread - Detach.d" -MT"src/Thread\ -\ Detach.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


