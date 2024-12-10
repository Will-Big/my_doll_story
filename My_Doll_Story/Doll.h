#pragma once
#include "Item.h"




/*
    3 x N(�ִ� ��Ʈ��) �� �ؽ��� ������
*/


class Texture;

class Doll :
    public Item
{
private:
    static int          m_iStartID;     // �Ҵ��� ID �� (�������� ����� 0���� �ʱ�ȭ�ؾ���)
    int                 m_iUniqID;      // �Ҵ�� ID ��

    Texture*            m_pTex;         // ���� �ؽ�ó

    int                 m_iXSize;       // �ؽ�ó�� ��ĭ X ũ��
    int                 m_iYSize;       // �ؽ�ó�� ��ĭ Y ũ��

    vector<int>         m_vMerged;      // ��Ʈ ��ü ����

    int                 m_iMaxPart;     // ���� ��Ʈ ��
    SCENE_TYPE          m_SceneType;
    
    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void SetTexture(Texture* _pTex, int _iMaxPart);
    const vector<int>& GetPartNum() { return m_vMerged; }              // ��ħ ���� ����
    void MergeParts(vector<int>& _vecPart);                     // ��ġ�� ����
    bool CheckComplete() { return m_vMerged.size() == m_iMaxPart; }
    
public:
    Doll(SCENE_TYPE _eType);
    Doll(const Doll& _doll);
    ~Doll();
};

