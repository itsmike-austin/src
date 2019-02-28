################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ assign.cpp 

OBJS += \
./src/Vector\ -\ assign.o 

CPP_DEPS += \
./src/Vector\ -\ assign.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ assign.o: ../src/Vector\ -\ assign.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - assign.d" -MT"src/Vector\ -\ assign.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


