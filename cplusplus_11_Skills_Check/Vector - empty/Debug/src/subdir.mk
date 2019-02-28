################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ empty.cpp 

OBJS += \
./src/Vector\ -\ empty.o 

CPP_DEPS += \
./src/Vector\ -\ empty.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ empty.o: ../src/Vector\ -\ empty.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - empty.d" -MT"src/Vector\ -\ empty.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


