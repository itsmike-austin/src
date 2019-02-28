################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm\ -\ find.cpp 

OBJS += \
./src/Algorithm\ -\ find.o 

CPP_DEPS += \
./src/Algorithm\ -\ find.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm\ -\ find.o: ../src/Algorithm\ -\ find.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Algorithm - find.d" -MT"src/Algorithm\ -\ find.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


