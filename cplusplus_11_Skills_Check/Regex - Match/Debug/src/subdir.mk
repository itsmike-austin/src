################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Regex\ -\ Match.cpp 

OBJS += \
./src/Regex\ -\ Match.o 

CPP_DEPS += \
./src/Regex\ -\ Match.d 


# Each subdirectory must supply rules for building sources it contributes
src/Regex\ -\ Match.o: ../src/Regex\ -\ Match.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Regex - Match.d" -MT"src/Regex\ -\ Match.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


