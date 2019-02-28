################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ begin\ -\ end.cpp 

OBJS += \
./src/Array\ -\ begin\ -\ end.o 

CPP_DEPS += \
./src/Array\ -\ begin\ -\ end.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ begin\ -\ end.o: ../src/Array\ -\ begin\ -\ end.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - begin - end.d" -MT"src/Array\ -\ begin\ -\ end.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


