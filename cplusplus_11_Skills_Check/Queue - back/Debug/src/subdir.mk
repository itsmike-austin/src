################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ back.cpp 

OBJS += \
./src/Queue\ -\ back.o 

CPP_DEPS += \
./src/Queue\ -\ back.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ back.o: ../src/Queue\ -\ back.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - back.d" -MT"src/Queue\ -\ back.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


