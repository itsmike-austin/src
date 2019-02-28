################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ size.cpp 

OBJS += \
./src/Vector\ -\ size.o 

CPP_DEPS += \
./src/Vector\ -\ size.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ size.o: ../src/Vector\ -\ size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - size.d" -MT"src/Vector\ -\ size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


