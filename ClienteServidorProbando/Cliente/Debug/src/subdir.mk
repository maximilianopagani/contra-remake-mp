################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BulletView.cpp \
../src/Cliente.cpp \
../src/EnemyView.cpp \
../src/GameView.cpp \
../src/LevelView.cpp \
../src/PlatformView.cpp \
../src/PlayerView.cpp \
../src/Sprite.cpp \
../src/TcpClient.cpp 

OBJS += \
./src/BulletView.o \
./src/Cliente.o \
./src/EnemyView.o \
./src/GameView.o \
./src/LevelView.o \
./src/PlatformView.o \
./src/PlayerView.o \
./src/Sprite.o \
./src/TcpClient.o 

CPP_DEPS += \
./src/BulletView.d \
./src/Cliente.d \
./src/EnemyView.d \
./src/GameView.d \
./src/LevelView.d \
./src/PlatformView.d \
./src/PlayerView.d \
./src/Sprite.d \
./src/TcpClient.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


