//---------------------------------------------------------------------------

#ifndef interfaceH
#define interfaceH
//---------------------------------------------------------------------------
class Interface{
public:
	static void initTestArray();
	static void initTestrowArray();
	static void initReagentArray();
	static void updateReagent(unsigned char circle, unsigned char pos, int v);
	static void updateCup(unsigned char pos, unsigned char status);
	static void pushTestResult(int test_no, char nums,float r1,float r2);
};

/**************************************************************
��ʼ���ԣ����еǼǵĲ���push��testrowarray�У�Ȼ������command=1
��������������actionlist��Ȼ������command=2��




******************************************************************/
#endif
