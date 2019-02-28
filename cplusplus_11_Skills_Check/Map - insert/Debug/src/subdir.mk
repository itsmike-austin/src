################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ insert.cpp 

OBJS += \
./src/Map\ -\ insert.o 

CPP_DEPS += \
./src/Map\ -\ insert.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ insert.o: ../src/Map\ -\ insert.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - insert.d" -MT"src/Map\ -\ insert.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


