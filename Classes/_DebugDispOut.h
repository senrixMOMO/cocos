#pragma once
#ifdef _DEBUG
#include <windows.h>
#include <memory>
#include <chrono>

#define _dbgSetUp(A) _DebugDispOut::GetInstance().SetUp(A)
#define _dbgSetAlpha(A) _DebugDispOut::GetInstance().SetAlpha(A)
#define _dbgStartDeb() _DebugDispOut::GetInstance().StartDeb()
#define _dbgAddDeb() _DebugDispOut::GetInstance().AddDeb()
#define _dbgWaitMode() _DebugDispOut::GetInstance().WaitMode()

#define _dbgDrawBox(fmt, ...) _DebugDispOut::GetInstance().DrawBox(fmt, __VA_ARGS__)	
#define _dbgDrawCircle(fmt, ...) _DebugDispOut::GetInstance().DrawCircle(fmt, __VA_ARGS__)	
#define _dbgDrawLine(fmt, ...) _DebugDispOut::GetInstance().DrawLine(fmt, __VA_ARGS__)	
#define _dbgDrawPixel(fmt, ...) _DebugDispOut::GetInstance().DrawPixel(fmt, __VA_ARGS__)	
#define _dbgDrawGraph(fmt, ...) _DebugDispOut::GetInstance().DrawGraph(fmt, __VA_ARGS__)	
#define _dbgDrawString(fmt, ...) _DebugDispOut::GetInstance().DrawString(fmt, __VA_ARGS__)	
#define _dbgDrawFormatString(fmt, ...) _DebugDispOut::GetInstance().SetScreen(); \
										DxLib::DrawFormatString(fmt, __VA_ARGS__);\
										 _DebugDispOut::GetInstance().RevScreen()

using chrono_clock = std::chrono::system_clock;
using TimePoint = chrono_clock::time_point;
class _DebugDispOut
{
public:
	static _DebugDispOut &GetInstance()
	{
		return *s_Instance;
	}
	int DrawBox(int x1, int y1, int x2, int y2, unsigned int color, bool Fill_Flag);
	int DrawCircle(int x, int y, int r, unsigned int color, int Fill_Flag);
	int DrawLine(int x1, int y1, int x2, int y2, unsigned int color);
	int DrawPixel(int x, int y, unsigned int color);
	int DrawGraph(int x, int y, int GrHandle, int TransFlag);

	int DrawString(int x, int y, const char *string, unsigned int color);
	int DrawFormatString(int x, int y, unsigned int color,const char *FormatString, ...);

	bool SetUp(int alpha);
	bool SetAlpha(int alpha);
	bool StartDeb();
	bool AddDeb();
	bool SetScreen();
	bool RevScreen();

	void WaitMode();
private:
	struct _DebugDispOutDeleter
	{
		void operator()(_DebugDispOut* _debug) const
		{
			delete _debug;
		}
	};

	_DebugDispOut();
	~_DebugDispOut();
	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeleter> s_Instance;

	FILE* _debugFp = nullptr;
	int _debugScreen;
	int _debugStringScreen;
	int _alpha;
	TimePoint startTime;
	TimePoint endTime;
	double waitTime;
	bool DrawFlag;
};

#else
#define _dbgSetUp(A) 
#define _dbgSetAlpha(A)
#define _dbgStartDeb()
#define _dbgAddDeb() 
#define _dbgDrawBox(fmt, ...)
#define _dbgDrawCircle(fmt, ...)
#define _dbgDrawLine(fmt, ...)
#define _dbgDrawPixel(fmt, ...)
#define _dbgDrawGraph(fmt, ...)
#define _dbgDrawString(fmt, ...)
#define _dbgDrawFormatString(fmt, ...)


#endif	//_DEBUG

//waitmode
//start = now
//do {end =} while(mil)(end - st).count < waitTime if(process break;)while
