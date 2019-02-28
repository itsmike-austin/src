################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Iterator\ -\ iterator_traits.cpp 

OBJS += \
./src/Iterator\ -\ iterator_traits.o 

CPP_DEPS += \
./src/Iterator\ -\ iterator_traits.d 


# Each subdirectory must supply rules for building sources it contributes
src/Iterator\ -\ iterator_traits.o: ../src/Iterator\ -\ iterator_traits.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Iterator - iterator_traits.d" -MT"src/Iterator\ -\ iterator_traits.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


