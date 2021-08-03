#include "Game2.h"

Game2::Game2(Screen *screen, Gamepad *gamepad) {
	this->screen = screen;
	this->gamepad = gamepad;
}

Game2::~Game2() {
	
}

void Game2::begin() {
	this->screen->buffer->fillScreen(0);
	this->screen->buffer->setTextColor(1, 0);
	this->screen->buffer->setTextSize(1);
	this->screen->buffer->setCursor(0, 0, 2);
	this->screen->buffer->print("Platformer Game!");
	this->screen->update();
	delay(2000);
}

void Game2::loop() {
	this->tick();
	this->draw();
	this->screen->update();
}



#define ARRAY_LENGTH(array) sizeof array / sizeof array[0]

bool rectIntersection(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	return !(x0 > x3 || x1 < x2 || y0 > y3 || y1 < y2);
}

void Game2::tick() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();


	const int size = 10;
	
	this->vy -= 0.1;
	if (this->vy <= -1) {
		this->vy = -1;
	}

	const int mapCellSize = 20;
	const int mapRows = ARRAY_LENGTH(this->map);
	const int mapCols = ARRAY_LENGTH(this->map[0]);
	for (unsigned int row = 0; row < mapRows; row++) {
		for (unsigned int col = 0; col < mapCols; col++) {
			const int cell_x = col * mapCellSize;
			const int cell_y = (mapRows - row) * mapCellSize;
			switch (this->map[row][col]) {
				case 1: break;
				case 2:
					if (rectIntersection(this->x, this->y, this->x + size, this->y + size, cell_x, cell_y, cell_x + mapCellSize, cell_y + mapCellSize)) {
						if (this->vy < 0) {
							this->vy = 0;
						}
						if (this->vx < 0) {
							this->vx = 0;
						}
						if (this->vx > 0) {
							this->vx = 0;
						}
					}
					break;
			}
		}
	}

	if (this->gamepad->isButtonPress(JUMP_BUTTON_PIN) && this->vy == 0) {
		tone(BUZZER_PIN, 120, 15);
		this->vy = 3;
	}
	
	this->vx = 0;

	if (this->gamepad->isButtonHold(LEFT_BUTTON_PIN)) {
		this->vx = -3;
	}

	if (this->gamepad->isButtonHold(RIGHT_BUTTON_PIN)) {
		this->vx = 3;
	}
	
	this->x += this->vx;
	this->y += this->vy;

	this->xc = -this->x + screenWidth / 2;
	//this->yc = this->y - screenHeight / 2;

}


void Game2::draw() {
	const int screenWidth = this->screen->buffer->width();
	const int screenHeight = this->screen->buffer->height();

	this->screen->buffer->fillSprite(0);

	const int mapCellSize = 20;
	const int mapRows = ARRAY_LENGTH(this->map);
	const int mapCols = ARRAY_LENGTH(this->map[0]);
	for (unsigned int row = 0; row < mapRows; row++) {
		for (unsigned int col = 0; col < mapCols; col++) {
			const int cell_x = col * mapCellSize;
			const int cell_y = (mapRows - row) * mapCellSize;
			switch (this->map[row][col]) {
				case 1: break;
				case 2:
					this->screen->buffer->drawRect(cell_x + this->xc, screenHeight - cell_y - mapCellSize + this->yc, mapCellSize, mapCellSize, 2);
					break;
			}
		}
	}
	
	const int size = 10;
	this->screen->buffer->drawRect(this->x + this->xc, screenHeight - this->y - size + this->yc, size, size, 1);
}