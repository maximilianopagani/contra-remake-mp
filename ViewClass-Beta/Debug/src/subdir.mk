################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ContraRemake.cpp \
../src/Game.cpp \
../src/GameView.cpp \
../src/Level.cpp \
../src/Logger.cpp \
../src/Player.cpp \
../src/Sprite.cpp \
../src/Utils.cpp 

OBJS += \
./src/ContraRemake.o \
./src/Game.o \
./src/GameView.o \
./src/Level.o \
./src/Logger.o \
./src/Player.o \
./src/Sprite.o \
./src/Utils.o 

CPP_DEPS += \
./src/ContraRemake.d \
./src/Game.d \
./src/GameView.d \
./src/Level.d \
./src/Logger.d \
./src/Player.d \
./src/Sprite.d \
./src/Utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


