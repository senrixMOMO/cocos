#ifdef _DEBUG
#include <windows.h>
#include "_DebugDispOut.h"

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut());

_DebugDispOut::_DebugDispOut()
{
	_debugScreen = -1;
	_alpha = 0;
	DrawFlag = true;
}


_DebugDispOut::~_DebugDispOut()
{
	FreeConsole();
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2, unsigned int color, bool Fill_Flag)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawBox(
		x1 + lpSceneMng.gameScreenPos.x,
		y1 + lpSceneMng.gameScreenPos.y,
		x2 + lpSceneMng.gameScreenPos.x,
		y2 + lpSceneMng.gameScreenPos.y, color, Fill_Flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawCircle(int x, int y, int r, unsigned int color, int Fill_Flag)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawCircle(
		x + lpSceneMng.gameScreenPos.x,
		y + lpSceneMng.gameScreenPos.y,
		r, color, Fill_Flag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawLine(int x1, int y1, int x2, int y2, unsigned int color)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawLine(
		x1 + lpSceneMng.gameScreenPos.x,
		y1 + lpSceneMng.gameScreenPos.y,
		x2 + lpSceneMng.gameScreenPos.x,
		y2 + lpSceneMng.gameScreenPos.y, color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawPixel(int x, int y, unsigned int color)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawPixel(
		x + lpSceneMng.gameScreenPos.x,
		y + lpSceneMng.gameScreenPos.y,color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawGraph(
		x + lpSceneMng.gameScreenPos.x,
		y + lpSceneMng.gameScreenPos.y, GrHandle, TransFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawString(int x, int y, const char *string, unsigned int color)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawString(x ,y, string, color);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

int _DebugDispOut::DrawFormatString(int x, int y, unsigned int color,const char * FormatString, ...)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	int rtnFlag = DxLib::DrawFormatString(x, y, color, FormatString);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
	return rtnFlag;
}

bool _DebugDispOut::SetUp(int alpha)
{
	if (_debugScreen == -1)
	{
		_debugScreen = MakeScreen(lpSceneMng.screenSize.x, lpSceneMng.screenSize.y, true);
	}
	_alpha = alpha;
	return true;
}

bool _DebugDispOut::SetAlpha(int alpha)
{
	_alpha = alpha;
	return true;
}

bool _DebugDispOut::StartDeb()
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	ClsDrawScreen();
	SetDrawScreen(ghBefor);
	return true;
}

bool _DebugDispOut::AddDeb()
{
	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		DrawFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_PGDN))
	{
		DrawFlag = false;
	}
	if (DrawFlag)
	{
		lpSceneMng.addDrawQue({ _debugScreen,0, 0});
	}
	WaitMode();
	return true;
}

bool _DebugDispOut::SetScreen()
{
	_debugStringScreen = GetDrawScreen();
	SetDrawScreen(_debugScreen);
	return true;
}

bool _DebugDispOut::RevScreen()
{
	SetDrawScreen(_debugStringScreen);
	return true;
}

void _DebugDispOut::WaitMode()
{
	if (CheckHitKey(KEY_INPUT_MULTIPLY))
	{
		if (CheckHitKey(KEY_INPUT_ADD))
		{
			waitTime += 100;
		}
		else
		{
			waitTime++;
		}
	}
	if (CheckHitKey(KEY_INPUT_NUMPADENTER))
	{
		if (CheckHitKey(KEY_INPUT_SUBTRACT))
		{
			waitTime -= 100;
		}
		else
		{
			waitTime--;
		}
		if (waitTime < 0.0)
		{
			waitTime = 0.0;
		}
	}
	if (CheckHitKey(KEY_INPUT_DIVIDE))
	{
		waitTime = 0.0;
	}
	

	if (waitTime)
	{
		startTime = chrono_clock::now();
		do {
			endTime = chrono_clock::now();
			if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				break;
			}
		} while (std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() < waitTime);
	}
}

#endif	//_DEBUG