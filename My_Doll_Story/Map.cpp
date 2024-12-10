#include "pch.h"
#include "Map.h"

#include "Block.h"
#include "Player.h"
#include "Scene.h"
#include "Wall.h"
#include "GameManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

#define START_POS_X 560
#define START_POS_Y 120

#include "Main.h"
#include "Item.h"
#include "Cotton.h"
#include "Doll.h"

void Map::update()
{
	//wchar_t szBuffer[255] = {};
	//swprintf_s(szBuffer, L"Y: %d, X: %d", m_sPlayerIndex.y, m_sPlayerIndex.x);
	//SetWindowText(Main::GetInst()->GetMainHwnd(), szBuffer);

	//Undo();
}

Map::Map()
	: m_vecMap{}
	, m_setWall{}
	, m_sPlayerIndex{}
	, m_vMapPos{ 400,0 }
	, m_vMapScale{ 1200,900 }
{
}

Map::~Map()
{
	for (int i = 0; i < Y_MAX; i++)
	{
		for (int j = 0; j < X_MAX; j++)
		{
			//delete m_vecMap[i][j];
		}
	}
}

void Map::init(Player* _player, int _x, int _y, MapIndex _sPlayerIndex, MapIndex& _out)
{

	Vec2 vBlockStartPos = { START_POS_X, START_POS_Y }; // �� ���� 

	for (int i = 0; i < Y_MAX; i++)
	{
		for (int j = 0; j < X_MAX; j++)
		{
			Block* newBlock = new Block({ i, j }, this);
			newBlock->SetPos(vBlockStartPos);
			m_vecMap[i].push_back(newBlock);
			vBlockStartPos.x += BLOCK_SIZE;
		}
		vBlockStartPos.y += BLOCK_SIZE;
		vBlockStartPos.x = START_POS_X;
	}

	bool firstY = true;
	bool firstX = true;

	//��� ����
	for (int i = ((Y_MAX - _y) / 2); i < ((Y_MAX - _y) / 2) + _y; i++)
	{
		if (firstY)
		{
			_out.y = i;
			firstY = false;
		}

		for (int j = (X_MAX - _x) / 2; j < ((X_MAX - _x) / 2) + _x; j++)
		{
			if (firstX)
			{
				_out.x = j;
				firstX = false;
			}

			MakeOnOff(j, i);
			if (i == ((Y_MAX - _y) / 2))
			{
				m_vecMap[i][j]->m_NotRenderY = i;
				SetWall(j, i, POS::UP);
			}
			if (i / (((Y_MAX - _y) / 2) + _y - 1) == 1)
			{
				SetWall(j, i, POS::DOWN);
			}
			if (j == (X_MAX - _x) / 2)
			{
				m_vecMap[i][j]->m_NotRenderX = j;
				SetWall(j, i, POS::LEFT);
			}
			if (j / (((X_MAX - _x) / 2) + _x - 1) == 1)
			{
				SetWall(j, i, POS::RIGHT);
			}
		}
	}


	// �÷��̾� ���� ����
	m_sPlayerIndex = _sPlayerIndex;

}


void Map::MakeOnOff(int _x, int _y)
{
	m_vecMap[_y][_x]->SetBool(true);
}

void Map::SetWall(int _x, int _y, POS _pos)
{
	//�Ѱ��� ��� ����
	m_vecMap[_y][_x]->SetWallBool(_pos);

	//�پ��ִ� ��� ���� 
	UINT next = ((UINT)_pos + 2) % (UINT)POS::LAST;
	int x = 0, y = 0;

	if (next < 2)
	{
		if (next % 2 == 0) //UP
		{
			x = _x;
			y = _y + 1;
		}
		else              //Left
		{
			y = _y;
			x = _x + 1;
		}
	}
	else if (next >= 2)
	{
		if (next % 2 == 0)//Down
		{
			y = _y - 1;
			x = _x;
		}
		else             //Right
		{
			x = _x - 1;
			y = _y;
		}
	}

	if (x >= 0 && x < 9 && y >= 0 && y < 7)
	{
		m_vecMap[y][x]->SetWallBool((POS)next);
	}
}

void Map::SetNewWall(int _x, int _y)
{
	//����ó���� ��ġ�ڰ� 

	for (UINT i = 0; i < (UINT)POS::LAST; i++)
	{
		m_vecMap[_y][_x]->SetWallBool((POS)i);
	}

	if (_x - 1 >= 0)
	{
		if (m_vecMap[_y][_x - 1]->GetBool())
		{
			SetWall(_x - 1, _y, POS::LEFT);
		}
	}

	if (_x + 1 <= 8)
	{
		if (m_vecMap[_y][_x + 1]->GetBool())
		{
			SetWall(_x + 1, _y, POS::RIGHT);
		}
	}

	if (_y - 1 >= 0)
	{
		if (m_vecMap[_y - 1][_x]->GetBool())
		{
			SetWall(_x, _y - 1, POS::UP);
		}
	}

	if (_y + 1 <= 6)
	{
		if (m_vecMap[_y + 1][_x]->GetBool())
		{
			SetWall(_x, _y + 1, POS::DOWN);
		}
	}
}

//���� ������ִ� �Լ�
void Map::SetRibbon(int _x, int _y, POS _pos)
{
	//�Ѱ��� ��� ����
	m_vecMap[_y][_x]->SetRibbonBool(_pos);

	//�پ��ִ� ��� ���� 
	UINT next = ((UINT)_pos + 2) % (UINT)POS::LAST;
	int x = 0, y = 0;

	if (next < 2)
	{
		if (next % 2 == 0) //UP
		{
			x = _x;
			y = _y + 1;
		}
		else              //Left
		{
			y = _y;
			x = _x + 1;
		}
	}
	else if (next >= 2)
	{
		if (next % 2 == 0)//Down
		{
			y = _y - 1;
			x = _x;
		}
		else             //Right
		{
			x = _x - 1;
			y = _y;
		}
	}

	if (x >= 0 && x < 9 && y >= 0 && y < 7)
	{
		m_vecMap[y][x]->SetRibbonBool((POS)next);
	}
}



bool Map::Move(KEY _key, MapIndex& _out)
{
	//�ε����� 0�� �ȵǰ�
	if (m_sPlayerIndex.x >= 0 && m_sPlayerIndex.x < 9 && m_sPlayerIndex.y >= 0 && m_sPlayerIndex.y < 7)
	{
		auto vPlayerDir = GameManager::GetInst()->GetPlayer()->GetDir();
		auto cPlayerLook = GameManager::GetInst()->GetPlayer()->GetLookAt();

		MapIndex catchIndex = { -100, -100 };
		switch (cPlayerLook)
		{
		case 'u':
			catchIndex = { -1, 0 };
			break;
		case 'd':
			catchIndex = { 1, 0 };
			break;
		case 'l':
			catchIndex = { 0, -1 };
			break;
		case 'r':
			catchIndex = { 0, 1 };
			break;
		}

		MapIndex sPlayerDir = { (int)vPlayerDir.y, (int)vPlayerDir.x };

		// 1. ����� ���� ��ġ�� ������ �÷��̾� ���� �� ������ ����� ���� �ִ��� üũ�ϱ� ���� ��ǥ
		// 2. ���� �̵��� ��ġ���� �����¿츦 �˻��� �� ���� �̵��ϱ� �� ��ġ�� �˻����� �ʱ� ���� ����ó�� ��ǥ
		int exceptionDir = -1;
		if (sPlayerDir.y < 0)
			exceptionDir = 0;     // up
		else if (sPlayerDir.y > 0)
			exceptionDir = 1;     // down
		else if (sPlayerDir.x < 0)
			exceptionDir = 2;     // left
		else if (sPlayerDir.x > 0)
			exceptionDir = 3;     // right

		POS _pos = POS::LAST;
		if (sPlayerDir.x < 0)
		{
			_pos = POS::LEFT;
		}
		else if (sPlayerDir.x > 0)
		{
			_pos = POS::RIGHT;
		}
		else if (sPlayerDir.y < 0)
		{
			_pos = POS::UP;
		}
		else if (sPlayerDir.y > 0)
		{
			_pos = POS::DOWN;
		}


		//=============================================================================== �̵� ���� ó�� ===============================================================================================
		//
		// ���� ���� ������ �߰� �ϰ� �ʹٸ� ���⿡ if �� �߰��ؼ� �ۼ��ϱ� !



		// ���� ���� ���� �� �Ǵ� �������� ���� ���� ��
   		if (m_vecMap[m_sPlayerIndex.y][m_sPlayerIndex.x]->CheckBlock(_key) || m_vecMap[m_sPlayerIndex.y][m_sPlayerIndex.x]->CheckRibbon(_key))
		{
			return false;
		}
		else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->GetBool_Torn())
		{
			return false;
		}

		//Scissors item Check
		bool _bScissors = false;

		// �÷��̾� ���� ���� ���� �տ� �������� ���� ��
 		if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->IsItem())
		{
			if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->GetItem()->ItemOn())
			{
				// ��� �ִ� ���°� �ƴ϶��
				if (!GameManager::GetInst()->GetPlayer()->IsGrab())
				{
   					return false;
				}

				// ��� �ִ� ����
				else
				{
					if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->GetItem()->GetItemType() == ITEM_TYPE::SCISSORS)
					{
						if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->CheckRibbon(_key))
						{
							//
						}
						else if (m_sPlayerIndex.y + catchIndex.y * 2 > 6 or m_sPlayerIndex.y + catchIndex.y * 2 < 0 or m_sPlayerIndex.x + catchIndex.x * 2> 8 or m_sPlayerIndex.x + catchIndex.x * 2 < 0)
						{
							return false;
						}
						else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->IsItem())
						{
							if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::TAPE)
							{
								return false;
							}

							else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
							{
								return false;
							}
							else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
							{
								return false;
							}


						}
						else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->GetBool_Torn())
						{
							return false;
						}
						_bScissors = true;
					}

					//Scissors item Check 
					if (!_bScissors &&
						(m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->CheckBlock(_key) ||
							m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->CheckRibbon(_key))) // ����ִ� �������� ���� �������� �� // ������ ���������� /
					{
						return false;
					}

					else if (_bScissors && m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->CheckBlock(_key))
					{
						return false;
					}

					else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->GetBool_Torn() // �������� ������ Ÿ�Ͽ� ������
						&& m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->GetItem()->GetItemType() != ITEM_TYPE::TAPE) // �� �������� �������� �ƴ϶��
					{
						return false;
					}

					// ��� �ִ� �������� ��������� 
					else if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->GetItem()->GetItemType() == ITEM_TYPE::TAPE)
					{
						if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y * 2][m_sPlayerIndex.x + (int)vPlayerDir.x * 2]->IsItem())
						{
							return false;
						}
					}
					
				}

				// ���� ����� ��� ������ ��ġ��
				if (catchIndex.x == (int)vPlayerDir.x and catchIndex.y == (int)vPlayerDir.y)
				{
					// ��� �ִ� �������� ���� �������� ��
					if (m_vecMap[m_sPlayerIndex.y + (int)vPlayerDir.y][m_sPlayerIndex.x + (int)vPlayerDir.x]->CheckBlock(_key))
					{
						return false;
					}
					// ��� �ִ� �������� �� �̶��
					else if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
					{
							if (!((Cotton*)(m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()))->ExceptionMove(sPlayerDir, catchIndex, exceptionDir, _key, false))
						{
							return false;
						}
					}
					// ��� �ִ� �������� ���� �̶��
					else if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
					{
						if (m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->IsItem())
						{
							if (m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
							{
								//
							}

							else if (m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::SCISSORS or m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::TAPE)
							{
								//
							}
							else
							{
								return false;
							}
						}
					}
				}
				else // ���� ����� ��� ������ ��ġ���� ����
				{
					return false;
				}
			}
		}


		// ��������� �ذ� �÷��̾ ������������ ������ ���� ���¿��� �ڷ� �� �� ���� ����ó��
		else if (m_sPlayerIndex.y + catchIndex.y <= 6 and m_sPlayerIndex.y + catchIndex.y >= 0 and m_sPlayerIndex.x + catchIndex.x <= 8 and m_sPlayerIndex.x + catchIndex.x >= 0)
		{
			// �÷��̾ �ٶ󺸴� ���� �տ� �������� �ִٸ�
			if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->IsItem())
			{
				// �� �������� ���̶��
				if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
				{
					if (!((Cotton*)(m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()))->ExceptionMove(sPlayerDir, catchIndex, exceptionDir, _key, true))
					{
						return false;
					}
				}
			}
		}


		//=============================================================================== �̵� �κ�  ===============================================================================================

		if (GameManager::GetInst()->GetPlayer()->IsGrab() &&
			m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->IsItem() &&
			m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->ItemOn() &&
			!m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->CheckBlock(_key) &&
			!m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->CheckRibbon(_key)) //������ ���� üũ
		{
			// ��� �ִ� �������� �����̶�� 
			if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
			{
				// ��� �ִ� �����۰� ���� ������ ���� ���� �տ� �������� �ִٸ�
				if (catchIndex.x == (int)vPlayerDir.x and catchIndex.y == (int)vPlayerDir.y
					&& m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->IsItem())
				{
					// �� �������� �����̶�� 
					if (m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
					{
						auto vecPart = ((Doll*)(m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()))->GetPartNum();
						((Doll*)(m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()))->MergeParts(vecPart);

						m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->SetIsOn();
						m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->SetItem(nullptr);	

						if (((Doll*)(m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetItem()))->CheckComplete())
						{
							int a = 0;
							// ���� ! 
						}
					}
				}
				else
				{
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
				}

				
			}
	
			// ��� �ִ� �������� �������� ���� ����� ��� ������ ���ٸ�
			else if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::TAPE
				&& catchIndex.x == (int)vPlayerDir.x and catchIndex.y == (int)vPlayerDir.y)
			{
				// ������ ������ ������ ���� �ִٸ�
				if (m_vecMap[m_sPlayerIndex.y + sPlayerDir.y * 2][m_sPlayerIndex.x + sPlayerDir.x * 2]->GetBool_Torn())
				{	
					// �������� ���ֱ� + �ε巯�� �̵�
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
					
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->Use();
					// �ش� ������ Ÿ���� ���ش� (Use)
					//MakeTornOnOff(m_sPlayerIndex.x + catchIndex.x * 2, m_sPlayerIndex.y + catchIndex.y * 2);
					
				}
				else
				{
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
				}
			}

			// ��� �ִ� �������� �� �̶��
			else if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
			{

				// ��� �ִ� �������� ����� �� �̶��
				if (((Cotton*)m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem())->GetConnectedCotton() != nullptr)
				{
					MapIndex otherCottonIndex = { m_sPlayerIndex.y + catchIndex.y * 2, m_sPlayerIndex.x + catchIndex.x * 2 };
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveCotton(otherCottonIndex, vPlayerDir, m_sPlayerIndex);
				}
				else
				{
					m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
				}

				// �̵��� �������� �� �� ��� �̵��� ��ġ���� �� �� �� �� �� �˻��ؼ� ���� �ִٸ� �� �ذ� �Բ� ����� ������ ����� �ش�. (���� �ִ� ��ġ�� ������)
				((Cotton*)(m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()))->CheckConnect(exceptionDir, sPlayerDir);
			}
			else
			{
				m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
					
			}

			//m_vecUndo.push_back((UINT)_pos); //������ �̵�����
			//m_vecUndo.push_back((UINT)ITEM_TYPE::SCISSORS + (UINT)POS::LAST); //�������
		}

		//�����϶� ����üũ ���ֱ�
		if (_bScissors)
		{
			if (m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->CheckRibbon(_key))
			{
				m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->MoveItem(vPlayerDir);
				//m_vecUndo.push_back((UINT)_pos);
				SoundManager::GetInst()->PlaySound(SOUND::E_ITEM, CHANNEL::EFFECT);
				m_vecMap[m_sPlayerIndex.y + catchIndex.y][m_sPlayerIndex.x + catchIndex.x]->GetItem()->Use();
				//m_vecUndo.push_back((UINT)ITEM_TYPE::SCISSORS + (UINT)POS::LAST);
				//SetRibbon(m_sPlayerIndex.x + catchIndex.x, m_sPlayerIndex.y + catchIndex.y, _pos);
				//m_vecUndo.push_back((UINT)ITEM_TYPE::RIBBON + (UINT)POS::LAST);
			}
		}

		//���� �� �÷��̾� ���� ��ġ ����
		m_PrevPlayerPos.push(m_sPlayerIndex);

		if (KEY::UP == _key)
		{
			m_sPlayerIndex.y -= 1;
		}
		else if (KEY::DOWN == _key)
		{
			m_sPlayerIndex.y += 1;
		}
		else if (KEY::LEFT == _key)
		{
			m_sPlayerIndex.x -= 1;
		}
		else if (KEY::RIGHT == _key)
		{
			m_sPlayerIndex.x += 1;
		}

		_out = m_sPlayerIndex;
		return true;

	}
	return false;
}


void Map::Reset()
{
}

//�÷��̾� �̵� Undo
void Map::Undo()
{
	bool _bCtrl = false;

	if (InputManager::GetInst()->GetKeyState(KEY::LCTRL) == KEY_STATE::HOLD)
	{
		_bCtrl = true;
	}

	static float fElapsedTime = 0.f;
	float _fDuration = 0.31f;

	if (fElapsedTime < _fDuration)
	{
		// �Է��� �����ϸ鼭 �ð��� ��� �÷��ִ� �κ�
		fElapsedTime += fDT;
	}
	else
	{
		// ������ �ð��� ���� ��Ȳ�̹Ƿ� ���ϴ� Ű �Է��� �޾Ƶ� ��
		// TAP �� �޴� ��Ȳ������!
		if (InputManager::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
		{
			if (_bCtrl)
			{
				if (!m_PrevPlayerPos.empty())
				{
					MapIndex _prevPos = m_PrevPlayerPos.top();

				}
				fElapsedTime = 0.f;
			}
			_bCtrl = false;
		}
	}
}

//Item Undo
void Map::ItemUndo(POS _playerPos)
{
	if (m_vecUndo.back() >= (UINT)POS::LAST)
	{
		vector<UINT> _item; // ������ ���� �ӽ� ����
		//Item Undo
		while (m_vecUndo.back() >= (UINT)POS::LAST)
		{
			_item.push_back(m_vecUndo.back());
			m_vecUndo.pop_back();
		}


		UINT _Dir = m_vecUndo.back(); //�������� ����������� ���������� ����
		m_vecUndo.pop_back(); //�� ����

		Vec2 _dir{ -1.f,-1.f }; //�̵��ؾ��� ����
		MapIndex _itemIndex = m_sPlayerIndex; //�̵��� ������ �ε���

		//������ ����  MoveItem 
		if (_Dir == (UINT)POS::UP)
		{
			_dir = { 0.f,1.f };
			//_itemIndex = m_sPlayerIndex;
		}
		else if (_Dir == (UINT)POS::DOWN)
		{
			_dir = { 0.f,-1.f };
			//_itemIndex.x = m_sPlayerIndex.x;
			//_itemIndex.y = m_sPlayerIndex.y + 2;
		}
		else if (_Dir == (UINT)POS::LEFT)
		{
			_dir = { 1.f,0.f };
			//_itemIndex = m_sPlayerIndex;
		}

		else if (_Dir == (UINT)POS::RIGHT)
		{
			_dir = { -1.f,0.f };
			//_itemIndex.x = m_sPlayerIndex.x + 2;
			//_itemIndex.y = m_sPlayerIndex.y;
		}

		//������ ���� ���� 
		for (size_t i = 0; i <= _item.size(); i++)
		{
			//4 DOLL
			//5 SCISSORS 
			//6 RIBBON
			//7 COTTON 
			//8 TAPE 
			//9 BUTTON
			if (_item.back() == 4)
			{

			}
			else if (_item.back() == 5)
			{
				if (!m_vecMap[_itemIndex.y][_itemIndex.x]->GetItem())
					m_vecMap[_itemIndex.y][_itemIndex.x]->MoveItem(_dir);
				else
				{
					if (_playerPos == POS::LEFT)
					{
						_itemIndex.x += 2;
					}
					else if (_playerPos == POS::RIGHT)
					{
						_itemIndex.x -= 2;
					}
					else if (_playerPos == POS::UP)
					{
						_itemIndex.y -= 2;
					}
					else if (_playerPos == POS::DOWN)
					{
						_itemIndex.y += 2;
					}
					m_vecMap[_itemIndex.y][_itemIndex.x]->MoveItem(_dir);
				}
			}
			else if (_item.back() == 6)
			{
				SetRibbon(_itemIndex.x + (int)_dir.x, _itemIndex.y + (int)_dir.y, (POS)_Dir);
				m_vecMap[_itemIndex.y][_itemIndex.x]->GetItem()->SetIsOn();
				_item.pop_back();
			}
			else if (_item.back() == 7)
			{

			}
			else if (_item.back() == 8)
			{

			}
			else if (_item.back() == 9)
			{

			}
		}
	}
}

void Map::MakeTornOnOff(int _x, int _y)
{
	if (m_vecMap[_y][_x]->GetBool()) // Ȱ��ȭ�� ���̶��
	{
		if (m_vecMap[_y][_x]->GetBool_Torn()) m_vecMap[_y][_x]->SetBool_Torn(false);
		else m_vecMap[_y][_x]->SetBool_Torn(true);
	}
}

void Map::SetItem(Item* _pItem, int _x, int _y)
{
	_pItem->SetPos(IndexToVec({ _y, _x }));
	CreateObject(_pItem, GROUP_TYPE::ITEM);
	m_vecMap[_y][_x]->SetItem(_pItem);
}

bool Map::IsItem(int _x, int _y)
{
	if (_x < 0 or _x >= 9 or _y < 0 or _y >= 7) // �ε��� ����ó��
		return false;
	if (!m_vecMap[_y][_x]->GetItem())			// ������ �ִ���
		return false;
	//�� �������� �����ִ� ��������
	return m_vecMap[_y][_x]->GetItem()->ItemOn();
}

bool Map::CheckPath(int _x, int _y, KEY _key)
{
	if (_x >= 0 && _x < 9 && _y >= 0 && _y < 7)
	{
		if (m_vecMap[_y][_x]->CheckBlock(_key))
			return false;
		if (m_vecMap[_y][_x]->CheckRibbon(_key))
			return false;
		else
			return true;
	}

}



void Map::render(HDC _background)
{
	//Test
	//Rectangle(_background
	//	, (int)m_vMapPos.x
	//	, (int)m_vMapPos.y
	//	, (int)(m_vMapPos.x + m_vMapScale.x)
	//	, (int)(m_vMapPos.y + m_vMapScale.y));
}