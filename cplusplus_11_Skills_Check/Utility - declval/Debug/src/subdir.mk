################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utility\ -\ declval.cpp 

OBJS += \
./src/Utility\ -\ declval.o 

CPP_DEPS += \
./src/Utility\ -\ declval.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utility\ -\ declval.o: ../src/Utility\ -\ declval.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Utility - declval.d" -MT"src/Utility\ -\ declval.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


