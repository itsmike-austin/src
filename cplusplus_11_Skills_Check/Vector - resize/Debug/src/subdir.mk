################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ resize.cpp 

OBJS += \
./src/Vector\ -\ resize.o 

CPP_DEPS += \
./src/Vector\ -\ resize.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ resize.o: ../src/Vector\ -\ resize.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - resize.d" -MT"src/Vector\ -\ resize.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


