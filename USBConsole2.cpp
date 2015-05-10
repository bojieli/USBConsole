// USBConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "USBConsole.h"
#include "mmsystem.h" //timeSetEvent必须用这两
#pragma comment ( lib, "Winmm.lib" )//
#include "stdafx.h"
#include "Windows.h"
#include "Hid.h"
extern "C" {
#include "hidsdi.h"

#include <setupapi.h>

}
static MMRESULT mr;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
LARGE_INTEGER freq;  
LARGE_INTEGER start_t , stop_t;
void InitTimer()
{
	QueryPerformanceFrequency(&freq);
	printf("The frequency of your pc is %d.\n", freq.QuadPart);
}
void StartTimer()
{
	QueryPerformanceCounter(&start_t);
}
void StopTimer(double* Time)
{
	QueryPerformanceCounter(&stop_t);
	*Time = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
}





CHid QHid;
CWinApp theApp;
using namespace std;
BYTE QSendTemp[9];

static void CALLBACK TimerCall(UINT wTimerID, UINT msg,DWORD dwUser, DWORD dwl,DWORD dw2)
{
	//答题器的发送端
	QHid.WriteToSend(QSendTemp,9);
	
}
UINT ThreadFunc(LPVOID lpParam)
{
	while(1)//基站接收端
	{
		

	}
	return 0;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{


	QHid.PIDR = 6;
	QHid.PIDS = 7;
	while(!QHid.OpenDevice())
		Sleep(1000);
	for(int i=1;i<15;i++)
	{
		printf("%f\n",239.0/i);
	}
	while(1);


	printf("找到设备！\n");
	BYTE Buf1[9];
	for (int i = 0; i < 9; i++)
	{
		Buf1[i] = 0;
		QSendTemp[i] = 0;
	}
	QHid.GetID();
	while(1);
	for(int i=0;i<10;i++)
	{
		Buf1[4] = 0xf3;
		Buf1[8] = i+1;
		QHid.WriteToReceive(Buf1,9);
		
	}
	while(1);
	Buf1[4] = 0xf2;
	Buf1[8] = 5;	QHid.WriteToReceive(Buf1,9);
	Buf1[8] = 0;	QHid.WriteToSend(Buf1,9);//答题器配置
	QHid.GetChannel();
	CWinThread* pThread;	pThread=AfxBeginThread(ThreadFunc,NULL);

	mr = timeSetEvent(200,1,(LPTIMECALLBACK)TimerCall,NULL,TIME_PERIODIC);

	while(1)//答题器的接收端
	{
		BYTE BufR[9];
		if(QHid.Read(BufR,9))
		{
			for(int i=0;i<9;i++)
				printf("%x ",BufR[i]);
			printf("\n");
		}
	}












	

	
	return 0;
}
