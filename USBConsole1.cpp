// USBConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "USBConsole.h"
#include "mmsystem.h" //timeSetEvent必须用这两
#pragma comment ( lib, "Winmm.lib" )//
#include "stdafx.h"
//#include "EasyUsbProgramer.h"
#include "Windows.h"
#include "Hid.h"



/* global constants */
extern "C" {

// This file is in the Windows DDK available from Microsoft.
#include "hidsdi.h"

#include <setupapi.h>

}
static MMRESULT mr;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// The one and only application object


/*
这个CPP用于答题器和基站两个一起测试





*/









LARGE_INTEGER freq;  
LARGE_INTEGER start_t , stop_t;  
double Qtime = 0.0;
double MainTime = 0.0;




CHid QHid;
CWinApp theApp;
using namespace std;
BYTE BufTemp[9];
long CountSend = 0;
long CountReceive = 0;
long CountMainR = 0;
static void CALLBACK TimerCall(UINT wTimerID, UINT msg,DWORD dwUser, DWORD dwl,DWORD dw2)
{
	//答题器的发送端
	CountSend++;
	for(int i = 0;i<9;i++)
		BufTemp[i] = 0;
	BufTemp[0] = 0xff;
	QueryPerformanceCounter(&start_t);
	QHid.WriteToSend(BufTemp,9);
	

	
}
int flag = 0;
BYTE Buf[9];
UINT ThreadFunc(LPVOID lpParam)
{
	BYTE Buf2[9];
	while(1)//基站接收端
	{
		if(m_Hid.Read(Buf2,9))
		{
			if(BufTemp[0] == 0xff)
			{
				QueryPerformanceCounter(&stop_t);
				MainTime = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
				CountMainR++;
			//	printf("收到\n");
			}
			//Buf2[1] = 0xff;
			m_Hid.WriteToSend(Buf2,9);
			
		}

	}
	return 0;
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}
	m_Hid.PIDR = 6;
	m_Hid.PIDS = 7;
	QHid.PIDR = 8;
	QHid.PIDS = 9;
	while(!m_Hid.OpenDevice())
		Sleep(1000);
	while(!QHid.OpenDevice())
		Sleep(1000);
	printf("找到设备！\n");
	BYTE Buf1[9];
	for (int i = 0; i < 9; i++)
	{
		Buf1[i] = 0;
	}
	Buf1[4] = 0xf2;
	
	Buf1[8] = 0;	m_Hid.WriteToReceive(Buf1,9);
	Buf1[8] = 5;	m_Hid.WriteToSend(Buf1,9);//基站配置
	Buf1[8] = 5;	QHid.WriteToReceive(Buf1,9);
	Buf1[8] = 0;	QHid.WriteToSend(Buf1,9);//答题器配置
	QHid.GetChannel();
	m_Hid.GetChannel();
	CWinThread* pThread;
	pThread=AfxBeginThread(ThreadFunc,NULL);
	for(int i = 0;i<9;i++)
		Buf[i] = 0;


	//mr = timeSetEvent(2,1,(LPTIMECALLBACK)TimerCall,NULL,TIME_PERIODIC);



	QueryPerformanceFrequency(&freq);  
	 printf("The frequency of your pc is %d.\n", freq.QuadPart);  
	 BYTE BufR[9];
	 long Countd = 0;
	 long biaohao = 0;
	while(1)//答题器的接收端
	{
		if(QHid.Read(BufR,9))
		{
			if(BufR[0]==0xff)
			{
				Countd++;
				QueryPerformanceCounter(&stop_t);
				Qtime = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;
				//printf("基站：%.2f\t答题器:%.2f\t发：%d\t收：%d\t基站收：%d\t差=%d\n",MainTime,Qtime,CountSend,Countd,CountMainR,CountMainR-Countd);
			}
			else
			{
				biaohao++;
				//for(int i=0;i<10;i++)
					printf("%d::回复答题器\t",biaohao);
					for(int i=0;i<9;i++)
					{
						printf("%x ",BufR[i]);
					}
					printf("\n");
			}
			
		}
	}












	

	printf("找到设备！\n");
	//m_Hid.WriteToSend(Buf,9);
	printf("写入!\n");
	int CC = 0;
	
	static long Count = 0;
//	m_Hid.GetID();
	m_Hid.SetChannel(0);
	m_Hid.GetChannel();
	//for(int i=0;i<10;i++)
	
	//m_Hid.SendMode(1);
		//Sleep(200);
	
	//Sleep(100);
	int Mode0Count = 0;
	
	//	Sleep(200);
	//while(1)
	
	LARGE_INTEGER freq;  
    LARGE_INTEGER start_t , stop_t;  
    double exe_time; 
	double time;
    
   
    BYTE Temp = 0;
	//Sleep(10000);
	while(1)
	{  
		//printf("进入while\n");
		QueryPerformanceCounter(&start_t); 
		
		QueryPerformanceCounter(&stop_t); 
		//printf("写入！");
		Temp = Buf[0];
		//Buf[0] = 0xff;
		
		time = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;  
		//printf("Write = %f\n",time);

		//QueryPerformanceCounter(&start_t); 
		if(m_Hid.Read(Buf,9)==1)
		{
			CountReceive++;
			//QueryPerformanceCounter(&start_t);  
			QueryPerformanceCounter(&stop_t); 
			exe_time = 1e3*(stop_t.QuadPart-start_t.QuadPart)/freq.QuadPart;  
					//	printf("Your program executed time is %fms.\n", exe_time);  
			Count++;
			//printf("ToToRead!\n");
			//printf("%d::\t",Count);
			for (int i = 0; i < 9; i++)
			{
				//printf("%x ",Buf[i]);
			}
			
			//printf("\n");
			//printf("\t%f\n",exe_time);
			//printf("Write =%.2f\tRead=%.2f\tAdd=%.2f\t%d\t%d\n",time,exe_time,time+exe_time,Temp,Buf[0]);
			printf("Send= %d\tReceive= %d\t 效率=%.5f\t差=%d\n",CountSend,CountReceive,CountReceive*1.0/CountSend,CountSend-CountReceive);
			//start_t = stop_t;
		}
		//Sleep(10);
		//
		Buf[0]++;
		//printf("CC = %d\n",CC);
		//else
		//	printf("错误!\n");
		//printf("推出while\n");
	}
	return nRetCode;
}
