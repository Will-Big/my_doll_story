#pragma once
#include <stack>
#include "Object.h"

// 맵 길이 고정
#define Y_MAX 7
#define X_MAX 9

class Block;
class Player;
class Wall;
class Item;


class Map :
	public Object
{
public:
	vector<Block*> m_vecMap[Y_MAX]; // Y 부터 쓰세요!
	vector<UINT> m_vecUndo;         // 모든 행동 기억 

	set<Vec2> m_setWall;

	MapIndex m_sPlayerIndex; // 플레이어 현재위치
	std::stack<MapIndex> m_PrevPlayerPos;

	Vec2 m_vMapPos;
	Vec2 m_vMapScale;

public:
	void MakeOnOff(int _x, int _y);
	void Reset();
	void SetWall(int _x, int _y, POS _pos);
	void SetNewWall(int _x, int _y); //외벽처리
	void SetRibbon(int _x, int _y,POS _pos); // ribbon setting
	bool Move(KEY _key, MapIndex& _out);


	void init(Player* _player, int _x, int _y, MapIndex _sPlayerIndex, MapIndex& _out);
	void update() override;
	void render(HDC _background) override;

	void Undo();
	void ItemUndo(POS _playerPos);
	// ============ Item 관련 멤버 함수
	void SetItem(Item* _pItem, int _x, int _y); // 아이템 타입과 아이템 인덱스를 받아서 동적으로 아이템 생성
	bool IsItem(int _x, int _y); // 아이템이 해당 인덱스에 있는지 확인
	bool CheckPath(int _x, int _y,KEY _key); // 가려는 방향에 벽이 있는지 없는지 확인
	void MakeTornOnOff(int _x, int _y); //테이프
public:
	Map();
	~Map();
};

