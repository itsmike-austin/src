################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Valarray\ -\ begin\ end.cpp 

OBJS += \
./src/Valarray\ -\ begin\ end.o 

CPP_DEPS += \
./src/Valarray\ -\ begin\ end.d 


# Each subdirectory must supply rules for building sources it contributes
src/Valarray\ -\ begin\ end.o: ../src/Valarray\ -\ begin\ end.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Valarray - begin end.d" -MT"src/Valarray\ -\ begin\ end.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

