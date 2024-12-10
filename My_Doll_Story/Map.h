#pragma once
#include <stack>
#include "Object.h"

// �� ���� ����
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
	vector<Block*> m_vecMap[Y_MAX]; // Y ���� ������!
	vector<UINT> m_vecUndo;         // ��� �ൿ ��� 

	set<Vec2> m_setWall;

	MapIndex m_sPlayerIndex; // �÷��̾� ������ġ
	std::stack<MapIndex> m_PrevPlayerPos;

	Vec2 m_vMapPos;
	Vec2 m_vMapScale;

public:
	void MakeOnOff(int _x, int _y);
	void Reset();
	void SetWall(int _x, int _y, POS _pos);
	void SetNewWall(int _x, int _y); //�ܺ�ó��
	void SetRibbon(int _x, int _y,POS _pos); // ribbon setting
	bool Move(KEY _key, MapIndex& _out);


	void init(Player* _player, int _x, int _y, MapIndex _sPlayerIndex, MapIndex& _out);
	void update() override;
	void render(HDC _background) override;

	void Undo();
	void ItemUndo(POS _playerPos);
	// ============ Item ���� ��� �Լ�
	void SetItem(Item* _pItem, int _x, int _y); // ������ Ÿ�԰� ������ �ε����� �޾Ƽ� �������� ������ ����
	bool IsItem(int _x, int _y); // �������� �ش� �ε����� �ִ��� Ȯ��
	bool CheckPath(int _x, int _y,KEY _key); // ������ ���⿡ ���� �ִ��� ������ Ȯ��
	void MakeTornOnOff(int _x, int _y); //������
public:
	Map();
	~Map();
};

