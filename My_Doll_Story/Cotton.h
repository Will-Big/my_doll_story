#pragma once
#include "Item.h"


/*
    다른 솜과 붙는 기능(+붙었는지 확인 하는 기능)
    붙은 솜과 함께 움직이는 기능
    잡힌 솜과 붙은 솜이 동시에 움직일 수 있는지 확인하는 기능
    
    ! 붙어있는 솜을 움직일때 솜 포인터가 사라지는 버그
*/



class Cotton :
    public Item
{
public:
    Cotton*     m_bConnectedCotton;
    Texture*    m_pTexture;
    MapIndex   m_cCottonIndex;

public:
    void Use() override;
    void update() override;
    void render(HDC _dc) override;

public:
    void CheckConnect(int _exceptDir, MapIndex _sPlayerDir);                                                                  // 솜이 움직였을때 이동이 완료된 위치에서 상하좌우 를 체크해서 솜이 있는지 체크하는 함수야 (이동하기 전 위치는 제외)
    void ExceptionConnect(MapIndex _sPlayerDir, MapIndex _keyIndex);                                        // 반복적인 스위치문 줄여주기
    bool ExceptionMove(MapIndex _playerDir, MapIndex _catchIndex, int _exceptionDir, KEY _key, bool _isBack);        // 솜의 움직임 예외처리
    bool ExceptionSideCotton(MapIndex _leftCheck, MapIndex _rightCheck); // 플레이어 기준 솜의 좌 우측 예외처리

public:
    void SetIndex(MapIndex _NewCottonIndex) { m_cCottonIndex.y = _NewCottonIndex.y; m_cCottonIndex.x = _NewCottonIndex.x; }   // 솜이 움직였을때 맵상 인덱스를 최신화 시켜주기
    MapIndex GetIndex() {return m_cCottonIndex; }                                                                             // 솜의 맵상 인덱스 반환
    
    void ConnectCotton(Cotton* _cotton) { m_bConnectedCotton = _cotton; }
    Cotton* GetConnectedCotton() { return m_bConnectedCotton; }

public:
    Cotton();
    Cotton(int _x, int _y);
    ~Cotton();
};

