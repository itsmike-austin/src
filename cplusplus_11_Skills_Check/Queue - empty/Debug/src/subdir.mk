################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ empty.cpp 

OBJS += \
./src/Queue\ -\ empty.o 

CPP_DEPS += \
./src/Queue\ -\ empty.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ empty.o: ../src/Queue\ -\ empty.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - empty.d" -MT"src/Queue\ -\ empty.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


