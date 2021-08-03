#pragma once
#include <Arduino.h>
#include "../screen/Screen.h"
#include "../gamepad/Gamepad.h"

class Game2 {
	public:
		Game2(Screen *screen, Gamepad *gamepad);
		~Game2();
		void begin();
		void tick();
		void draw();
		void loop();
	private:
		Screen *screen = nullptr;
		Gamepad *gamepad = nullptr;
		int x = 60;
		int y = 60;
		int vx = 0;
		float vy = -1;
		int xc = 0;
		int yc = 0;
		int map[8][8] = {
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 1, 1, 1, 1}, 
			{1, 1, 1, 1, 2, 2, 1, 1}, 
			{2, 2, 2, 2, 2, 2, 2, 2}
		};
};