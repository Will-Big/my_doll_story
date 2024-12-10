#include "pch.h"
#include "Block.h"

#include "SelectGDI.h"
#include "GameManager.h"

#include "Item.h"
#include "Cotton.h"

#include "Map.h"

#include "TimeManager.h"
#include "ResManager.h"
#include "SoundManager.h"

#include "Texture.h"
#include "Animator.h"


Block::Block(MapIndex _sBlockIndex, Map* _pMap)
	: isOnOff(false)
	, m_sBlockIndex(_sBlockIndex)
	, m_vDir(Vec2(0.f, 0.f))
	, m_pMap(_pMap)
	, m_bIsConnected(false)
	, m_bItemMoving(false)
{
	m_vScale = { BLOCK_SIZE, BLOCK_SIZE };

	for (UINT i = 0; i < (UINT)POS::LAST; i++)
		arrWallOnOff[i] = false;
	for (UINT i = 0; i < (UINT)POS::LAST; i++)
		arrRibbonOnOff[i] = false;

	m_pTexture[0] = ResManager::GetInst()->LoadTexture(L"VerticalWall", L"texture\\스테이지\\공통\\바늘.bmp");
	m_pTexture[1] = ResManager::GetInst()->LoadTexture(L"HorizontalWall", L"texture\\스테이지\\공통\\핀.bmp");
	m_pTexture[2] = ResManager::GetInst()->LoadTexture(L"VerticalRibbon", L"texture\\스테이지\\공통\\실벽_세로.bmp");
	m_pTexture[3] = ResManager::GetInst()->LoadTexture(L"HorizontalRibbon", L"texture\\스테이지\\공통\\실벽_가로.bmp");
	m_pTexture[4] = ResManager::GetInst()->LoadTexture(L"TileImage", L"texture\\스테이지\\공통\\찢어진타일.bmp");
}

Block::~Block()
{
}



void Block::update()
{
	if (m_pItem != nullptr)
	{
		if (m_bIsConnected)
		{
			MoveCotton({ 0,0 }, m_vDir, { 0,0 });
		}
		else if (m_bItemMoving)
		{
			MoveItem(m_vDir);
		}
	}
}

void Block::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	MapIndex curIndex = VecToIndex(vPos); //현재 블록 인덱스

	SelectGDI pen(_dc, PEN_TYPE::WHITE);

	if (isOnOff)
	{
		// 찢어진 타일이 뚫려보이게 하려고 수정
		if (isTorn) {
			SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
			Rectangle(_dc
				, (int)(m_vPos.x - m_vScale.x / 2.f)
				, (int)(m_vPos.y - m_vScale.y / 2.f)
				, (int)(m_vPos.x + m_vScale.x / 2.f)
				, (int)(m_vPos.y + m_vScale.y / 2.f));

			TransparentBlt(_dc							//전부 float 으로 작업하기 때문에 int 로의 형변환이 필요함
				, (int)(vPos.x - GetScale().x / 2.f)
				, (int)(vPos.y - GetScale().y / 2.f)
				, (int)GetScale().x 		//가로길이
				, (int)GetScale().y		//세로길이
				, m_pTexture[4]->GetDC()
				, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
				, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
				, m_pTexture[4]->Width()	//자를 사이즈
				, m_pTexture[4]->Height()	//자를 사이즈
				, RGB(255, 255, 255));					//투명화할 색깔
		}
		else
		{
			SelectGDI brush(_dc, BRUSH_TYPE::T);
			Rectangle(_dc
				, (int)(m_vPos.x - m_vScale.x / 2.f)
				, (int)(m_vPos.y - m_vScale.y / 2.f)
				, (int)(m_vPos.x + m_vScale.x / 2.f)
				, (int)(m_vPos.y + m_vScale.y / 2.f));
		}

		if (curIndex.x != m_NotRenderX)
		{
			if (arrWallOnOff[(UINT)POS::LEFT])
			{
				TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
					, (int)(vPos.x - GetScale().x / 1.6f)
					, (int)(vPos.y - GetScale().y / 2.f)
					, (int)GetScale().x / 5.f		//가로길이
					, (int)GetScale().y		//세로길이
					, m_pTexture[0]->GetDC()
					, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
					, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
					, m_pTexture[0]->Width()	//자를 사이즈
					, m_pTexture[0]->Height()	//자를 사이즈
					, RGB(255, 255, 255));					//투명화할 색깔
			}
		}


		if (curIndex.y != m_NotRenderY)
		{
			if (arrWallOnOff[(UINT)POS::UP])
			{
				TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
					, (int)(vPos.x - GetScale().x / 2.f)
					, (int)(vPos.y - GetScale().y / 1.7f)
					, (int)GetScale().x					//가로길이
					, (int)GetScale().y / 5.f					//세로길이
					, m_pTexture[1]->GetDC()
					, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
					, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
					, m_pTexture[1]->Width()	//자를 사이즈
					, m_pTexture[1]->Height()	//자를 사이즈
					, RGB(255, 255, 255));					//투명화할 색깔
			}
		}
	}

	if (arrRibbonOnOff[(UINT)POS::LEFT])
	{
		TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
			, (int)(vPos.x - GetScale().x / 1.4f)
			, (int)(vPos.y - GetScale().y / 2.f)
			, (int)GetScale().x / 2.f			//가로길이
			, (int)GetScale().y / 0.9f					//세로길이
			, m_pTexture[2]->GetDC()
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, m_pTexture[2]->Width()	//자를 사이즈
			, m_pTexture[2]->Height()	//자를 사이즈
			, RGB(255, 255, 255));					//투명화할 색깔
	}
	if (arrRibbonOnOff[(UINT)POS::UP])
	{
		TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
			, (int)(vPos.x - GetScale().x / 2.f)
			, (int)(vPos.y - GetScale().y / 1.3f)
			, (int)GetScale().x / 0.9f			//가로길이
			, (int)GetScale().y / 2.f					//세로길이
			, m_pTexture[3]->GetDC()
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, 0		//텍스쳐 내에서 자를 위치의 좌상단(LT)
			, m_pTexture[3]->Width()	//자를 사이즈
			, m_pTexture[3]->Height()	//자를 사이즈
			, RGB(255, 255, 255));					//투명화할 색깔
	}

}

//벽 bool값 바꿔주는 함수
void Block::SetWallBool(POS _pos)
{
	arrWallOnOff[(UINT)_pos] = !arrWallOnOff[(UINT)_pos];
}

//Ribbon 벽 bool값 바꿔주는 함수
void Block::SetRibbonBool(POS _pos)
{
	arrRibbonOnOff[(UINT)_pos] = !arrRibbonOnOff[(UINT)_pos];
}

bool Block::CheckBlock(KEY _key)
{
	if (KEY::UP == _key)
	{
		return arrWallOnOff[(UINT)POS::UP];
	}
	else if (KEY::DOWN == _key)
	{
		return arrWallOnOff[(UINT)POS::DOWN];
	}
	else if (KEY::LEFT == _key)
	{
		return arrWallOnOff[(UINT)POS::LEFT];
	}
	else if (KEY::RIGHT == _key)
	{
		return arrWallOnOff[(UINT)POS::RIGHT];
	}

	return false;
}

bool Block::CheckRibbon(KEY _key)
{
	if (KEY::UP == _key)
	{
		return arrRibbonOnOff[(UINT)POS::UP];
	}
	else if (KEY::DOWN == _key)
	{
		return arrRibbonOnOff[(UINT)POS::DOWN];
	}
	else if (KEY::LEFT == _key)
	{
		return arrRibbonOnOff[(UINT)POS::LEFT];
	}
	else if (KEY::RIGHT == _key)
	{
		return arrRibbonOnOff[(UINT)POS::RIGHT];
	}

	return false;
}

void Block::MoveItem(const Vec2& _vDir)
{
	static float fDuration = 0.3f;
	static Vec2 vNextDistance = { BLOCK_SIZE, BLOCK_SIZE };
	static Vec2 vStartPos;
	static Vec2 vMoveDistance;

	Vec2 vCurrentPos = m_pItem->GetPos();

	if (!m_bItemMoving)
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_PUSH, CHANNEL::EFFECT);
		m_vDir = _vDir;
		vStartPos = IndexToVec(m_sBlockIndex);
		vMoveDistance = vNextDistance * m_vDir;
		m_bItemMoving = true;
	}

	static float fElapsedTime = 0.f;

	if (fElapsedTime < fDuration)
	{
		vCurrentPos = vCurrentPos + vMoveDistance * (1.f / fDuration) * fDT; // 보간 이동

		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;

		m_bItemMoving = false;

		MapIndex newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };

		// 솜 멤버변수 인덱스를 최신화 시켜주기 위함
		if (m_pItem->GetItemType() == ITEM_TYPE::COTTON)
		{
			ChangeCottonIndex(newItemIndex);
		}

		// 언젠간 고치겠지.. 
		if (m_pItem->GetItemType() == ITEM_TYPE::TAPE)
		{
			if (!m_pMap->m_vecMap[newItemIndex.y][newItemIndex.x]->GetBool_Torn())
			{
				m_pMap->m_vecMap[newItemIndex.y][newItemIndex.x]->SetItem(m_pItem);
				Vec2 vNewPos = IndexToVec(newItemIndex);
				m_pItem->SetPos(vNewPos);
				
			}
			else
			{
				GameManager::GetInst()->GetMap()->MakeTornOnOff(m_sBlockIndex.x + m_vDir.x, m_sBlockIndex.y + m_vDir.y);
			}
			m_pItem = nullptr;
		}

 		else if (m_pItem->GetItemType() == ITEM_TYPE::SCISSORS)
		{
			POS _pos = {};
			if (m_vDir.x > 0)
			{
				_pos = POS::RIGHT;
			}
			else if (m_vDir.x < 0)
			{
				_pos = POS::LEFT;
			}

			else if (m_vDir.y > 0)
			{
				_pos = POS::DOWN;
			}

			else if (m_vDir.y < 0)
			{
				_pos = POS::UP;
			}

			if (m_vDir.x == 0)
			{
				if (!m_pMap->m_vecMap[m_sBlockIndex.y][m_sBlockIndex.x]->arrRibbonOnOff[(int)_pos])
				{
					m_pMap->m_vecMap[newItemIndex.y][newItemIndex.x]->SetItem(m_pItem);
					Vec2 vNewPos = IndexToVec(newItemIndex);
					m_pItem->SetPos(vNewPos);
				}

				else
				{
					GameManager::GetInst()->GetMap()->SetRibbon(m_sBlockIndex.x, m_sBlockIndex.y, _pos);
				}
			
			}
			else if (m_vDir.y == 0)
			{
				if (!m_pMap->m_vecMap[m_sBlockIndex.y][m_sBlockIndex.x]->arrRibbonOnOff[(int)_pos])
				{
					m_pMap->m_vecMap[newItemIndex.y][newItemIndex.x]->SetItem(m_pItem);
					Vec2 vNewPos = IndexToVec(newItemIndex);
					m_pItem->SetPos(vNewPos);
				}

				else
				{
					GameManager::GetInst()->GetMap()->SetRibbon(m_sBlockIndex.x, m_sBlockIndex.y, _pos);
				}
			}
			m_pItem = nullptr;

		}

		else
		{
			ChangeItemIndex(newItemIndex, m_pItem);
		}

		return;
	}

	m_pItem->SetPos(vCurrentPos);
}

void Block::ChangeItemIndex(MapIndex _sItemIndex, Item* _pItem)
{
	// 노 깜빡깜빡 버전 ...

	if (m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->IsItem())
	{
		if (m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
		{
			m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->SetItem(_pItem);
			Vec2 vNewPos = IndexToVec(_sItemIndex);
			_pItem->SetPos(vNewPos);
		}


	}

	else
	{
		m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->SetItem(_pItem);
		Vec2 vNewPos = IndexToVec(_sItemIndex);
		_pItem->SetPos(vNewPos);
	}
	

	m_pItem = nullptr;
}

void Block::ChangeItemCottonIndex(MapIndex _sItemIndex, Item* _pItem, MapIndex _playerIndex, const Vec2& _vDir)
{
	// 노 깜빡깜빡 버전 ...
	m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->SetItem(_pItem);
	Vec2 vNewPos = IndexToVec(_sItemIndex);
	_pItem->SetPos(vNewPos);



	if (_vDir.y > 0)  // 플레이어가 down 키를 누름 
	{
		if (m_sBlockIndex.y < _playerIndex.y) // 플레이어 위에 1번 솜이 있음
		{
			m_pMap->m_vecMap[_sItemIndex.y - (int)_vDir.y][_sItemIndex.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.y < 0) // 플레이어가 up 키를 누름 
	{
		if (m_sBlockIndex.y > _playerIndex.y)  // 플레이어 아래에 1번 솜이 있음
		{
			m_pMap->m_vecMap[_sItemIndex.y - (int)_vDir.y][_sItemIndex.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.x > 0) // 플레이어가 right 키를 누름 
	{
		if (m_sBlockIndex.x < _playerIndex.x) // 플레이어 좌측에 1번 솜
		{
			m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x - (int)_vDir.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.x < 0) // 플레이어가 left 키를 누름 
	{
		if (m_sBlockIndex.x > _playerIndex.x) // 플레이어 우측에 1번 솜
		{
			m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x - (int)_vDir.x]->SetItem(nullptr);
		}
	}

	else
	{
		m_pItem = nullptr;
	}
}

// 솜 멤버변수 인덱스를 최신화 시켜주기 위함
void Block::ChangeCottonIndex(MapIndex _NewItemIndex)
{
	((Cotton*)m_pItem)->SetIndex(_NewItemIndex);
}




// _otherCotton = 움직일 붙은 솜의 위치
void Block::MoveCotton(MapIndex _otherCotton, const Vec2& _vDir, MapIndex _playerIndex)
{
	static Block* pOtherBlock;
	static Item* pOtherItem;

	static float fDuration = 0.3f;
	static Vec2 vNextDistance = { BLOCK_SIZE, BLOCK_SIZE };
	static Vec2 vStartPos;
	static Vec2 vMoveDistance;

	// ////////////////////////////  동일 
	static MapIndex iPlayerIndex;

	Vec2 vCurrentPos = m_pItem->GetPos();

	if (!m_bItemMoving)
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_PUSH, CHANNEL::EFFECT);
		m_bIsConnected = true;
		m_vDir = _vDir;
		vStartPos = IndexToVec(m_sBlockIndex);
		vMoveDistance = vNextDistance * m_vDir;

		// 붙은 솜 초기화
		pOtherBlock = GameManager::GetInst()->GetMap()->m_vecMap[_otherCotton.y][_otherCotton.x];
		pOtherItem = pOtherBlock->GetItem();

		m_bItemMoving = true;

		// ////////////////////////////  동일 
		iPlayerIndex = _playerIndex;
	}

	static float fElapsedTime = 0.f;

	if (fElapsedTime < fDuration)
	{
		vCurrentPos = vCurrentPos + vMoveDistance * (1.f / fDuration) * fDT; // 보간 이동

		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;

		m_bItemMoving = false;
		m_bIsConnected = false;
		MapIndex newItemIndex = {};
		MapIndex otherItemIndex = {};

		if (_vDir.y > 0)  // 플레이어가 down 키를 누름 
		{
			if (m_sBlockIndex.y > iPlayerIndex.y) // 플레이어 아래에 1번 솜이 있음
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}

			else if (m_sBlockIndex.y < iPlayerIndex.y) // 플레이어 위에 1번 솜이 있음
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}
		}

		else if (_vDir.y < 0) // 플레이어가 up 키를 누름 
		{
			if (m_sBlockIndex.y > iPlayerIndex.y)  // 플레이어 아래에 1번 솜이 있음
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}

			else if (m_sBlockIndex.y < iPlayerIndex.y) // 플레이어 위에 1번 솜이 있음
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}
		}

		else if (_vDir.x > 0) // 플레이어가 right 키를 누름 
		{
			if (m_sBlockIndex.x > iPlayerIndex.x) // 플레이어 우측에 1번 솜
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}

			else if (m_sBlockIndex.x < iPlayerIndex.x) // 플레이어 좌측에 1번 솜
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}
		}

		else if (_vDir.x < 0) // 플레이어가 left 키를 누름 
		{
			if (m_sBlockIndex.x > iPlayerIndex.x) // 플레이어 우측에 1번 솜
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}

			else if (m_sBlockIndex.x < iPlayerIndex.x) // 플레이어 좌측에 1번 솜
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}
		}

		/*	MapIndex newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
			MapIndex otherItemIndex = { m_sBlockIndex };*/

			// 솜 멤버변수 인덱스를 최신화 시켜주기 위함
		if (m_pItem->GetItemType() == ITEM_TYPE::COTTON)
		{
			ChangeCottonIndex(newItemIndex);
			pOtherBlock->ChangeCottonIndex(otherItemIndex);
		}

		// 잡힌 솜의 포인터를 옮겨줌
		ChangeItemIndex(newItemIndex, m_pItem);
		//ChangeItemIndex(otherItemIndex, pOtherItem);
		//// 붙은 솜의 포인터를 옮겨줌
		ChangeItemCottonIndex(otherItemIndex, pOtherItem, iPlayerIndex, _vDir);

		return;
	}

	m_pItem->SetPos(vCurrentPos);
	//pOtherItem->SetPos(vCurrentPos - vMoveDistance);

	///////////////////// 동일 
	if (_vDir.y > 0)  // 플레이어가 down 키를 누름 
	{
		if (m_sBlockIndex.y > iPlayerIndex.y) // 플레이어 아래에 1번 솜이 있음
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}

		else if (m_sBlockIndex.y < iPlayerIndex.y) // 플레이어 위에 1번 솜이 있음
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}
	}

	else if (_vDir.y < 0) // 플레이어가 up 키를 누름 
	{
		if (m_sBlockIndex.y > iPlayerIndex.y)  // 플레이어 아래에 1번 솜이 있음
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}

		else if (m_sBlockIndex.y < iPlayerIndex.y) // 플레이어 위에 1번 솜이 있음
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}
	}

	else if (_vDir.x > 0) // 플레이어가 right 키를 누름 
	{
		if (m_sBlockIndex.x > iPlayerIndex.x) // 플레이어 우측에 1번 솜
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}

		else if (m_sBlockIndex.x < iPlayerIndex.x) // 플레이어 좌측에 1번 솜
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}
	}

	else if (_vDir.x < 0) // 플레이어가 left 키를 누름 
	{
		if (m_sBlockIndex.x > iPlayerIndex.x) // 플레이어 우측에 1번 솜
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}

		else if (m_sBlockIndex.x < iPlayerIndex.x) // 플레이어 좌측에 1번 솜
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}
	}
}
