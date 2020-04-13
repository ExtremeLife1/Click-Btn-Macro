//// Capture_Macro.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
////
//
//#include <iostream>
////#include <WinUser.h>
//#include <Windows.h>
//#include <random>
//
//
//int X_PRNG()
//{
//
//	std::random_device rd;
//	std::mt19937 mersenne(rd());
//
//	std::uniform_int_distribution<>die(0, GetSystemMetrics(SM_CXSCREEN));
//
//	return die(mersenne);
//}
//int Y_PRNG()
//{
//
//	std::random_device rd;
//	std::mt19937 mersenne(rd());
//
//	std::uniform_int_distribution<>die(0, GetSystemMetrics(SM_CYSCREEN));
//
//	return die(mersenne);
//}
//
//void LeftClick()
//{
//	INPUT    Input = { 0 };
//	// left down 
//	Input.type = INPUT_MOUSE;
//	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//	::SendInput(1, &Input, sizeof(INPUT));
//
//	// left up
//	::ZeroMemory(&Input, sizeof(INPUT));
//	Input.type = INPUT_MOUSE;
//	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
//	::SendInput(1, &Input, sizeof(INPUT));
//}
//
//void MoveMouse(int x, int y)
//{
//	Sleep(1);
//	UINT ninput = 1;
//	INPUT ip;
//	int cbsize = sizeof(ip);
//	ip.type = INPUT_MOUSE;
//	ip.mi.mouseData = 0;
//	ip.mi.time = 0;
//	ip.mi.dx = x * (65536 / GetSystemMetrics(SM_CXSCREEN));
//	ip.mi.dy = y * (65536 / GetSystemMetrics(SM_CYSCREEN));
//	ip.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
//	SendInput(ninput, &ip, cbsize);
//}
//
//void KeyboardDown(WORD vk)
//{
//	INPUT input;
//	WORD vkey = vk;
//	input.type = INPUT_KEYBOARD;
//	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
//	input.ki.time = 0;
//	input.ki.dwExtraInfo = 0;
//	input.ki.wVk = vkey;
//	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
//	SendInput(1, &input, sizeof(INPUT));
//
//}
//
//void KeyboardUp(INPUT input)
//{
//	input.ki.dwFlags = KEYEVENTF_KEYUP;
//	SendInput(1, &input, sizeof(INPUT));
//}
//
//void Return_Mouse_Abs_Position(POINT ptMouse)
//{
//	GetCursorPos(&ptMouse);
//}
//int main()
//{
//	double Interval;
//	int count_macro = 0;
//	POINT ptMouse;
//	std::cout << "Macro System" << std::endl;
//	std::cout << "____________________" << std::endl;
//	std::cout << "1. Test(무작위적으로 마우스 움직이기)" << std::endl;
//	std::cout << "2. Get Curser Absolute Position" << std::endl;
//	std::cout << "3. Get Keyboard Input" << std::endl;
//	std::cout << "4. Make Macro System" << std::endl;
//	std::cout << "5. Retry Macro System" << std::endl;
//	std::cout << "____________________" << std::endl;
//
//	while (true)
//	{
//		int Num;
//		scanf_s("%d", &Num);	
//		switch (Num)
//		{
//		case 1:
//			for (int i = 0; i < 1000; i++)
//				MoveMouse(X_PRNG(), Y_PRNG());
//		case 2:
//			GetCursorPos(&ptMouse);
//			//Return_Mouse_Abs_Position(ptMouse);
//			std::cout << "( " << ptMouse.x << ", " << ptMouse.y << " )" << std::endl;
//		case 3:
//			//while (true)
//			//{
//			//}
//			//CaptureAnImage(GetDesktopWindow());
//			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_EXTENDEDKEY, 0);
//			KEYBDINPUT key;
//			key.wVk = VK_SNAPSHOT;
//			key.dwFlags = 0;
//			INPUT input_key;
//				int Input;
//				Sleep(10);
//
//				//std::cout << "Keyboard Input Is " << std::endl;
//				//std::cout << Input;
//				// Input is Ctrl+Q, quit this function.
//				//if()
//				break;
//			
//		case 4:
//			std::cout << "Set Interval[millisecond] Time: " << std::endl;
//			std::cin >> Interval;
//
//
//
//			count_macro++;
//		case 5:
//			for (int i = 0; i < count_macro; i++)
//			{
//				// Set mouse Position
//
//				// Set Keyboard or Mouse Event
//				KeyboardDown(VK_LBUTTON);
//				WM_LBUTTONDBLCLK;
//
//				Sleep(Interval);
//			}
//		default:
//			exit(0);
//
//		}
//	}
//	
//
//
//
//	//KeyboardDown(VK_CONTROL);
//	return 0;
//}
