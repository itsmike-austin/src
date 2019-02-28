################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ size.cpp 

OBJS += \
./src/Map\ -\ size.o 

CPP_DEPS += \
./src/Map\ -\ size.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ size.o: ../src/Map\ -\ size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - size.d" -MT"src/Map\ -\ size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


