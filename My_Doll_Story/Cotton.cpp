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

	// 스프라이트 적용
	m_pTexture = ResManager::GetInst()->LoadTexture(L"CottonImage", L"texture\\스테이지\\공통\\솜.bmp");
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

	// 이미 연결되어있는 상태면 체크 할 필요 x
	if (m_bConnectedCotton != nullptr)
	{
		return;
	}


	if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)
	{
		MapIndex keyIndex = {};


		switch (_exceptDir)
		{
		case 0: // 플레이어 진행 방향 : up
			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 정면

			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 좌측

			keyIndex = { 0, 1 };
			ExceptionConnect( _sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 우측

			break;
		case 1: // 플레이어 진행 방향 : down
			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 정면

			keyIndex = { 0, 1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 좌측

			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 우측

			break;
		case 2: // 플레이어 진행 방향 : left
			keyIndex = { 0, -1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 정면

			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 좌측

			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 우측

			break;
		case 3: // 플레이어 진행 방향 : right
			keyIndex = { 0, 1 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 정면

			keyIndex = { -1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 좌측

			keyIndex = { 1, 0 };
			ExceptionConnect(_sPlayerDir, keyIndex); // 플레이어 진행 방향 기준 우측

			break;
		}
	}
}

void Cotton::ExceptionConnect(MapIndex _sPlayerDir, MapIndex _keyIndex)
{
	// 9 * 7 맵을 벗어난 곳 예외처리
	if (m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y > 6 or m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y < 0
		or m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x > 8 or m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x < 0)
	{
		return;
	}
	// 플레이어 진행 방향 기준으로 _keyIndex 방향에 아이템이 있는지
	if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->IsItem())
	{
		// 그 아이템이 솜 이라면
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
			
			// 1번 솜과 2번 솜 서로 Connect
			((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()))->ConnectCotton(((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem())));
			((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _sPlayerDir.y + _keyIndex.y][m_cCottonIndex.x + _sPlayerDir.x + _keyIndex.x]->GetItem()))->ConnectCotton(((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem())));

			SoundManager::GetInst()->PlaySound(SOUND::E_ITEM, CHANNEL::EFFECT);

			// 잘 연결 됐는지 검사용 코드
			Cotton* cotton = ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y][m_cCottonIndex.x]->GetItem()))->GetConnectedCotton();
			int a = 0;
		}
	}
}

bool Cotton::ExceptionMove(MapIndex _playerDir, MapIndex _catchIndex, int _exceptionDir, KEY _key, bool _isBack)
{
	if (m_bConnectedCotton != nullptr) // 잡고 있는 솜이 연결된 상태라면
	{
		MapIndex connectIndex = m_bConnectedCotton->GetIndex();

		if(m_cCottonIndex.y + _catchIndex.y == connectIndex.y && m_cCottonIndex.x + _catchIndex.x == connectIndex.x) // 잡고 있는 연결된 상태인 솜 앞에 아이템이 솜이라면
		{

			// 플레이어가 연결된 2개의 솜이 벽 한칸 떨어져 있는 상황에서 밀었을때 일어나는 버그 방지 코드
			if (_isBack)
			{
				int a = 0;
			}

			// 9 * 7 맵을 벗어난 곳 예외처리
			else if (m_cCottonIndex.y + _catchIndex.y * 2 > 6 or m_cCottonIndex.y + _catchIndex.y * 2 < 0
				or m_cCottonIndex.x + _catchIndex.x * 2 > 8 or m_cCottonIndex.x + _catchIndex.x * 2 < 0)
			{
				
				return false;
			}

			// 잡고 있는 연결된 상태인 솜 앞에 솜 앞에 아이템이 있다면
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y * 2][m_cCottonIndex.x + _catchIndex.x * 2]->IsItem()))
			{
				return false;
			}	
			// 잡고 있는 연결된 상태인 솜 앞에 솜 앞에 벽이 있다면
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckBlock(_key))) 
			{
				return false;
			}
			// 잡고 있는 연결된 상태인 솜 앞에 솜 앞에 리본이 있다면
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckRibbon(_key)))
			{
				return false;
			}
			// 잡고 있는 연결된 상태인 솜 앞에 솜 앞에 함정이 있다면
			else if ((GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y * 2][m_cCottonIndex.x + _catchIndex.x * 2]->GetBool_Torn()))
			{
				return false;
			}

		}

		// 솜 연결 상태 (가로, 세로) 를 판단하여 이동 차단 
		else // 잡고 있는 연결된 상태인 솜의 좌측이나 우측에 솜이 있다.  
		{
			MapIndex leftCheck = {};
			MapIndex rightCheck = {};
			switch (_exceptionDir)
			{
			case 0: // 플레이어 진행 방향 : up
				leftCheck = { 0, -1 };
				rightCheck = { 0, 1 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 1: // 플레이어 진행 방향 : down
				leftCheck = { 0, 1 };
				rightCheck = { 0, -1 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 2: // 플레이어 진행 방향 : left
				leftCheck = { 1, 0 };
				rightCheck = { -1, 0 };
				if (!ExceptionSideCotton(leftCheck, rightCheck))
				{
					return false;
				}

				break;
			case 3: // 플레이어 진행 방향 : right
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

	// 잡고 있는 솜이 연결된 솜이 아니라면
	else
	{
		// 9 * 7 맵을 벗어난 곳 예외처리
		if (m_cCottonIndex.y + _playerDir.y > 6 or m_cCottonIndex.y + _playerDir.y< 0
			or m_cCottonIndex.x + _playerDir.x>8  or m_cCottonIndex.x + _playerDir.x < 0)
		{
			return false;
		}

		// 9 * 7 맵을 벗어난 곳 예외처리
		else if (m_cCottonIndex.y + _catchIndex.y > 6 or m_cCottonIndex.y + _catchIndex.y < 0
			or m_cCottonIndex.x + _catchIndex.x>8 or m_cCottonIndex.x + _catchIndex.x < 0)
		{
			int a = 0;
		}

		// 잡고 있는 솜 앞에 아이템이 있다면
		else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->IsItem())
		{
			// 잡고 있는 솜 앞에 리본이 있다면
			if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->CheckRibbon(_key))
			{
				// 앞에 리본이 있는 방향으로 움직인다면
				if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _playerDir.y][m_cCottonIndex.x + _playerDir.x]->CheckRibbon(_key))
				{
					return false;
				}
			}
			// 잡고 있는 솜 앞에 가위가 있다면
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::SCISSORS)
			{
				// 앞에 가위가 있는 방향으로 움직인다면
				if (m_cCottonIndex.y + _catchIndex.y == m_cCottonIndex.y + _playerDir.y && m_cCottonIndex.x + _playerDir.x == m_cCottonIndex.x + _catchIndex.x)
				{
					return false;
				}
			}
			// 잡고 있는 솜 앞에 테이프가 있다면
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::TAPE)
			{
				// 앞에 테이프가 있는 방향으로 움직인다면
				if (m_cCottonIndex.y + _catchIndex.y == m_cCottonIndex.y + _playerDir.y && m_cCottonIndex.x + _playerDir.x == m_cCottonIndex.x + _catchIndex.x)
				{
					return false;
				}
			}
			// 잡고 있는 솜 앞에 인형이 있다면
			else if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _catchIndex.y][m_cCottonIndex.x + _catchIndex.x]->GetItem()->GetItemType() == ITEM_TYPE::DOLL)
			{
				// 앞에 테이프가 있는 방향으로 움직인다면
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
	// 9 * 7 맵 내부에서만 사이드 좌측 검색 
	if (m_cCottonIndex.y + _leftCheck.y <= 6 and m_cCottonIndex.y + _leftCheck.y >= 0 and m_cCottonIndex.x + _leftCheck.x <= 8 and m_cCottonIndex.x + _leftCheck.x >= 0)
	{
		if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _leftCheck.y][m_cCottonIndex.x + _leftCheck.x]->IsItem()) // 잡고 있는 연결된 솜 좌측에 아이템이 있다면
		{
			if ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _leftCheck.y][m_cCottonIndex.x + _leftCheck.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)) // 그 아이템이 솜이라면
			{
				return false;
			}
		}

		// 뒤로가기 
	}
	
	// 9 * 7 맵 내부에서만 사이드 우측 검색 
	if (m_cCottonIndex.y + _rightCheck.y <= 6 and m_cCottonIndex.y + _rightCheck.y >= 0 and m_cCottonIndex.x + _rightCheck.x <= 8 and m_cCottonIndex.x + _rightCheck.x >= 0)
	{
		if (GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _rightCheck.y][m_cCottonIndex.x + _rightCheck.x]->IsItem()) // 잡고 있는 연결된 솜 우측에 아이템이 있다면
		{
			if ((Cotton*)(GameManager::GetInst()->GetMap()->m_vecMap[m_cCottonIndex.y + _rightCheck.y][m_cCottonIndex.x + _rightCheck.x]->GetItem()->GetItemType() == ITEM_TYPE::COTTON)) // 그 아이템이 솜이라면
			{
				return false;
			}
		}
	}
	

	return true;
}
