#pragma once
#include "Item.h"


/*
    �ٸ� �ذ� �ٴ� ���(+�پ����� Ȯ�� �ϴ� ���)
    ���� �ذ� �Բ� �����̴� ���
    ���� �ذ� ���� ���� ���ÿ� ������ �� �ִ��� Ȯ���ϴ� ���
    
    ! �پ��ִ� ���� �����϶� �� �����Ͱ� ������� ����
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
    void CheckConnect(int _exceptDir, MapIndex _sPlayerDir);                                                                  // ���� ���������� �̵��� �Ϸ�� ��ġ���� �����¿� �� üũ�ؼ� ���� �ִ��� üũ�ϴ� �Լ��� (�̵��ϱ� �� ��ġ�� ����)
    void ExceptionConnect(MapIndex _sPlayerDir, MapIndex _keyIndex);                                        // �ݺ����� ����ġ�� �ٿ��ֱ�
    bool ExceptionMove(MapIndex _playerDir, MapIndex _catchIndex, int _exceptionDir, KEY _key, bool _isBack);        // ���� ������ ����ó��
    bool ExceptionSideCotton(MapIndex _leftCheck, MapIndex _rightCheck); // �÷��̾� ���� ���� �� ���� ����ó��

public:
    void SetIndex(MapIndex _NewCottonIndex) { m_cCottonIndex.y = _NewCottonIndex.y; m_cCottonIndex.x = _NewCottonIndex.x; }   // ���� ���������� �ʻ� �ε����� �ֽ�ȭ �����ֱ�
    MapIndex GetIndex() {return m_cCottonIndex; }                                                                             // ���� �ʻ� �ε��� ��ȯ
    
    void ConnectCotton(Cotton* _cotton) { m_bConnectedCotton = _cotton; }
    Cotton* GetConnectedCotton() { return m_bConnectedCotton; }

public:
    Cotton();
    Cotton(int _x, int _y);
    ~Cotton();
};

