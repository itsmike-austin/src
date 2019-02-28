################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ istream_iterator.cpp 

OBJS += \
./src/Iterator\ -\ istream_iterator.o 

CPP_DEPS += \
./src/Iterator\ -\ istream_iterator.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ istream_iterator.o: ../src/Iterator\ -\ istream_iterator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - istream_iterator.d" -MT"src/Iterator\ -\ istream_iterator.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


