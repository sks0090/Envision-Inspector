#pragma once
class Camera
{
public:
	Camera();
	~Camera();

public:
	int SizeX;
	int SizeY;
	int BitDepth;
	int Pitch;
	int cntBand;
	bool isColor;
	bool isLinescan;
};

