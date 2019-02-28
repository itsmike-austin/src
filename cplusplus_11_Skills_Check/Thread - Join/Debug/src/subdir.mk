################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Thread\ -\ Join.cpp 

OBJS += \
./src/Thread\ -\ Join.o 

CPP_DEPS += \
./src/Thread\ -\ Join.d 


# Each subdirectory must supply rules for building sources it contributes
src/Thread\ -\ Join.o: ../src/Thread\ -\ Join.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Thread - Join.d" -MT"src/Thread\ -\ Join.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


