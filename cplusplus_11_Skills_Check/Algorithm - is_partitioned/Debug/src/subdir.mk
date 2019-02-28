################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ is_partitioned.cpp 

OBJS += \
./src/Algorithm\ -\ is_partitioned.o 

CPP_DEPS += \
./src/Algorithm\ -\ is_partitioned.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ is_partitioned.o: ../src/Algorithm\ -\ is_partitioned.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - is_partitioned.d" -MT"src/Algorithm\ -\ is_partitioned.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


