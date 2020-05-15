#pragma once

enum class LAYER
{		
	BG,						// ”wŒi
	CHAR,					// ·¬×¸À°
	UI,						// UI
	BUTTON,
	EX,						// ½º±‚È‚Ç
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER& key);
LAYER operator++(LAYER& key);
