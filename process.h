//---------------------------------------------------------------------------

#ifndef processH
#define processH
#include <vcl.h>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;
#define TEST_NUMBER 512
#define REAGENT_NUMBER 512
#define CUP_NUMBER  44
#define T0 10   //ȡ������Ӧ���ʱ�䣬����Ҫ��10s ����ɣ�����ͨѶ����
#define T1  10   // ȡ�Լ�����Ӧ�� �������� ��ϴ��
#define  T2 10    //��ȡ���
#define  T4 100 //��ϴ���б���
//---------------------------------------------------------------------------

//������Ŀ����
struct TestConfig{
	int test_id;

	int reagent1;
	int sample_type1;
	int time1;
	int reagent2;
	int sample_type2;
	int time2;
	int reagent3;  //if -1 no reagent
	int sample_type3;
	int time3;
	int reagent4;
	int sample_type4;
	int time4;
	int v1,v2,v3,v4;
	int priority;    //0 is highest

	int wavenum;//��ȡ������Ŀ
	int wl0;//������
	int wl1;//������


};



struct TestRow{
	int sample_no;
	unsigned short position;
	int sample_type;     //�������� 1���������� 0
	char pre_dilute; // Ԥϡ��
	int  dilute_info;
	int dilute_type;//�Ƿ��������ϡ��
	int dilute_reagent;
	int sample_id;
	int sample_cup_type;
	int priority; //smaller is highest  ���� 1 �Ӽ� 0
	int test_type;  // �հ�1 ���� 2���ʿ� 3  ���� 04
	//TDateTime reg_time;
	int sample_volume;
	int  test_id;
    int test_no;  //ȷ������id

};
struct Reagent_pos{

	unsigned short circle; //��Ȧ0����Ȧ0
	unsigned short pos;
};

struct Reagent_Info{
	int reagent_id;
	Reagent_pos r_pos;
	double  left_volume;

};
typedef vector<Reagent_Info>  ReagentInfoArray;

class TestArray{
public:
	TestConfig test_config_array[TEST_NUMBER];
	void push(TestConfig tc){
		test_config_array[tc.test_id]=tc;
	}
};

class ReagentArray{
public:
	ReagentInfoArray  reagent_info_array[REAGENT_NUMBER];
	void push(Reagent_Info ri){
		reagent_info_array[ri.reagent_id].push_back(ri);
	}
};

struct CupInfo{
	int cup_pos;
	char is_in_use;
	char status;
};

class CupInfoArray{
public:
	CupInfo cv[CUP_NUMBER];
	void clear(int i){
		cv[i].is_in_use=0;
		cv[i].status=0;
	}
	void clearall(){
		for(int i=0; i<CUP_NUMBER;i++)
			clear(i);
	}
	int getFreecup()
	{
		for(int i=0; i<CUP_NUMBER;i++)
			if(!cv[i].is_in_use) return i;
		// full return -1
		return -1;
    }
};


//�Ǽǵ�������Ŀ�ʿأ����� ���棬���ȷ������ݿ����棬Ȼ������ʼ����
bool comp(const TestRow &a,const TestRow &b);
class TestRowArray{
public:
	vector<TestRow> test_array;

	void rearrange(){ // ���չ������� ���Ȱ���Ŀ���ȼ���Ȼ���ղ������ȼ� ��test_type
		sort(test_array.begin(),test_array.end(),comp);
	}
	void push(TestRow tr){
		test_array.push_back(tr);
	}


};

struct Action{
	unsigned short type;// 0  ����Ʒ����Ӧ�� 1 ���Լ�����Ӧ��  2 ��ȡ���
	//0
	union{
		//0 ����Ʒ����Ӧ��
		struct {
			unsigned short sample_pos;
			unsigned short cup_pos;
			int sample_volume;
			char sample_type;
			char wash_type;
		}get_sample;
		// 1 ���Լ�����Ӧ��
		struct {
			int reagent_id;
			Reagent_pos r_pos;
			unsigned short cup_pos;
			int sample_volume;
			char sample_type;
			char wash_type;
		}get_reagent;
		//2 ��ȡ���
		struct{
			unsigned short cup_pos;
			int wavenum;
			int  wavelength0;
			int  wavelength1;
		}get_result;
		 //3 ��ϴ��Ӧ��
		struct{
			unsigned short cup_pos;
		}wash_cup;
		//4  ��ϴ���з�Ӧ��
		//5 ��λ
		//6 ��ע
		//7��Ӧ���հ�
		//8 ͨ�ż��
		//9��Ӧ��עˮ
		//10��������ϴ
		//11������
		//12 �Լ��������
		struct {
			int  startpos;
			int  endpos;
		}reagent_check;

	}params;



};

struct ActionRow{
	Action a;
	int step;
	int ptestrow;
	int start_time;
	int end_time;
	int span_to_next; //seconds
	int span_to_prev;
	operator <(const ActionRow &a){ return start_time<a.start_time;}
	int  toStream(unsigned char * dest);
};

//sorted TestRowArray -->  action sequence when start
class ActionSequence{
public:
	list<ActionRow> action_list;
	int starttime;
	int endtime;
	int from_time;
	void clearAll();
	void insertTestRow(int i);
	void insertOneRow( vector<ActionRow> & av);
	void makelist(); // ͨ������insertTestRow ���ɶ�������
	int getendtime();
	int get_next_available(int i);
	int get_available_time(vector<ActionRow> & av);//��ȡ�����ʱ��
};


void testinitial();
extern TestArray g_test_array;
extern ReagentArray g_reagent_array;
extern TestRowArray g_test_row_array;
extern ActionSequence g_action_sequence;

#endif
