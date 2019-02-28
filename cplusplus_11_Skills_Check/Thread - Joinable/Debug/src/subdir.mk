################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Thread\ -\ Joinable.cpp 

OBJS += \
./src/Thread\ -\ Joinable.o 

CPP_DEPS += \
./src/Thread\ -\ Joinable.d 


# Each subdirectory must supply rules for building sources it contributes
src/Thread\ -\ Joinable.o: ../src/Thread\ -\ Joinable.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Thread - Joinable.d" -MT"src/Thread\ -\ Joinable.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


