################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ erase.cpp 

OBJS += \
./src/Map\ -\ erase.o 

CPP_DEPS += \
./src/Map\ -\ erase.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ erase.o: ../src/Map\ -\ erase.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - erase.d" -MT"src/Map\ -\ erase.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


