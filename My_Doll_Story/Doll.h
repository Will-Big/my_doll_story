#pragma once
#include "Item.h"




/*
    3 x N(최대 파트수) 의 텍스쳐 사이즈
*/


class Texture;

class Doll :
    public Item
{
private:
    static int          m_iStartID;     // 할당할 ID 값 (스테이지 입장시 0으로 초기화해야함)
    int                 m_iUniqID;      // 할당된 ID 값

    Texture*            m_pTex;         // 인형 텍스처

    int                 m_iXSize;       // 텍스처의 한칸 X 크기
    int                 m_iYSize;       // 텍스처의 한칸 Y 크기

    vector<int>         m_vMerged;      // 파트 합체 여부

    int                 m_iMaxPart;     // 인형 파트 수
    SCENE_TYPE          m_SceneType;
    
    

public:
    void update() override;
    void render(HDC _dc) override;

public:
    void SetTexture(Texture* _pTex, int _iMaxPart);
    const vector<int>& GetPartNum() { return m_vMerged; }              // 합침 당할 인형
    void MergeParts(vector<int>& _vecPart);                     // 합치는 인형
    bool CheckComplete() { return m_vMerged.size() == m_iMaxPart; }
    
public:
    Doll(SCENE_TYPE _eType);
    Doll(const Doll& _doll);
    ~Doll();
};

