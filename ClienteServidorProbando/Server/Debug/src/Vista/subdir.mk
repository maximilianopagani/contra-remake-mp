################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Vista/BulletView.cpp \
../src/Vista/EnemyView.cpp \
../src/Vista/GameView.cpp \
../src/Vista/LevelView.cpp \
../src/Vista/PlatformView.cpp \
../src/Vista/PlayerView.cpp \
../src/Vista/Sprite.cpp 

OBJS += \
./src/Vista/BulletView.o \
./src/Vista/EnemyView.o \
./src/Vista/GameView.o \
./src/Vista/LevelView.o \
./src/Vista/PlatformView.o \
./src/Vista/PlayerView.o \
./src/Vista/Sprite.o 

CPP_DEPS += \
./src/Vista/BulletView.d \
./src/Vista/EnemyView.d \
./src/Vista/GameView.d \
./src/Vista/LevelView.d \
./src/Vista/PlatformView.d \
./src/Vista/PlayerView.d \
./src/Vista/Sprite.d 


# Each subdirectory must supply rules for building sources it contributes
src/Vista/%.o: ../src/Vista/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


