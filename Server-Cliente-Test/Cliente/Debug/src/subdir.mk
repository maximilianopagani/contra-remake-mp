################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GameClient.cpp \
../src/MainCliente.cpp \
../src/SocketClient.cpp 

OBJS += \
./src/GameClient.o \
./src/MainCliente.o \
./src/SocketClient.o 

CPP_DEPS += \
./src/GameClient.d \
./src/MainCliente.d \
./src/SocketClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


