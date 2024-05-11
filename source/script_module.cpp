#include "stdafx.h"
#include "script.h"


ResultType Script::ParseModuleDirective(LPCTSTR aName)
{
	if (g->CurrentFunc || mClassObjectCount)
		return CONDITION_FALSE;
	int at;
	if (mModules.Find(aName, &at))
		return ScriptError(ERR_DUPLICATE_DECLARATION, aName);
	// TODO: Validate module names.
	auto mod = new ScriptModule(aName, mDefaultImport);
	if (!mModules.Insert(mod, at))
		return FAIL;
	CloseCurrentModule();
	mCurrentModule = mod;
	return CONDITION_TRUE;
}


ResultType Script::ParseImportStatement(LPTSTR aBuf)
{
	aBuf = omit_leading_whitespace(aBuf);
	// This is fairly rigid because only a subset of the intended syntax is implemented:
	if (_tcsnicmp(aBuf, _T("* from "), 7) || !Var::ValidateName(aBuf += 7, DISPLAY_NO_ERROR))
		return ScriptError(_T("Invalid import"), aBuf);
	auto imp = SimpleHeap::Alloc<ScriptImport>();
	imp->name = SimpleHeap::Alloc(aBuf);
	imp->mod = nullptr;
	imp->line_number = mCombinedLineNumber;
	imp->file_index = mCurrFileIndex;
	imp->next = mCurrentModule->mImports;
	mCurrentModule->mImports = imp;
	return OK;
}


Var *Script::FindImportedVar(LPCTSTR aVarName)
{
	for (auto imp = mCurrentModule->mImports; imp; imp = imp->next)
	{
		// TODO: Use exports, not all vars
		auto var = imp->mod->mVars.Find(aVarName);
		if (var && var->IsDeclared())
			return var;
	}
	return nullptr;
}


ResultType Script::ResolveImports()
{
	for (auto mod = mLastModule; mod; mod = mod->mPrev)
	{
		for (auto imp = mod->mImports; imp; imp = imp->next)
		{
			if (!imp->mod && !(imp->mod = mModules.Find(imp->name)))
			{
				mCurrLine = nullptr;
				mCombinedLineNumber = imp->line_number;
				mCurrFileIndex = imp->file_index;
				return ScriptError(_T("Module not found"), imp->name);
			}
		}
	}
	return OK;
}


ResultType Script::CloseCurrentModule()
{
	// Terminate each module with RETURN so that all labels have a target and
	// all control flow statements that need it have a non-null mRelatedLine.
	if (!AddLine(ACT_EXIT))
		return FAIL;

	mCurrentModule->mPrev = mLastModule;
	mLastModule = mCurrentModule;

	ASSERT(!mCurrentModule->mFirstLine || mCurrentModule->mFirstLine == mFirstLine);
	mCurrentModule->mFirstLine = mFirstLine;
	mFirstLine = nullptr; // Start a new linked list of lines.
	mLastLine = nullptr;
	return OK;
}
