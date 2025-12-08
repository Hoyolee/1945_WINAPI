#pragma once
#include "CScene.h"
#include "CBombUI.h"
#include "CLifeUI.h"
#include "CBoss.h"
#include "CMap.h"
#include "CEnemyBullet.h"

class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	void Offset();

private:
};

