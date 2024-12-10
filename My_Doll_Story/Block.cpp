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

	m_pTexture[0] = ResManager::GetInst()->LoadTexture(L"VerticalWall", L"texture\\��������\\����\\�ٴ�.bmp");
	m_pTexture[1] = ResManager::GetInst()->LoadTexture(L"HorizontalWall", L"texture\\��������\\����\\��.bmp");
	m_pTexture[2] = ResManager::GetInst()->LoadTexture(L"VerticalRibbon", L"texture\\��������\\����\\�Ǻ�_����.bmp");
	m_pTexture[3] = ResManager::GetInst()->LoadTexture(L"HorizontalRibbon", L"texture\\��������\\����\\�Ǻ�_����.bmp");
	m_pTexture[4] = ResManager::GetInst()->LoadTexture(L"TileImage", L"texture\\��������\\����\\������Ÿ��.bmp");
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
	MapIndex curIndex = VecToIndex(vPos); //���� ��� �ε���

	SelectGDI pen(_dc, PEN_TYPE::WHITE);

	if (isOnOff)
	{
		// ������ Ÿ���� �շ����̰� �Ϸ��� ����
		if (isTorn) {
			SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
			Rectangle(_dc
				, (int)(m_vPos.x - m_vScale.x / 2.f)
				, (int)(m_vPos.y - m_vScale.y / 2.f)
				, (int)(m_vPos.x + m_vScale.x / 2.f)
				, (int)(m_vPos.y + m_vScale.y / 2.f));

			TransparentBlt(_dc							//���� float ���� �۾��ϱ� ������ int ���� ����ȯ�� �ʿ���
				, (int)(vPos.x - GetScale().x / 2.f)
				, (int)(vPos.y - GetScale().y / 2.f)
				, (int)GetScale().x 		//���α���
				, (int)GetScale().y		//���α���
				, m_pTexture[4]->GetDC()
				, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
				, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
				, m_pTexture[4]->Width()	//�ڸ� ������
				, m_pTexture[4]->Height()	//�ڸ� ������
				, RGB(255, 255, 255));					//����ȭ�� ����
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
				TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
					, (int)(vPos.x - GetScale().x / 1.6f)
					, (int)(vPos.y - GetScale().y / 2.f)
					, (int)GetScale().x / 5.f		//���α���
					, (int)GetScale().y		//���α���
					, m_pTexture[0]->GetDC()
					, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
					, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
					, m_pTexture[0]->Width()	//�ڸ� ������
					, m_pTexture[0]->Height()	//�ڸ� ������
					, RGB(255, 255, 255));					//����ȭ�� ����
			}
		}


		if (curIndex.y != m_NotRenderY)
		{
			if (arrWallOnOff[(UINT)POS::UP])
			{
				TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
					, (int)(vPos.x - GetScale().x / 2.f)
					, (int)(vPos.y - GetScale().y / 1.7f)
					, (int)GetScale().x					//���α���
					, (int)GetScale().y / 5.f					//���α���
					, m_pTexture[1]->GetDC()
					, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
					, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
					, m_pTexture[1]->Width()	//�ڸ� ������
					, m_pTexture[1]->Height()	//�ڸ� ������
					, RGB(255, 255, 255));					//����ȭ�� ����
			}
		}
	}

	if (arrRibbonOnOff[(UINT)POS::LEFT])
	{
		TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
			, (int)(vPos.x - GetScale().x / 1.4f)
			, (int)(vPos.y - GetScale().y / 2.f)
			, (int)GetScale().x / 2.f			//���α���
			, (int)GetScale().y / 0.9f					//���α���
			, m_pTexture[2]->GetDC()
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, m_pTexture[2]->Width()	//�ڸ� ������
			, m_pTexture[2]->Height()	//�ڸ� ������
			, RGB(255, 255, 255));					//����ȭ�� ����
	}
	if (arrRibbonOnOff[(UINT)POS::UP])
	{
		TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
			, (int)(vPos.x - GetScale().x / 2.f)
			, (int)(vPos.y - GetScale().y / 1.3f)
			, (int)GetScale().x / 0.9f			//���α���
			, (int)GetScale().y / 2.f					//���α���
			, m_pTexture[3]->GetDC()
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, m_pTexture[3]->Width()	//�ڸ� ������
			, m_pTexture[3]->Height()	//�ڸ� ������
			, RGB(255, 255, 255));					//����ȭ�� ����
	}

}

//�� bool�� �ٲ��ִ� �Լ�
void Block::SetWallBool(POS _pos)
{
	arrWallOnOff[(UINT)_pos] = !arrWallOnOff[(UINT)_pos];
}

//Ribbon �� bool�� �ٲ��ִ� �Լ�
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
		vCurrentPos = vCurrentPos + vMoveDistance * (1.f / fDuration) * fDT; // ���� �̵�

		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;

		m_bItemMoving = false;

		MapIndex newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };

		// �� ������� �ε����� �ֽ�ȭ �����ֱ� ����
		if (m_pItem->GetItemType() == ITEM_TYPE::COTTON)
		{
			ChangeCottonIndex(newItemIndex);
		}

		// ������ ��ġ����.. 
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
	// �� �������� ���� ...

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
	// �� �������� ���� ...
	m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x]->SetItem(_pItem);
	Vec2 vNewPos = IndexToVec(_sItemIndex);
	_pItem->SetPos(vNewPos);



	if (_vDir.y > 0)  // �÷��̾ down Ű�� ���� 
	{
		if (m_sBlockIndex.y < _playerIndex.y) // �÷��̾� ���� 1�� ���� ����
		{
			m_pMap->m_vecMap[_sItemIndex.y - (int)_vDir.y][_sItemIndex.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.y < 0) // �÷��̾ up Ű�� ���� 
	{
		if (m_sBlockIndex.y > _playerIndex.y)  // �÷��̾� �Ʒ��� 1�� ���� ����
		{
			m_pMap->m_vecMap[_sItemIndex.y - (int)_vDir.y][_sItemIndex.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.x > 0) // �÷��̾ right Ű�� ���� 
	{
		if (m_sBlockIndex.x < _playerIndex.x) // �÷��̾� ������ 1�� ��
		{
			m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x - (int)_vDir.x]->SetItem(nullptr);
		}
	}

	else if (_vDir.x < 0) // �÷��̾ left Ű�� ���� 
	{
		if (m_sBlockIndex.x > _playerIndex.x) // �÷��̾� ������ 1�� ��
		{
			m_pMap->m_vecMap[_sItemIndex.y][_sItemIndex.x - (int)_vDir.x]->SetItem(nullptr);
		}
	}

	else
	{
		m_pItem = nullptr;
	}
}

// �� ������� �ε����� �ֽ�ȭ �����ֱ� ����
void Block::ChangeCottonIndex(MapIndex _NewItemIndex)
{
	((Cotton*)m_pItem)->SetIndex(_NewItemIndex);
}




// _otherCotton = ������ ���� ���� ��ġ
void Block::MoveCotton(MapIndex _otherCotton, const Vec2& _vDir, MapIndex _playerIndex)
{
	static Block* pOtherBlock;
	static Item* pOtherItem;

	static float fDuration = 0.3f;
	static Vec2 vNextDistance = { BLOCK_SIZE, BLOCK_SIZE };
	static Vec2 vStartPos;
	static Vec2 vMoveDistance;

	// ////////////////////////////  ���� 
	static MapIndex iPlayerIndex;

	Vec2 vCurrentPos = m_pItem->GetPos();

	if (!m_bItemMoving)
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_PUSH, CHANNEL::EFFECT);
		m_bIsConnected = true;
		m_vDir = _vDir;
		vStartPos = IndexToVec(m_sBlockIndex);
		vMoveDistance = vNextDistance * m_vDir;

		// ���� �� �ʱ�ȭ
		pOtherBlock = GameManager::GetInst()->GetMap()->m_vecMap[_otherCotton.y][_otherCotton.x];
		pOtherItem = pOtherBlock->GetItem();

		m_bItemMoving = true;

		// ////////////////////////////  ���� 
		iPlayerIndex = _playerIndex;
	}

	static float fElapsedTime = 0.f;

	if (fElapsedTime < fDuration)
	{
		vCurrentPos = vCurrentPos + vMoveDistance * (1.f / fDuration) * fDT; // ���� �̵�

		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;

		m_bItemMoving = false;
		m_bIsConnected = false;
		MapIndex newItemIndex = {};
		MapIndex otherItemIndex = {};

		if (_vDir.y > 0)  // �÷��̾ down Ű�� ���� 
		{
			if (m_sBlockIndex.y > iPlayerIndex.y) // �÷��̾� �Ʒ��� 1�� ���� ����
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}

			else if (m_sBlockIndex.y < iPlayerIndex.y) // �÷��̾� ���� 1�� ���� ����
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}
		}

		else if (_vDir.y < 0) // �÷��̾ up Ű�� ���� 
		{
			if (m_sBlockIndex.y > iPlayerIndex.y)  // �÷��̾� �Ʒ��� 1�� ���� ����
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}

			else if (m_sBlockIndex.y < iPlayerIndex.y) // �÷��̾� ���� 1�� ���� ����
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}
		}

		else if (_vDir.x > 0) // �÷��̾ right Ű�� ���� 
		{
			if (m_sBlockIndex.x > iPlayerIndex.x) // �÷��̾� ������ 1�� ��
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}

			else if (m_sBlockIndex.x < iPlayerIndex.x) // �÷��̾� ������ 1�� ��
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}
		}

		else if (_vDir.x < 0) // �÷��̾ left Ű�� ���� 
		{
			if (m_sBlockIndex.x > iPlayerIndex.x) // �÷��̾� ������ 1�� ��
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex };
			}

			else if (m_sBlockIndex.x < iPlayerIndex.x) // �÷��̾� ������ 1�� ��
			{
				newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
				otherItemIndex = { m_sBlockIndex.y + (int)m_vDir.y * 2, m_sBlockIndex.x + (int)m_vDir.x * 2 };
			}
		}

		/*	MapIndex newItemIndex = { m_sBlockIndex.y + (int)m_vDir.y, m_sBlockIndex.x + (int)m_vDir.x };
			MapIndex otherItemIndex = { m_sBlockIndex };*/

			// �� ������� �ε����� �ֽ�ȭ �����ֱ� ����
		if (m_pItem->GetItemType() == ITEM_TYPE::COTTON)
		{
			ChangeCottonIndex(newItemIndex);
			pOtherBlock->ChangeCottonIndex(otherItemIndex);
		}

		// ���� ���� �����͸� �Ű���
		ChangeItemIndex(newItemIndex, m_pItem);
		//ChangeItemIndex(otherItemIndex, pOtherItem);
		//// ���� ���� �����͸� �Ű���
		ChangeItemCottonIndex(otherItemIndex, pOtherItem, iPlayerIndex, _vDir);

		return;
	}

	m_pItem->SetPos(vCurrentPos);
	//pOtherItem->SetPos(vCurrentPos - vMoveDistance);

	///////////////////// ���� 
	if (_vDir.y > 0)  // �÷��̾ down Ű�� ���� 
	{
		if (m_sBlockIndex.y > iPlayerIndex.y) // �÷��̾� �Ʒ��� 1�� ���� ����
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}

		else if (m_sBlockIndex.y < iPlayerIndex.y) // �÷��̾� ���� 1�� ���� ����
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}
	}

	else if (_vDir.y < 0) // �÷��̾ up Ű�� ���� 
	{
		if (m_sBlockIndex.y > iPlayerIndex.y)  // �÷��̾� �Ʒ��� 1�� ���� ����
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}

		else if (m_sBlockIndex.y < iPlayerIndex.y) // �÷��̾� ���� 1�� ���� ����
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}
	}

	else if (_vDir.x > 0) // �÷��̾ right Ű�� ���� 
	{
		if (m_sBlockIndex.x > iPlayerIndex.x) // �÷��̾� ������ 1�� ��
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}

		else if (m_sBlockIndex.x < iPlayerIndex.x) // �÷��̾� ������ 1�� ��
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}
	}

	else if (_vDir.x < 0) // �÷��̾ left Ű�� ���� 
	{
		if (m_sBlockIndex.x > iPlayerIndex.x) // �÷��̾� ������ 1�� ��
		{
			pOtherItem->SetPos(vCurrentPos - vMoveDistance);
		}

		else if (m_sBlockIndex.x < iPlayerIndex.x) // �÷��̾� ������ 1�� ��
		{
			pOtherItem->SetPos(vCurrentPos + vMoveDistance);
		}
	}
}
