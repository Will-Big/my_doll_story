#include "pch.h"
#include "Cotton.h"

#include "ResManager.h"
#include "Animator.h"

#include "GameManager.h"
#include "Map.h"
#include "Block.h"
#include "SoundManager.h"


Cotton::Cotton()
	: m_pTexture(nullptr)
	, m_bConnectedCotton(nullptr)
	, m_cCottonIndex{0, 0}
{
}
	
Cotton::Cotton(int _x, int _y)
	: m_pTexture(nullptr)
	, m_bConnectedCotton(nullptr)
	, m_cCottonIndex{ _y, _x }
{	
	SetItemType(ITEM_TYPE::COTTON);

	SetScale(Vec2(110.f, 110.f));

	// ��������Ʈ ����
	m_pTexture = ResManager::GetInst()->LoadTexture(L"CottonImage", L"texture\\��������\\����\\��.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Cotton", m_pTexture, Vec2(0.f, 0.f), Vec2(110.f, 114.f), Vec2(0.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"Cotton", true);
}

Cotton::~Cotton()
{
}

void Cotton::Use()
{
}

void Cotton::update()
{
}


void Cotton::render(HDC _dc)		
{
	component_render(_dc);
}

void Cotton::CheckConnect(int _exceptDir, MapIndex _sPlayerDir)
{

	// �̹� ����Ǿ��ִ� ���¸� üũ �� �ʿ� x
	if (m_bConnectedCotton != nullptr)
	{
		return;
	}


	if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
	{
		MapIndex keyIndex = {};


		switch (_exceptDir)
		{
		case 0: // �÷��̾� ���� ���� : up
			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 0, 1 };
			ExceptionConnect( _sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			break;
		case 1: // �÷��̾� ���� ���� : down
			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 0, 1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			break;
		case 2: // �÷��̾� ���� ���� : left
			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			break;
		case 3: // �÷��̾� ���� ���� : right
			keyIndex = { 0, 1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // �÷��̾� ���� ���� ���� ����

			break;
		}
	}
}

void Cotton::ExceptionConnect(MapIndex _sPlayerDir, MapIndex _keyIndex)
{
	// 9 * 7 ���� ��� �� ����ó��
	if (m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y > 6 or m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y < 0
		or m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x > 8 or m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x < 0)
	{
		return;
	}
	// �÷��̾� ���� ���� �������� _keyIndex ���⿡ �������� �ִ���
	if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->IsItem())
	{
		// �� �������� �� �̶��
		if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON))
		{

			if ((((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem()))->GetConnectedCotton() != nullptr))
			{
				return;
			}

			MapIndex test = _keyIndex;
			if (_keyIndex.x == 0)
			{
				if (_keyIndex.y < 0)
				{
					test.y = (UINT)KEY::UP;
				}
				else
				{
					test.y = (UINT)KEY::DOWN;
				}

				if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y][m_cCottonIndex.x + _sPlayerDir.x]->CheckBlock((KEY)test.y) or GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y ][m_cCottonIndex.x + _sPlayerDir.x]->CheckRibbon((KEY)test.y))
				{
					return;
				}
			}
			else if (_keyIndex.y == 0)
			{
				if (_keyIndex.x < 0)
				{
					test.x = (UINT)KEY::LEFT;
				}

				else
				{
					test.x = (UINT)KEY::RIGHT;
				}

				if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y][m_cCottonIndex.x + _sPlayerDir.x ]->CheckBlock((KEY)test.x) or GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y][m_cCottonIndex.x + _sPlayerDir.x]->CheckRibbon((KEY)test.x))
				{
					return;
				}
			}
			
			// 1�� �ذ� 2�� �� ���� Connect
			((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()))->ConnectCotton(((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem())));
			((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem()))->ConnectCotton(((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem())));

			SoundManager::GetInst()->PlaySound(SOUND::E_ITEM, CHANNEL::EFFECT);

			// �� ���� �ƴ��� �˻�� �ڵ�
			Cotton* cotton = ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()))->GetConnectedCotton();
			int a = 0;
		}
	}
}

bool Cotton::ExceptionMove(MapIndex _playerDir, MapIndex _catchIndex, int _exceptionDir, KEY _key, bool _isBack)
{
	if (m_bConnectedCotton != nullptr) // ��� �ִ� ���� ����� ���¶��
	{
		MapIndex connectIndex = m_bConnectedCotton->GetIndex();

		if(m_cCottonIndex.y + _catchIndex.y == connectIndex.y && m_cCottonIndex.x + _catchIndex.x == connectIndex.x) // ��� �ִ� ����� ������ �� �տ� �������� ���̶��
		{

			// �÷��̾ ����� 2���� ���� �� ��ĭ ������ �ִ� ��Ȳ���� �о����� �Ͼ�� ���� ���� �ڵ�
			if (_isBack)
			{
				int a = 0;
			}

			// 9 * 7 ���� ��� �� ����ó��
			else if (m_cCottonIndex.y + _catchIndex.y * 2 > 6 or m_cCottonIndex.y + _catchIndex.y * 2 < 0
				or m_cCottonIndex.x + _catchIndex.x * 2 > 8 or m_cCottonIndex.x + _catchIndex.x * 2 < 0)
			{
				
				return false;
			}

			// ��� �ִ� ����� ������ �� �տ� �� �տ� �������� �ִٸ�
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y * 2][m_cCottonIndex.x + _catchIndex.x * 2]->IsItem()))
			{
				return false;
			}	
			// ��� �ִ� ����� ������ �� �տ� �� �տ� ���� �ִٸ�
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckBlock(_key))) 
			{
				return false;
			}
			// ��� �ִ� ����� ������ �� �տ� �� �տ� ������ �ִٸ�
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckRibbon(_key)))
			{
				return false;
			}
			// ��� �ִ� ����� ������ �� �տ� �� �տ� ������ �ִٸ�
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y * 2][m_cCottonIndex.x + _catchIndex.x * 2]->GetBool_Torn()))
			{
				return false;
			}

		}

		// �� ���� ���� (����, ����) �� �Ǵ��Ͽ� �̵� ���� 
		else // ��� �ִ� ����� ������ ���� �����̳� ������ ���� �ִ�.  
		{
			MapIndex leftCheck = {};
			MapIndex rightCheck = {};
			switch (_exceptionDir)
			{
			case 0: // �÷��̾� ���� ���� : up
				leftCheck = { 0, -1 };
				rightCheck = { 0, 1 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 1: // �÷��̾� ���� ���� : down
				leftCheck = { 0, 1 };
				rightCheck = { 0, -1 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 2: // �÷��̾� ���� ���� : left
				leftCheck = { 1, 0 };
				rightCheck = { -1, 0 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 3: // �÷��̾� ���� ���� : right
				leftCheck = { -1, 0 };
				rightCheck = { 1, 0 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			}
		}
	}

	// ��� �ִ� ���� ����� ���� �ƴ϶��
	else
	{
		// 9 * 7 ���� ��� �� ����ó��
		if (m_cCottonIndex.y + _playerDir.y > 6 or m_cCottonIndex.y + _playerDir.y< 0
			or m_cCottonIndex.x + _playerDir.x>8  or m_cCottonIndex.x + _playerDir.x < 0)
		{
			return false;
		}

		// 9 * 7 ���� ��� �� ����ó��
		else if (m_cCottonIndex.y + _catchIndex.y > 6 or m_cCottonIndex.y + _catchIndex.y < 0
			or m_cCottonIndex.x + _catchIndex.x>8 or m_cCottonIndex.x + _catchIndex.x < 0)
		{
			int a = 0;
		}

		// ��� �ִ� �� �տ� �������� �ִٸ�
		else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->IsItem())
		{
			// ��� �ִ� �� �տ� ������ �ִٸ�
			if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckRibbon(_key))
			{
				// �տ� ������ �ִ� �������� �����δٸ�
				if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _playerDir.y][m_cCottonIndex.x + _playerDir.x]->CheckRibbon(_key))
				{
					return false;
				}
			}
			// ��� �ִ� �� �տ� ������ �ִٸ�
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::SCISSORS)
			{
				// �տ� ������ �ִ� �������� �����δٸ�
				if (m_cCottonIndex.y + _catchIndex.y == m_cCottonIndex.y + _playerDir.y && m_cCottonIndex.x + _playerDir.x == m_cCottonIndex.x + _catchIndex.x)
				{
					return false;
				}
			}
			// ��� �ִ� �� �տ� �������� �ִٸ�
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::TAPE)
			{
				// �տ� �������� �ִ� �������� �����δٸ�
				if (m_cCottonIndex.y + _catchIndex.y == m_cCottonIndex.y + _playerDir.y && m_cCottonIndex.x + _playerDir.x == m_cCottonIndex.x + _catchIndex.x)
				{
					return false;
				}
			}
			// ��� �ִ� �� �տ� ������ �ִٸ�
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
			{
				// �տ� �������� �ִ� �������� �����δٸ�
				if (m_cCottonIndex.y + _catchIndex.y == m_cCottonIndex.y + _playerDir.y && m_cCottonIndex.x + _playerDir.x == m_cCottonIndex.x + _catchIndex.x)
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

bool Cotton::ExceptionSideCotton(MapIndex _leftCheck, MapIndex _rightCheck)
{
	// 9 * 7 �� ���ο����� ���̵� ���� �˻� 
	if (m_cCottonIndex.y + _leftCheck.y <= 6 and m_cCottonIndex.y + _leftCheck.y >= 0 and m_cCottonIndex.x + _leftCheck.x <= 8 and m_cCottonIndex.x + _leftCheck.x >= 0)
	{
		if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _leftCheck.y][m_cCottonIndex.x + _leftCheck.x]->IsItem()) // ��� �ִ� ����� �� ������ �������� �ִٸ�
		{
			if ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _leftCheck.y][m_cCottonIndex.x + _leftCheck.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)) // �� �������� ���̶��
			{
				return false;
			}
		}

		// �ڷΰ��� 
	}
	
	// 9 * 7 �� ���ο����� ���̵� ���� �˻� 
	if (m_cCottonIndex.y + _rightCheck.y <= 6 and m_cCottonIndex.y + _rightCheck.y >= 0 and m_cCottonIndex.x + _rightCheck.x <= 8 and m_cCottonIndex.x + _rightCheck.x >= 0)
	{
		if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _rightCheck.y][m_cCottonIndex.x + _rightCheck.x]->IsItem()) // ��� �ִ� ����� �� ������ �������� �ִٸ�
		{
			if ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _rightCheck.y][m_cCottonIndex.x + _rightCheck.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)) // �� �������� ���̶��
			{
				return false;
			}
		}
	}
	

	return true;
}
