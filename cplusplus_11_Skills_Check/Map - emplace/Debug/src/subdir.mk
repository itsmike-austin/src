################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Map\ -\ emplace.cpp 

OBJS += \
./src/Map\ -\ emplace.o 

CPP_DEPS += \
./src/Map\ -\ emplace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Map\ -\ emplace.o: ../src/Map\ -\ emplace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Map - emplace.d" -MT"src/Map\ -\ emplace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


