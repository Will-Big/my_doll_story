#pragma once
#include "Object.h"

class Item;
class Map;
class Texture;

class Block :
	public Object
{
private:
	// 괴물이 된 블록 ㅜㅜ
	// 미안해 ...
	

	bool isOnOff;
	bool arrWallOnOff[(UINT)POS::LAST]; // UP LEFT DOWN RIGHT
	bool arrRibbonOnOff[(UINT)POS::LAST]; // UP LEFT DOWN RIGHT // ribbon 벽에 대한 배열

	// Item 관련 멤버 변수
	Map* m_pMap;
	Item* m_pItem;
	bool m_bItemMoving;
	MapIndex m_sBlockIndex;
	Vec2 m_vDir;

	// 찢어진 블록 관련 멤버 변수
	bool isTorn;

	bool m_bIsConnected;

public:
	int m_NotRenderY=-1;//렌더하면안되는 인덱스
	int m_NotRenderX=-1;//렌더하면안되는 인덱스

	Texture* m_pTexture[5]; //세로벽 , 가로벽 , 세로리본 , 가로리본 , 찢어진 종이 순서
public:
	void SetBool(bool _onoff) { isOnOff = _onoff; }
	bool GetBool() { return isOnOff; }
	void SetWallBool(POS _pos);
	void SetRibbonBool(POS _pos);
	bool CheckBlock(KEY _key);
	bool CheckRibbon(KEY _key);
	// Item 관련 멤버 함수
	bool IsItem() { return m_pItem != nullptr; }				// 아이템이 있는지 확인하는 함수
	Item* GetItem() { return m_pItem; }							// 해당 블록에 있는 아이템 가져오기 (다운캐스팅 해서 자신의 클래스에 맞게 사용)
	void SetItem(Item* _pItem) { m_pItem = _pItem; }            // 현재 블록에 아이템 포인터 등록
	void MoveItem(const Vec2& _vDir);							// 아이템을 해당 방향으로 보내기
	void ChangeItemIndex(MapIndex _sItemIndex, Item* _pItem);	// 아이템의 인덱스를 변경(Move Item 이후 자동적으로 수행됨)
	// 솜
	void ChangeCottonIndex(MapIndex _NewItemIndex);				// 솜 멤버변수 인덱스를 최신화 시켜주기 위함
	void MoveCotton(MapIndex _otherCotton, const Vec2& _vDir, MapIndex _playerIndex);
	void ChangeItemCottonIndex(MapIndex _sItemIndex, Item* _pItem, MapIndex _playerIndex, const Vec2& _vDir);
	// 찢어진 블록 관련 멤버 변수
	void SetBool_Torn(bool _onoff) { isTorn = _onoff; }
	bool GetBool_Torn() { return isTorn; }

public:
	void update() override;
	void render(HDC _dc) override;

public:
	Block(MapIndex _sBlockIndex, Map* _pMap);
	~Block();
};

