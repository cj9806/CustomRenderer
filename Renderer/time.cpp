#include "time.h"
#include <ctime>
#include <chrono>
#include "GLFW/glfw3.h"

float time::timeSinceStart() const
{
	return (float)glfwGetTime();
}

float time::systemTime() const
{
	auto sysTime = std::chrono::system_clock::now();
	return 0;
}

float time::deltaTime() const
{
	return DeltaTime;
}

void time::resetTime()
{
	totalTime = 0;
}

void time::setTime(float time)
{
	totalTime = time;
}

void time::tick() 
{
	//increase total time
	totalTime = timeSinceStart();
	//update current deltatime and last delta time
	DeltaTime = totalTime - totalTimeLastFrame;
	totalTimeLastFrame = totalTime;
}