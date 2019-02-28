################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Regex\ -\ Search.cpp 

OBJS += \
./src/Regex\ -\ Search.o 

CPP_DEPS += \
./src/Regex\ -\ Search.d 


# Each subdirectory must supply rules for building sources it contributes
src/Regex\ -\ Search.o: ../src/Regex\ -\ Search.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Regex - Search.d" -MT"src/Regex\ -\ Search.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


