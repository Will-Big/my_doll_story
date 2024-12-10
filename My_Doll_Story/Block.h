#pragma once
#include "Object.h"

class Item;
class Map;
class Texture;

class Block :
	public Object
{
private:
	// ������ �� ��� �̤�
	// �̾��� ...
	

	bool isOnOff;
	bool arrWallOnOff[(UINT)POS::LAST]; // UP LEFT DOWN RIGHT
	bool arrRibbonOnOff[(UINT)POS::LAST]; // UP LEFT DOWN RIGHT // ribbon ���� ���� �迭

	// Item ���� ��� ����
	Map* m_pMap;
	Item* m_pItem;
	bool m_bItemMoving;
	MapIndex m_sBlockIndex;
	Vec2 m_vDir;

	// ������ ��� ���� ��� ����
	bool isTorn;

	bool m_bIsConnected;

public:
	int m_NotRenderY=-1;//�����ϸ�ȵǴ� �ε���
	int m_NotRenderX=-1;//�����ϸ�ȵǴ� �ε���

	Texture* m_pTexture[5]; //���κ� , ���κ� , ���θ��� , ���θ��� , ������ ���� ����
public:
	void SetBool(bool _onoff) { isOnOff = _onoff; }
	bool GetBool() { return isOnOff; }
	void SetWallBool(POS _pos);
	void SetRibbonBool(POS _pos);
	bool CheckBlock(KEY _key);
	bool CheckRibbon(KEY _key);
	// Item ���� ��� �Լ�
	bool IsItem() { return m_pItem != nullptr; }				// �������� �ִ��� Ȯ���ϴ� �Լ�
	Item* GetItem() { return m_pItem; }							// �ش� ��Ͽ� �ִ� ������ �������� (�ٿ�ĳ���� �ؼ� �ڽ��� Ŭ������ �°� ���)
	void SetItem(Item* _pItem) { m_pItem = _pItem; }            // ���� ��Ͽ� ������ ������ ���
	void MoveItem(const Vec2& _vDir);							// �������� �ش� �������� ������
	void ChangeItemIndex(MapIndex _sItemIndex, Item* _pItem);	// �������� �ε����� ����(Move Item ���� �ڵ������� �����)
	// ��
	void ChangeCottonIndex(MapIndex _NewItemIndex);				// �� ������� �ε����� �ֽ�ȭ �����ֱ� ����
	void MoveCotton(MapIndex _otherCotton, const Vec2& _vDir, MapIndex _playerIndex);
	void ChangeItemCottonIndex(MapIndex _sItemIndex, Item* _pItem, MapIndex _playerIndex, const Vec2& _vDir);
	// ������ ��� ���� ��� ����
	void SetBool_Torn(bool _onoff) { isTorn = _onoff; }
	bool GetBool_Torn() { return isTorn; }

public:
	void update() override;
	void render(HDC _dc) override;

public:
	Block(MapIndex _sBlockIndex, Map* _pMap);
	~Block();
};

