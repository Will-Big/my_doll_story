#include "pch.h"
#include "Player.h"

#include "InputManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Animator.h"
#include "GameManager.h"
#include "SoundManager.h"

#include "PathManager.h"
#include "ResManager.h"
#include "Texture.h"
#include "Scene.h"

#include "Map.h"


Player::Player()
	: m_bMoving(false)
	, m_bGrab(false)
	, m_cLookAt('d')
	, m_vDir(0.f, 1.0f)
{
	m_pTex = ResManager::GetInst()->LoadTexture(L"PlayerImage", L"texture\\스테이지\\공통\\캐릭터.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_UP",			m_pTex, Vec2(0.f, 290.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"IDLE_DOWN",		m_pTex, Vec2(0.f, 0.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT",		m_pTex, Vec2(0.f, 870.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 2);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT",		m_pTex, Vec2(0.f, 580.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 2);

	GetAnimator()->CreateAnimation(L"MOVE_UP",			m_pTex, Vec2(580.f, 290.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"MOVE_DOWN",		m_pTex, Vec2(580.f, 0.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"MOVE_LEFT",		m_pTex, Vec2(580.f, 870.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"MOVE_RIGHT",		m_pTex, Vec2(580.f, 580.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);

	GetAnimator()->CreateAnimation(L"HOLD_IDLE_UP",		m_pTex, Vec2(1160.f, 290.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"HOLD_IDLE_DOWN",	m_pTex, Vec2(1160.f, 0.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"HOLD_IDLE_LEFT",	m_pTex, Vec2(1160.f, 870.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 1);
	GetAnimator()->CreateAnimation(L"HOLD_IDLE_RIGHT",	m_pTex, Vec2(1160.f, 580.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.5f, 1);

	GetAnimator()->CreateAnimation(L"HOLD_MOVE_UP",		m_pTex, Vec2(1450.f, 290.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"HOLD_MOVE_DOWN",	m_pTex, Vec2(1450.f, 0.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"HOLD_MOVE_LEFT",	m_pTex, Vec2(1450.f, 870.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);
	GetAnimator()->CreateAnimation(L"HOLD_MOVE_RIGHT",	m_pTex, Vec2(1450.f, 580.f), Vec2(290.f, 290.f), Vec2(290.f, 0.f), 0.15f, 2);

	float holdoffset = 22.f;

	GetAnimator()->SetOffset(L"IDLE_UP", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"IDLE_DOWN", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"IDLE_LEFT", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"IDLE_RIGHT", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"MOVE_UP", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"MOVE_DOWN", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"MOVE_LEFT", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"MOVE_RIGHT", Vec2(0.f, -12.f));
	GetAnimator()->SetOffset(L"HOLD_IDLE_UP", Vec2(0.f, -12.f - holdoffset));
	GetAnimator()->SetOffset(L"HOLD_IDLE_DOWN", Vec2(0.f, -12.f + holdoffset / 2));
	GetAnimator()->SetOffset(L"HOLD_IDLE_LEFT", Vec2(0.f - holdoffset, -12.f));
	GetAnimator()->SetOffset(L"HOLD_IDLE_RIGHT", Vec2(0.f + holdoffset, -12.f));
	GetAnimator()->SetOffset(L"HOLD_MOVE_UP", Vec2(0.f, -12.f - holdoffset));
	GetAnimator()->SetOffset(L"HOLD_MOVE_DOWN", Vec2(0.f, -12.f + holdoffset));
	GetAnimator()->SetOffset(L"HOLD_MOVE_LEFT", Vec2(0.f - holdoffset, -12.f));
	GetAnimator()->SetOffset(L"HOLD_MOVE_RIGHT", Vec2(0.f + holdoffset, -12.f));
}

Player::~Player()
{

}

void Player::update()
{
	float fMoveTime = 0.3f;			// 이동 시간
	Vec2 vPos = GetPos();

	GetAnimator()->update();

	// 애니메이션 스프라이트 선택
	if (!m_bMoving) { // 서 있음
		if (!m_bGrab) { // 잡고 있지 않음
			if (m_cLookAt == 'u') GetAnimator()->Play(L"IDLE_UP", true);
			else if (m_cLookAt == 'd') GetAnimator()->Play(L"IDLE_DOWN", true);
			else if (m_cLookAt == 'l') GetAnimator()->Play(L"IDLE_LEFT", true);
			else if (m_cLookAt == 'r') GetAnimator()->Play(L"IDLE_RIGHT", true);
		}
		else { // 잡음
			if (m_cLookAt == 'u') GetAnimator()->Play(L"HOLD_IDLE_UP", true);
			else if (m_cLookAt == 'd') GetAnimator()->Play(L"HOLD_IDLE_DOWN", true);
			else if (m_cLookAt == 'l') GetAnimator()->Play(L"HOLD_IDLE_LEFT", true);
			else if (m_cLookAt == 'r') GetAnimator()->Play(L"HOLD_IDLE_RIGHT", true);
		}
	}
	else { // 움직이고 있음
		if (!m_bGrab) { // 잡고 있지 않음
			if (m_cLookAt == 'u') GetAnimator()->Play(L"MOVE_UP", true);
			else if (m_cLookAt == 'd') GetAnimator()->Play(L"MOVE_DOWN", true);
			else if (m_cLookAt == 'l') GetAnimator()->Play(L"MOVE_LEFT", true);
			else if (m_cLookAt == 'r') GetAnimator()->Play(L"MOVE_RIGHT", true);
		}
		else { // 잡음
			if (m_cLookAt == 'u') GetAnimator()->Play(L"HOLD_MOVE_UP", true);
			else if (m_cLookAt == 'd') GetAnimator()->Play(L"HOLD_MOVE_DOWN", true);
			else if (m_cLookAt == 'l') GetAnimator()->Play(L"HOLD_MOVE_LEFT", true);
			else if (m_cLookAt == 'r') GetAnimator()->Play(L"HOLD_MOVE_RIGHT", true);
		}
	}

	if (m_bMoving)
	{
		MovePlayer(vPos, m_vDir * Vec2(BLOCK_SIZE, BLOCK_SIZE), fMoveTime);
		return;
	}

	// 키 입력
	if (InputManager::GetInst()->GetKeyState(KEY::SPACE) == KEY_STATE::HOLD)
	{
		MapIndex catchIndex = { -1, -1 }; // Y, X
		MapIndex playerIndex = GameManager::GetInst()->GetMap()->m_sPlayerIndex;
		KEY _key = KEY::LAST;
		switch (m_cLookAt)
		{
		case 'u':
		{
			catchIndex = { -1, 0 };
			_key = KEY::UP;
		}
		break;
		case 'd':
		{
			catchIndex = { 1, 0 };
			_key = KEY::DOWN;
		}
		break;
		case 'l':
		{
			catchIndex = { 0, -1 };
			_key = KEY::LEFT;
		}
		break;
		case 'r':
		{
			catchIndex = { 0, 1 };
			_key = KEY::RIGHT;
		}
		break;
		}

		catchIndex = { playerIndex.y + catchIndex.y, playerIndex.x + catchIndex.x };

		// 플레이어가 바라보는 방향쪽을 체크 기준이기 때문에
		// 바라보는 방향의 반대쪽으로 갈 경우 길이 있는지는 else로 체크
		if (GameManager::GetInst()->GetMap()->CheckPath(catchIndex.x, catchIndex.y, _key)
			&& GameManager::GetInst()->GetMap()->CheckPath(playerIndex.x, playerIndex.y, _key)
			&& GameManager::GetInst()->GetMap()->IsItem(catchIndex.x, catchIndex.y))
			m_bGrab = true;
		else if (GameManager::GetInst()->GetMap()->CheckPath(playerIndex.x, playerIndex.y, _key) &&
			!GameManager::GetInst()->GetMap()->CheckPath(catchIndex.x, catchIndex.y, _key) &&
			GameManager::GetInst()->GetMap()->IsItem(catchIndex.x, catchIndex.y))
			m_bGrab = true;
	}
	else
	{
		m_bGrab = false;
	}

	if (InputManager::GetInst()->GetKeyState(KEY::UP) == KEY_STATE::HOLD)
		MoveByKey(KEY::UP);
	else if (InputManager::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
		MoveByKey(KEY::RIGHT);
	else if (InputManager::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
		MoveByKey(KEY::LEFT);
	else if (InputManager::GetInst()->GetKeyState(KEY::DOWN) == KEY_STATE::HOLD)
		MoveByKey(KEY::DOWN);
}


void Player::MoveByKey(KEY _eKey)
{
	static float fMoveTime = 0.3f;

	Vec2 vPos = GetPos();

	if (_eKey == KEY::RIGHT or _eKey == KEY::LEFT)
	{
		if (m_bGrab && m_vDir.x == 0)
		{
			return;
		}
	}
	else
	{
		if (m_bGrab && m_vDir.y == 0)
		{
			return;
		}
	}
	

	m_vDir = Vec2(1.f, 0.f);
	char cLookAt = ' ';

	switch (_eKey)
	{
	case KEY::DOWN:
		m_vDir = Vec2(0.f, 1.f);
		cLookAt = 'd';
		break;
	case KEY::LEFT:
		m_vDir = Vec2(-1.f, 0.f);
		cLookAt = 'l';
		break;
	case KEY::UP:
		m_vDir = Vec2(0.f, -1.f);
		cLookAt = 'u';
		break;
	case KEY::RIGHT:
		m_vDir = Vec2(1.f, 0.f);
		cLookAt = 'r';
		break;
	}

	if (!m_bGrab)
	{
		m_cLookAt = cLookAt;
	}

	if (GameManager::GetInst()->GetMap()->Move(_eKey, m_playerIndex))
	{
		SoundManager::GetInst()->PlayWalkSound();
		MovePlayer(vPos, m_vDir * Vec2(BLOCK_SIZE, BLOCK_SIZE), fMoveTime);
	}
}

//Undo 했을때 MovePlayer
void Player::UndoMovePlayer(POS _pos)
{
	float fMoveDistance = BLOCK_SIZE;	// 이동 거리
	float fMoveTime = 0.3f;			// 이동 시간
	static float fElapsedTime = 0.f;
	float _fDuration = 0.31f;
	Vec2 vPos = GetPos();

	if (POS::UP == _pos)
	{
		m_vDir = Vec2(0.f, -1.f);
		MovePlayer(vPos, Vec2(0.0f, -fMoveDistance), fMoveTime);
		m_cLookAt = 'u';
	}
	else if (POS::DOWN == _pos)
	{
		m_vDir = Vec2(0.f, 1.f);
		MovePlayer(vPos, Vec2(0.0f, +fMoveDistance), fMoveTime);
		m_cLookAt = 'd';

	}
	else if (POS::LEFT == _pos)
	{
		m_vDir = Vec2(-1.f, 0.f);
		MovePlayer(vPos, Vec2(-fMoveDistance, 0.0f), fMoveTime);
		m_cLookAt = 'l';
	}
	else if (POS::RIGHT == _pos)
	{
		m_vDir = Vec2(1.f, 0.f);
		MovePlayer(vPos, Vec2(+fMoveDistance, 0.0f), fMoveTime);
		m_cLookAt = 'r';
	}
}

void Player::render(HDC _dc)
{
	//Rectangle(_dc, (int)(m_vPos.x - m_vScale.x / 2.f), (int)(m_vPos.y - m_vScale.y / 2.f)
	//	, (int)(m_vPos.x + m_vScale.x / 2.f), (int)(m_vPos.y + m_vScale.y / 2.f));

	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	m_pCollider->finalupdate();
	component_render(_dc);
}


void Player::MovePlayer(Vec2& _vCurrentPosition, const Vec2& _vMoveDistance, float _fDuration)
{
	static Vec2 vStartPos;

	if (!m_bMoving)
	{
		vStartPos = _vCurrentPosition;
		m_bMoving = true;
	}

	static float fElapsedTime = 0.f;

	if (fElapsedTime < _fDuration)
	{
		_vCurrentPosition = _vCurrentPosition + _vMoveDistance * (1.f / _fDuration) * fDT; // 보간 이동

		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;

		Vec2 vDest = vStartPos + _vMoveDistance;
		_vCurrentPosition = vDest;

		m_bMoving = false;
	}

	SetPos(_vCurrentPosition);
}

