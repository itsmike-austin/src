################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ at.cpp 

OBJS += \
./src/Map\ -\ at.o 

CPP_DEPS += \
./src/Map\ -\ at.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ at.o: ../src/Map\ -\ at.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - at.d" -MT"src/Map\ -\ at.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


