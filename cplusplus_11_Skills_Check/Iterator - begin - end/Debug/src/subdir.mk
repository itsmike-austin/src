################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ begin\ -\ end.cpp 

OBJS += \
./src/Iterator\ -\ begin\ -\ end.o 

CPP_DEPS += \
./src/Iterator\ -\ begin\ -\ end.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ begin\ -\ end.o: ../src/Iterator\ -\ begin\ -\ end.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - begin - end.d" -MT"src/Iterator\ -\ begin\ -\ end.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


