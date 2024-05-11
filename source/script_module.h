#pragma once


struct ScriptImport
{
	LPTSTR name = nullptr;
	ScriptModule *mod = nullptr;
	ScriptImport *next = nullptr;
	LineNumberType line_number = 0;
	FileIndexType file_index = 0;

	ScriptImport() {}
	ScriptImport(ScriptModule *aMod) : mod(aMod) {}
};


class ScriptModule
{
public:
	LPCTSTR mName = nullptr;
	Line *mFirstLine = nullptr;
	ScriptImport *mImports = nullptr;
	ScriptModule *mPrev = nullptr;
	VarList mVars;
	bool mExecuted = false;

	ScriptModule() {}
	ScriptModule(LPCTSTR aName, ScriptImport &aDefaultImport)
	{
		mName = SimpleHeap::Alloc(aName);
		mImports = &aDefaultImport;
	}

	void *operator new(size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void *operator new[](size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void operator delete(void *aPtr) {}
	void operator delete[](void *aPtr) {}
};

typedef ScriptItemList<ScriptModule, 16> ScriptModuleList;
