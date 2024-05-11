#pragma once


struct ScriptImport
{
	LPTSTR name = nullptr;
	ScriptModule *mod = nullptr;
	ScriptImport *next = nullptr;
	LineNumberType line_number = 0;
	FileIndexType file_index = 0;
	bool all = true;

	ScriptImport() {}
	ScriptImport(ScriptModule *aMod) : mod(aMod) {}

	void *operator new(size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void *operator new[](size_t aBytes) {return SimpleHeap::Alloc(aBytes);}
	void operator delete(void *aPtr) {}
	void operator delete[](void *aPtr) {}
};


class ScriptModule : public ObjectBase
{
public:
	LPCTSTR mName = nullptr;
	Line *mFirstLine = nullptr;
	ScriptImport *mImports = nullptr;
	ScriptModule *mPrev = nullptr;
	VarList mVars;
	Var *mSelf = nullptr;
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

	IObject_Type_Impl("Module");
	ResultType Invoke(IObject_Invoke_PARAMS_DECL) override;
	Object *Base() override { return sPrototype; }
	static Object *sPrototype;
};

typedef ScriptItemList<ScriptModule, 16> ScriptModuleList;
