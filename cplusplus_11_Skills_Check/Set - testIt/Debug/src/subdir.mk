################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Set\ -\ testIt.cpp 

OBJS += \
./src/Set\ -\ testIt.o 

CPP_DEPS += \
./src/Set\ -\ testIt.d 


# Each subdirectory must supply rules for building sources it contributes
src/Set\ -\ testIt.o: ../src/Set\ -\ testIt.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Set - testIt.d" -MT"src/Set\ -\ testIt.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


