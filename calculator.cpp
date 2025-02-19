#include <windows.h>
#include<string>

// HWND textbox;
// char textsaved[20];

 HWND input,plus=0,minus,divide,multiple,num1,num2;
 float pluss,minuss,multiplee,dividee,numo=0,numb=0;
 char numsaved1[20],numsaved2[20];


/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {

	switch(Message) {
		case WM_CREATE:
			 input = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE|WS_CHILD,35,20,170,25,hwnd,NULL,NULL,NULL);
			 plus = CreateWindow("BUTTON","+",WS_VISIBLE|WS_CHILD,40,117,25,25,hwnd,(HMENU) 1,NULL,NULL);
			 minus = CreateWindow("BUTTON","-",WS_VISIBLE|WS_CHILD,80,117,25,25,hwnd,(HMENU) 2,NULL,NULL);
			 multiple = CreateWindow("BUTTON","*",WS_VISIBLE|WS_CHILD,120,117,25,25,hwnd,(HMENU) 3,NULL,NULL);
			 divide = CreateWindow("BUTTON","/",WS_VISIBLE|WS_CHILD,160,117,25,25,hwnd,(HMENU) 4,NULL,NULL);
			 num1 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,35,58,170,20,hwnd,NULL,NULL,NULL);
			 num2 = CreateWindow("EDIT","",WS_BORDER|WS_CHILD|WS_VISIBLE,35,88,170,20,hwnd,NULL,NULL,NULL);
            break;
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		case WM_COMMAND:{
			switch(LOWORD(wParam)){
				case 1:{
				numo = (GetWindowText(num1,&numsaved1[0],20));
				numb = (GetWindowText(num2,&numsaved2[0],20));
				float firstnum = std::stof(numsaved1);
				float secondnum = std::stof(numsaved2);
				pluss = firstnum + secondnum;
				char str[20];
				sprintf(str,"%f",pluss);
				::MessageBox(hwnd,str,"Result",MB_OK);
				break;
				}
				case 2:{
					numo = (GetWindowText(num1,&numsaved1[0],20));
					numb = (GetWindowText(num2,&numsaved2[0],20));
					float firstnum = std::stof(numsaved1);
					float secondnum = std::stof(numsaved2);
					pluss = firstnum - secondnum;
					char str[20];
					sprintf(str,"%f",pluss);
					::MessageBox(hwnd,str,"Result",MB_OK);
					break;
				}
				case 3:{
					numo = (GetWindowText(num1,&numsaved1[0],20));
					numb = (GetWindowText(num2,&numsaved2[0],20));
					float firstnum = std::stof(numsaved1);
					float secondnum = std::stof(numsaved2);
					pluss = firstnum * secondnum;
					char str[20];
					sprintf(str,"%f",pluss);
					::MessageBox(hwnd,str,"Result",MB_OK);
					break;
				}
				case 4:{
					numo = (GetWindowText(num1,&numsaved1[0],20));
					numb = (GetWindowText(num2,&numsaved2[0],20));
					float firstnum = std::stof(numsaved1);
					float secondnum = std::stof(numsaved2);
					pluss = firstnum / secondnum;
					char str[20];
					sprintf(str,"%f",pluss);
					::MessageBox(hwnd,str,"Result",MB_OK);
					break;
				}
			}
			break;
		}
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(130,253,7));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */	
		HWND_DESKTOP,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}

