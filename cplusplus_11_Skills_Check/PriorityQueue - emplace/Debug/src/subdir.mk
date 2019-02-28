################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Queue\ -\ emplace.cpp 

OBJS += \
./src/Queue\ -\ emplace.o 

CPP_DEPS += \
./src/Queue\ -\ emplace.d 


# Each subdirectory must supply rules for building sources it contributes
src/Queue\ -\ emplace.o: ../src/Queue\ -\ emplace.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Queue - emplace.d" -MT"src/Queue\ -\ emplace.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


