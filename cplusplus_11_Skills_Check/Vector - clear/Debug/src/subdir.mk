################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ clear.cpp 

OBJS += \
./src/Vector\ -\ clear.o 

CPP_DEPS += \
./src/Vector\ -\ clear.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ clear.o: ../src/Vector\ -\ clear.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - clear.d" -MT"src/Vector\ -\ clear.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


