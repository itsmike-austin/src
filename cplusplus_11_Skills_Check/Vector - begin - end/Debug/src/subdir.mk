################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vector\ -\ begin\ -\ end.cpp 

OBJS += \
./src/Vector\ -\ begin\ -\ end.o 

CPP_DEPS += \
./src/Vector\ -\ begin\ -\ end.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vector\ -\ begin\ -\ end.o: ../src/Vector\ -\ begin\ -\ end.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Vector - begin - end.d" -MT"src/Vector\ -\ begin\ -\ end.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


