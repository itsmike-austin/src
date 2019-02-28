################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/String\ -\ Constant\ Iterator.cpp 

OBJS += \
./src/String\ -\ Constant\ Iterator.o 

CPP_DEPS += \
./src/String\ -\ Constant\ Iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/String\ -\ Constant\ Iterator.o: ../src/String\ -\ Constant\ Iterator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/String - Constant Iterator.d" -MT"src/String\ -\ Constant\ Iterator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


