################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ empty.cpp 

OBJS += \
./src/Map\ -\ empty.o 

CPP_DEPS += \
./src/Map\ -\ empty.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ empty.o: ../src/Map\ -\ empty.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - empty.d" -MT"src/Map\ -\ empty.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


