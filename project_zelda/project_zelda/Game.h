#pragma once
class Game
{
public:
	Game();
	~Game();
public:
	void Init(HWND hwnd);
	void Update();
	void Render();
public:
	HWND _hwnd = {};
	HDC _hdc = {};

public:

	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};
	RECT _rect;
};

