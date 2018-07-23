//**************************************************************************/
// Copyright (c) 1998-2007 Autodesk, Inc.
// All rights reserved.
// 
// These coded instructions, statements, and computer programs contain
// unpublished proprietary information written by Autodesk, Inc., and are
// protected by Federal copyright law. They may not be disclosed to third
// parties or copied or duplicated in any form, in whole or in part, without
// the prior written consent of Autodesk, Inc.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: Denis Grigor
//***************************************************************************/

#include "testBench.h"

#define testBench_CLASS_ID	Class_ID(0x4084be6a, 0x5644bdd3)



// Fuction exposure part

#include <maxscript\maxscript.h>
#include <maxscript\maxwrapper\objectsets.h>
#include <maxscript\maxwrapper\maxclasses.h>
#include <maxscript\macros\define_instantiation_functions.h>
#include <string>


//some helper defines
#define printIt(x) ExecuteMAXScriptScript((std::wstring(L"print\"") + x + std::wstring(L"\"")).c_str())
#define stringer(x) std::to_wstring(x)



bool exampleFunc(INode* test_node);

def_visible_primitive(exampleFunc, "exampleFunc");
Value* exampleFunc_cf(Value** arg_list, int argument_count)
{
	//Check if we received just one argument
	check_arg_count(exampleFunc, 1, argument_count);

	//Check if the type of the argument is the one expected
	//type_check(arg_list[0], ObjectSet, _M("[The TestFunction should receive a selection as input]."));
	type_check(arg_list[0], MAXNode, _M("[The 'exampleFunc' should receive a Node as input]."));

	//Pass the argument to the "to be tested function"
	INode* test_subject = arg_list[0]->to_node();

	if (exampleFunc(test_subject))
	{
		return &true_value;
	}

	return &false_value;
}

bool exampleFunc(INode* test_node)
{
	TimeValue now = GetCOREInterface()->GetTime();
	Object* obj = test_node->EvalWorldState(now).obj;
	TriObject *tri = static_cast<TriObject*>(obj->ConvertToType(now, Class_ID(TRIOBJ_CLASS_ID, 0)));
	if (!tri)
	{
		printIt(L"This cannot be cast to triMesh");
		return false;
	}
	Mesh some_mesh = tri->GetMesh();
	int vtx_number = some_mesh.numVerts;

	printIt(L"This node has a mesh with " + stringer(vtx_number) + L" vertices");

	return true;
}


// End of fuction exposure part


class testBench : public GUP
{
public:
	//Constructor/Destructor
	testBench();
	virtual ~testBench();

	// GUP Methods
	virtual DWORD     Start();
	virtual void      Stop();
	virtual DWORD_PTR Control(DWORD parameter);
	virtual void      DeleteThis();

	// Loading/Saving
	virtual IOResult Save(ISave* isave);
	virtual IOResult Load(ILoad* iload);
};



class testBenchClassDesc : public ClassDesc2 
{
public:
	virtual int IsPublic() 							{ return TRUE; }
	virtual void* Create(BOOL /*loading = FALSE*/) 		{ return new testBench(); }
	virtual const TCHAR *	ClassName() 			{ return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID SuperClassID() 				{ return GUP_CLASS_ID; }
	virtual Class_ID ClassID() 						{ return testBench_CLASS_ID; }
	virtual const TCHAR* Category() 				{ return GetString(IDS_CATEGORY); }

	virtual const TCHAR* InternalName() 			{ return _T("testBench"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() 					{ return hInstance; }					// returns owning module handle
	

};


ClassDesc2* GettestBenchDesc() { 
	static testBenchClassDesc testBenchDesc;
	return &testBenchDesc; 
}




testBench::testBench()
{

}

testBench::~testBench()
{

}

void testBench::DeleteThis()
{
	delete this;
}

// Activate and Stay Resident
DWORD testBench::Start()
{
	printIt(L"The testBench is up and ready");
	return GUPRESULT_KEEP;
}

void testBench::Stop()
{
	#pragma message(TODO("Do plugin un-initialization here"))
}

DWORD_PTR testBench::Control( DWORD /*parameter*/ )
{
	return 0;
}

IOResult testBench::Save(ISave* /*isave*/)
{
	return IO_OK;
}

IOResult testBench::Load(ILoad* /*iload*/)
{
	return IO_OK;
}

