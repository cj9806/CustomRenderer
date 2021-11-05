#pragma once
class time
{
	
private: 
	//time since start of the program
	float totalTime;
	//time at the end of the last frame
	float lastFrameTime;
	//the total time at the last frame
	float DeltaTime;

	float totalTimeLastFrame;
public:
	//return time since start of the program
	float timeSinceStart() const;
	//get the current real world time
	float systemTime() const;
	//time between frames
	float deltaTime() const;

	//reset time to zero again
	void resetTime();
	//set time to a new value
	void setTime(float);

	void tick();
};

