#include "Tool.h"
#include "Bomb.h"
#include "ShrinkPotion.h"

using namespace std;

//ToolClass ����

ToolClass::ToolClass() : status(INVALID), img(NULL)
{
	position.x = position.y = -1;
	position.height = DEFAULT_TOOL_HEIGHT;
	position.width = DEFAULT_TOOL_WIDTH;
}

ToolStatus ToolClass::getStatus()
{
	return status;
}

rect ToolClass::getPosition()
{
	return position;
}
bool ToolClass::collision(const rect & position2) //�ж����������Ƿ��ཻ
{
	if ((
		(position.x <= position2.x && position2.x <= position.x + position.width) ||
		(position2.x <= position.x && position.x <= position2.x + position2.width)
		) // ���� x ���꣬�ཻ��
		&&
		(
		(position.y <= position2.y && position2.y <= position.y + position.height) ||
		(position2.y <= position.y && position.y <= position2.y + position2.height)
	)) // ���� y ���꣬�ཻ��
	{
		return true;
	}
	return false;
}

void ToolClass::paint(GameStatusStruct * gameStatus)
{
	if (status == INBAG || status == ONBOARD)
		putImageScale(img, position.x, position.y, position.width, position.height);

	//����ڹ������У���Ҫ��ӡ��Ӧ�İ���
	if (status == INBAG)
	{
		const int textSize = 30;
		setTextBkColor(WHITE);
		setTextColor(BLACK);
		setTextSize(textSize);
		paintText(
			position.x + position.width - textSize,
			position.y + position.height - textSize,
			getVirtualKeyString()
		); //��֤�������ĸ�ڵ���ͼƬ�����½�
	}
}

bool ToolClass::appear()
{
	if (status != INVALID)
		return false;

	status = ONBOARD;

	//�ڳ�������������
	position.x = rand() % WINDOW_WIDTH - DEFAULT_TOOL_WIDTH;
	if (position.x < 0)
		position.x = 0;
	position.y = rand() % WINDOW_HEIGHT - DEFAULT_TOOL_HEIGHT;
	if (position.y < 0)
		position.y = 0;

	return true;
}

//ToolManagerClass ����

ToolManagerClass::ToolManagerClass()
{
	toolList.resize(TOOL_N);
}
ToolManagerClass::ToolManagerClass(const std::vector<ToolClass*>& _toolList)
{
	toolList = _toolList;
}
ToolManagerClass::~ToolManagerClass()
{
	for (ToolClass* tool : toolList)
		delete tool;
}

void ToolManagerClass::putToolOnBoard(int gameClock)
{
	for (int i = 0; i < TOOL_N; i++)
	{
		if (toolList[i]->getStatus() == INVALID &&
			gameClock >= toolList[i]->getNextAppearTime())
		{
			toolList[i]->appear();
		}
	}
}

void ToolManagerClass::settleTool(const rect & userPosition)
{
	for (ToolClass * tool : toolList)
	{
		if (tool->getStatus() == ONBOARD && tool->collision(userPosition))
		{
			tool->gain();
		}
	}
}

bool ToolManagerClass::use(int virtualKey, GameStatusStruct * gameStatus
)
{
	//�ݹ����
	for (int i = 0; i < TOOL_N; i++)
	{
		if (virtualKey == toolList[i]->getVirtualKey())
		{
			return toolList[i]->release(gameStatus);
		}
	}
	return false;
}

void ToolManagerClass::paint(GameStatusStruct * gameStatus)
{	
	for (ToolClass* tool : toolList)
		tool->paint(gameStatus);
}