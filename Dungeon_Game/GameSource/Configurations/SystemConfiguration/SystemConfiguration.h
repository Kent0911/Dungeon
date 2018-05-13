#pragma once

#include "../../../Library/KitLib/include/Kitlib.h"
#include "../../../Library/DirectXTK/include/SpriteFont.h"
#include "../../../KitEngine/Render/Render.h"

#define GAME_TITLE "Dungeon_Game"
#define GAMEPAD_THRESHOLD 100

enum class WINDOW {
	Left = 0,
	Top = 0,
	Right = 1080,
	Bottom = 760,
	Width = Right - Left,
	Height = Bottom - Top
};

extern kit::vec2 g_windowSize;

enum class FRAME_RATE {
	Numerator = 60,
	Denominator = 1
};

enum class DEVICE :bool {
	GamePad = true,
	KeyboradAndMouse = false
};

