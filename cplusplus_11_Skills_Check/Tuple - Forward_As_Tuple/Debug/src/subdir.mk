################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Tuple\ -\ Forward_As_Tuple.cpp 

OBJS += \
./src/Tuple\ -\ Forward_As_Tuple.o 

CPP_DEPS += \
./src/Tuple\ -\ Forward_As_Tuple.d 


# Each subdirectory must supply rules for building sources it contributes
src/Tuple\ -\ Forward_As_Tuple.o: ../src/Tuple\ -\ Forward_As_Tuple.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Tuple - Forward_As_Tuple.d" -MT"src/Tuple\ -\ Forward_As_Tuple.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


