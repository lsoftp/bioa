//---------------------------------------------------------------------------


#pragma hdrstop

#include "interface.h"
#include "process.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

void initTestArray()
{

}
void initTestrowArray()
{

}
void initReagentArray()
{

}
void updateReagent(unsigned char circle, unsigned char pos, int v)
{

}
/*************************************************************
pos : test cup pos
status  step of cup
**************************************************************/

void updateCup(unsigned char pos, unsigned char status)
{

}
/*************************************************************
test_no : in database identify a test
nums,r1,r2 test result for this test_no test
**************************************************************/
void pushTestResult(int test_no, char nums,float r1,float r2)
{

}
void pushTestStatus(int test_num, int step, int status)
{

   g_test_row_array.test_array[test_num].status=status;
   int test_no= g_test_row_array.test_array[test_num].test_no;

   // to do ,update database test_no info

}
