################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utility\ -\ forward.cpp 

OBJS += \
./src/Utility\ -\ forward.o 

CPP_DEPS += \
./src/Utility\ -\ forward.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utility\ -\ forward.o: ../src/Utility\ -\ forward.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Utility - forward.d" -MT"src/Utility\ -\ forward.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


