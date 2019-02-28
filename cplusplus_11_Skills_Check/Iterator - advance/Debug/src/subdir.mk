################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ advance.cpp 

OBJS += \
./src/Iterator\ -\ advance.o 

CPP_DEPS += \
./src/Iterator\ -\ advance.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ advance.o: ../src/Iterator\ -\ advance.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - advance.d" -MT"src/Iterator\ -\ advance.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


