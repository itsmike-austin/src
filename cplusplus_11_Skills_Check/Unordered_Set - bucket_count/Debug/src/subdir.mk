################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Unordered_Set\ -\ bucket_count.cpp 

OBJS += \
./src/Unordered_Set\ -\ bucket_count.o 

CPP_DEPS += \
./src/Unordered_Set\ -\ bucket_count.d 


# Each subdirectory must supply rules for building sources it contributes
src/Unordered_Set\ -\ bucket_count.o: ../src/Unordered_Set\ -\ bucket_count.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Unordered_Set - bucket_count.d" -MT"src/Unordered_Set\ -\ bucket_count.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


