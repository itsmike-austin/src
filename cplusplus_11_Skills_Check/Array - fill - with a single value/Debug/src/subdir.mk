################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Array\ -\ fill\ -\ with\ a\ single\ value.cpp 

OBJS += \
./src/Array\ -\ fill\ -\ with\ a\ single\ value.o 

CPP_DEPS += \
./src/Array\ -\ fill\ -\ with\ a\ single\ value.d 


# Each subdirectory must supply rules for building sources it contributes
src/Array\ -\ fill\ -\ with\ a\ single\ value.o: ../src/Array\ -\ fill\ -\ with\ a\ single\ value.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Array - fill - with a single value.d" -MT"src/Array\ -\ fill\ -\ with\ a\ single\ value.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


