################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Model/Bullet.cpp \
../src/Model/CameraLogic.cpp \
../src/Model/ContraRemake.cpp \
../src/Model/Enemy.cpp \
../src/Model/Game.cpp \
../src/Model/Level.cpp \
../src/Model/Platform.cpp \
../src/Model/Player.cpp \
../src/Model/TcpListener.cpp 

OBJS += \
./src/Model/Bullet.o \
./src/Model/CameraLogic.o \
./src/Model/ContraRemake.o \
./src/Model/Enemy.o \
./src/Model/Game.o \
./src/Model/Level.o \
./src/Model/Platform.o \
./src/Model/Player.o \
./src/Model/TcpListener.o 

CPP_DEPS += \
./src/Model/Bullet.d \
./src/Model/CameraLogic.d \
./src/Model/ContraRemake.d \
./src/Model/Enemy.d \
./src/Model/Game.d \
./src/Model/Level.d \
./src/Model/Platform.d \
./src/Model/Player.d \
./src/Model/TcpListener.d 


# Each subdirectory must supply rules for building sources it contributes
src/Model/%.o: ../src/Model/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -ftest-coverage -fprofile-arcs -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


