#include <vector>
#include "Object.h"
#include "Defines.h"
#include "Enum.h"
#include "Console.h"
#include "Tile.h"
#include "Position.h"
using std::vector;

class GameManager;
class MapManager;

class Map : public Object
{
public:
	Map(Position pos);
	virtual ~Map() = default;
	// about map
public:
	void InitializePosition(const Position& _pos);
private:
	void GenerateBombs(const Position& _pos);
	void GenerateMap(const vector<unsigned short> indexes);
	//about logic
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void Hide();
	//member variables
private:
	MapManager* m_mapManager;
	GameManager* m_gameManager;
private:
	const int m_checkDirX[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const int m_checkDirY[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
};