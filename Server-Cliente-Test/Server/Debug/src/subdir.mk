################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/GameServer.cpp \
../src/SocketServer.cpp \
../src/TcpListener.cpp \
../src/main.cpp 

OBJS += \
./src/GameServer.o \
./src/SocketServer.o \
./src/TcpListener.o \
./src/main.o 

CPP_DEPS += \
./src/GameServer.d \
./src/SocketServer.d \
./src/TcpListener.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


