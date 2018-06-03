
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("src\fmMain.cpp", Form10);
//---------------------------------------------------------------------------
#include "process.h"
#include "clientsockt.h"
#include "handlethread.h"
#include "debugout.h"
void testinit()
{
	testinitial();
	DP1("rows %d",g_test_row_array.test_array.size());
	g_test_row_array.rearrange();
	 DP1("****************rows %d",g_test_row_array.test_array.size());
		 vector<TestRow>::iterator iter;
	for (iter=g_test_row_array.test_array.begin();iter!=g_test_row_array.test_array.end();iter++)
	{
		DP3("***%d*****%d******** %d",(*iter).test_id,(*iter).test_type,(*iter).priority);
	}
	g_action_sequence.makelist();
	DP1("size %d",g_action_sequence.action_list.size());
	list<ActionRow> &a=g_action_sequence.action_list;
	list<ActionRow>::iterator li;
	for(li=a.begin();li!=a.end();li++)
	{
		ActionRow ar= *li;
		DP3("test_id %d   s %d e %d",g_test_row_array.test_array[li->ptestrow].test_id, li->start_time,li->end_time);

	}
	CCliSocket::makeupWSA();
	g_tcp_client.init();
	g_tcp_client.Connect("127.0.0.1",40000);
	g_tcp_client.setNonBlock();
	g_handler=new HandleThread(true);
	g_handler->Resume();

}




//---------------------------------------------------------------------------
WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	testinit();
	//
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm10), &Form10);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
