################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/String\ -\ Length\ or\ Size.cpp 

OBJS += \
./src/String\ -\ Length\ or\ Size.o 

CPP_DEPS += \
./src/String\ -\ Length\ or\ Size.d 


# Each subdirectory must supply rules for building sources it contributes
src/String\ -\ Length\ or\ Size.o: ../src/String\ -\ Length\ or\ Size.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/String - Length or Size.d" -MT"src/String\ -\ Length\ or\ Size.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


