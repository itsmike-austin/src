################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Stack\ -\ emplace.cpp 

OBJS += \
./src/Stack\ -\ emplace.o 

CPP_DEPS += \
./src/Stack\ -\ emplace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Stack\ -\ emplace.o: ../src/Stack\ -\ emplace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Stack - emplace.d" -MT"src/Stack\ -\ emplace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


