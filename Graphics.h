#pragma once
#include "Draw.h"
#include "WinSize.h"


class Graphics {
public:
	Graphics();
	~Graphics();
public:
	void Process(IniDX* iniDX, Draw* draw);
};