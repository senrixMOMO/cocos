#pragma once
#ifdef _DEBUG
#include <windows.h>
#include <memory>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)	//... 可変引数

#ifdef _DEBUG
#define AST() {\
	CHAR ast_mes[256];\
	wsprintf(ast_mes, "%s %d行目\0", __FILE__, __LINE__);\
	MessageBox(0, ast_mes, "ｱｻｰﾄ表示", MB_OK);\
	}
#else
#define AST()
#endif

class _DebugConOut
{
public:
	static _DebugConOut &GetInstance()
	{
		return *s_Instance;
	}

private:
	struct _DebugConOutDeleter 
	{
		void operator()(_DebugConOut* _debug) const
		{
			delete _debug;
		}
	};

	_DebugConOut();
	~_DebugConOut();
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> s_Instance;

	FILE* _debugFp = nullptr;

};

#else
#define  TRACE(fmt, ...)
#define  AST()

#endif	//_DEBUG