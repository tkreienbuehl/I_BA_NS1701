//============================================================================
// Name        : TemperatureGuardian.cpp
// Author      : Melina Scodeller, Tobias Kreienbühl
// Version     :
// Copyright   : I_BA_NS_F1701
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include "../header/Controller.hpp"
#include "../header/SensorWatchDog.hpp"

int main() {
	std::cout << "TemperatureGuardian gestartet" << std::endl; // prints TemperatureGuardian
	pthread_t thread;

	Controller* controller = new Controller();

	SensorWatchDog* watchDog = new SensorWatchDog(controller);

	pthread_create(&thread, NULL, SensorWatchDog::startWatchDog, watchDog);

	controller->startController();

	watchDog->stopWatchDog();

	usleep(50 * 1000);

	delete controller;

	usleep(50 * 1000);

	delete watchDog;

	usleep(50 * 1000);

	std::cout << "bye bye" << std::endl;

}
