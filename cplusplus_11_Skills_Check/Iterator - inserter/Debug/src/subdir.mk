################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ inserter.cpp 

OBJS += \
./src/Iterator\ -\ inserter.o 

CPP_DEPS += \
./src/Iterator\ -\ inserter.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ inserter.o: ../src/Iterator\ -\ inserter.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - inserter.d" -MT"src/Iterator\ -\ inserter.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


