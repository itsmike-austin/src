################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Deque\ -\ shrink_to_fit.cpp 

OBJS += \
./src/Deque\ -\ shrink_to_fit.o 

CPP_DEPS += \
./src/Deque\ -\ shrink_to_fit.d 


# Each subdirectory must supply rules for building sources it contributes
src/Deque\ -\ shrink_to_fit.o: ../src/Deque\ -\ shrink_to_fit.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Deque - shrink_to_fit.d" -MT"src/Deque\ -\ shrink_to_fit.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


