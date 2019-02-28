################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.cpp 

OBJS += \
./src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.o 

CPP_DEPS += \
./src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.d 


# Each subdirectory must supply rules for building sources it contributes
src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.o: ../src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/List - begin - end -- cbegin - end -- crbegin - end.d" -MT"src/List\ -\ begin\ -\ end\ --\ cbegin\ -\ end\ --\ crbegin\ -\ end.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


