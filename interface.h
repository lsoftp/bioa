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
开始测试：所有登记的测试push到testrowarray中，然后设置command=1
其他动作，构造actionlist，然后设置command=2；




******************************************************************/
#endif
