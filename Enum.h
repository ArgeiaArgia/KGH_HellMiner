#pragma once
enum class SceneType
{
	TITLE, GAME, INFO, QUIT, END
};
enum class TileState
{
	REVEALED, HIDEN, FLAG
};
enum class Dir
{
	UP, DOWN, LEFT, RIGHT
};
enum class Challenge
{
	NONE, TIME, MOVE
};

enum class Action 
{
	DIG, FLAG,Select, RESET, TITLE
};