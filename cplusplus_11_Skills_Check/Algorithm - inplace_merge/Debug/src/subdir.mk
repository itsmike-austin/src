################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ inplace_merge.cpp 

OBJS += \
./src/Algorithm\ -\ inplace_merge.o 

CPP_DEPS += \
./src/Algorithm\ -\ inplace_merge.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ inplace_merge.o: ../src/Algorithm\ -\ inplace_merge.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - inplace_merge.d" -MT"src/Algorithm\ -\ inplace_merge.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


