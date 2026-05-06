#include "BottomUI.h"
#include "Console.h"

BottomUI::BottomUI(Position pos) : Object(pos)
{
}

void BottomUI::Update()
{
}

void BottomUI::Render() const
{
	SetColor(COLOR::VIOLET, COLOR::LIGHT_YELLOW);
	Gotoxy(0, 20);
	cout << "W A S D로 이동/ E로 파기/ Q로 깃발\n";
	cout << "      R로 리셋/ ESC로 타이틀      ";
}
