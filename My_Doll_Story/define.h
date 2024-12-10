#pragma once


#define DT TimeManager::GetInst()->GetDT()
#define fDT TimeManager::GetInst()->GetfDT()

#define BLOCK_SIZE 110.0f

#define DEV_MODE

enum class SCENE_TYPE
{
	MAIN,
	TITLE,
	MENU,
	START,
	CREATOR,
	HELP,
	SELECT_STAGE,
	SELECT_STAGE2,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	STAGE_06,
	STAGE_07,
	STAGE_08,
	UI_TEST,

	END,
};

enum class GROUP_TYPE
{
	DEFAULT,
	BACK,
	BLOCK,
	WALL,
	ITEM,
	PLAYER,
	UI,

	END = 10,
};

enum class ITEM_TYPE
{
	DOLL,
	SCISSORS,
	RIBBON,
	COTTON,
	TAPE,
	BUTTON,
	DEFAULT,
};

enum class KEY_STATE
{
	NONE,
	TAP,
	HOLD,
	AWAY,
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	LCTRL,
	Z,
	F1,
	F2,
	F3,
	F4,
	LAST,
};

enum class POS
{
	UP,
	LEFT,
	DOWN,
	RIGHT,
	LAST,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	T,
	YELLOW,
	END,
};

enum class PEN_TYPE
{
	GREEN,
	RED,
	WHITE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,


	END,
};