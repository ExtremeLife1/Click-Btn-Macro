#include <windows.h>
#include <iostream>
#include <vector>
#include "Timer.h"
#include <fstream>
#include <string>

/*
 *	Mouse clicking console application.
 *	Instructions:
 *	1: Set how long you would like the app to run for.
 *	2: Move the mouse to the location you would like it to click at and press control to save that point.
 *	   You can add as many points as you want and this app will alternate through them.
 *	   Push 'c' to stop saving the points and begin the demo.
 *     *** If you don't want to save any points and want control of the mouse yourself - then don't save
 *	       any points and just push 'c' to continue past that screen. ***
 *	3: After the 5 second countdown the application will start clicking at the locations you gave it. Or
 *	   if you set no locations will click at the current location your mouse is at.
 *     *** Push esc during this stage if you wish to stop or exit the program ***
 *
 *  #: ******* REMOVE OR EDIT THE COMMENTS AT LINE 120 TO 126 *******
 */

 // Function Declarations
void  LeftClick();														// Left clicks the mouse if called.
POINT GetMousePosition();												// Returns the mouses current position.
void  SetMousePosition(float, float);										// Sets the mouses position.
void Numbering(int);
void KeyboardDown(WORD vk);
void Read(std::vector<float>* x, std::vector<float>* y);

int main()
{
	// Get the current console window.
	HWND myWindow;
	AllocConsole();
	myWindow = FindWindowA("ConsoleWindowClass", NULL);

	// Variables
	float seconds = 0.0f;										// Timer for how long the app runs.
	int   clicks = 0;										// Number of clicks in the amount of time the app runs.
	float waitTime = 0.0f;										// User input of how long the app runs.
	int Number_of_Times = 0;
	bool  running = true;										// Value to keep our app running.
	bool  getMousePositions = true;										// Value if true lets us make a list of mouse positions.
	int   vectorPosition = 0;										// Value to keep track of our position in the mousePoints vector.
	int   vectorSize = 0;										// Size of the mousePoints vector.
	bool  hasPoints = false;									// Default false if we have no mouse points created.
	int count = 1;
	char ch;

	std::vector<int> do_function;
	std::vector<float> mousePoints_x;										// Vector container for our mouse points.
	std::vector<float> mousePoints_y;										// Vector container for our mouse points.

	std::cout << "=== READ ME ===" << std::endl;
	std::cout << "*** Warning - Make sure you don't have the mouse over something important! ***" << std::endl;
	std::cout << "*** This window will close after a 5 second countdown and start clicking!! ***" << std::endl;
	std::cout << "*** After the wait time you enterd the window will open itself again.      ***" << std::endl;
	std::cout << "*** If you want to read Macro log before you made, press 'w'				 ***" << std::endl;

	std::cin >> ch;
	if (ch == 'w')
		Read(&mousePoints_x, &mousePoints_y);

	std::cout << "\n\nHow many times do you want the mouse to click for? \n\n >> ";


	std::cin >> Number_of_Times;
	std::cout << std::endl;

	do
	{
		std::cout << "Press ctrl to add the current mouse position to the list or 'C' to continue" << std::endl;
		POINT mouse = GetMousePosition();
		std::cout << "Mouse X : " << mouse.x << "                " << std::endl;
		std::cout << "Mouse Y : " << mouse.y << "                " << std::endl;
		std::cout << "\nPoints saved in list : " << mousePoints_x.size() << std::endl;

		// If ctrl is pushed add the mouses location the the mousePoints vector.
		if (GetAsyncKeyState(VK_CONTROL))
		{
			hasPoints = true;
			mousePoints_x.push_back(mouse.x);
			mousePoints_y.push_back(mouse.y);
			std::cout << "Added Point (" << mouse.x << ", " << mouse.y << ")" << std::endl;
			Sleep(250);
		}

		if (GetAsyncKeyState(VK_SHIFT))
		{
			int Baek = 0, SShip = 0, Ileh = 0;
		// Shift 키를 누르게 되면 함수 실행 횟수를 결정한다.
			hasPoints = true;
			do_function.push_back(mousePoints_x.size());


			// count++;
			Sleep(250);
		}
		// If 'c' is pushed start the clicking after the 5 second count down.
		if (GetAsyncKeyState('C'))
		{
			getMousePositions = false;
		}

		COORD pos = { 0, 10 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		
	} while (getMousePositions);

	// Create a timer class.
	Timer t;
	t.InitGameTime();
	t.GetDeltaTime();
	// Set DT to 5 for now to start the 5 second count down.
	float DT = 5.0f;

	do
	{
		DT -= t.GetDeltaTime();
		COORD pos = { 0,15 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		std::cout << "Clicks will start in : " << DT << std::endl;

	} while (DT > 0.0f);

	// Reset DT.
	DT = 0.0f;
	// Hide the console window.
	ShowWindow(myWindow, 0);
	// Set the number of elements in our vector to its size minus one.
	vectorSize = (mousePoints_x.size() - 1);
	
	do
	{
		DT += t.GetDeltaTime();

		// If we have any points in the mousePoints vector. Alternate through them
		// and set the mouses location to the current point we are looking at in mousePoints.
		if (hasPoints)
		{
			SetMousePosition(mousePoints_x[vectorPosition], mousePoints_y[vectorPosition]);
			for (int i = 0; i < do_function.size(); i++)
			{
				if (vectorPosition == do_function[i])
				{
					Numbering(count); count++;
				}
			}

			vectorPosition++;
			if (vectorPosition > vectorSize)
			{
				vectorPosition = 0;
			}
		}
		// Remove the comment from the line below to enable the clicking.
		LeftClick();

		// Somes of the games i've tested this on need a small pause to register all the clicks.
		// Enable this if you have that problem. And/or click the object you want to constantly click first before
		// the 5 second timer runs out.
		Sleep(1000);

		clicks++;
		if (DT > 1.0f)
		{
			seconds += DT;
			DT = 0.0f;
		}
		// If escape is presses quit the program.
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			running = false;
		}

	} //while (seconds < waitTime && running);
	while (clicks < Number_of_Times && running);
	std::cout << "Finished - Mouse Was Clicked : " << clicks << " times in " << seconds << " seconds" << std::endl;
	ShowWindow(myWindow, 1);
}

//
// Desc    : Clicks the left mouse button down and releases it.
// Returns : Nothing.
//
void LeftClick()
{
	INPUT    Input = { 0 };													// Create our input.

	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.

	ZeroMemory(&Input, sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type = INPUT_MOUSE;									// Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.
}

//
// Desc    : Gets the cursors current position on the screen.
// Returns : The mouses current on screen position.
// Info    : Used a static POINT, as sometimes it would return trash values
//
POINT GetMousePosition()
{
	static POINT m;
	POINT mouse;
	GetCursorPos(&mouse);
	m.x = mouse.x;
	m.y = mouse.y;
	return m;
}

//
// Desc    : Sets the cursors position to the point you enter (POINT& mp).
// Returns : Nothing.
//
void SetMousePosition(float mp_x, float mp_y)
{
	long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx = mp_x * (65535.0f / fScreenWidth);
	float fy = mp_y * (65535.0f / fScreenHeight);

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;

	SendInput(1, &Input, sizeof(INPUT));
}


void Numbering(int count)
{
	int Count = count;
	int Baek = 0, SShip = 0, Ileh = 0;
	if (Count >= 100)
	{
		Baek = Count / 100; Count = Count % 100;
	}
	if (Count >= 10)
	{
		SShip = Count / 10; Count = Count % 10;
	}
	if (Count >= 1)
	{
		Ileh = Count;
	}
	// 0: 48 ~ 9: 57
	KeyboardDown(48 + Baek);
	KeyboardDown(48 + SShip);
	KeyboardDown(48 + Ileh);
}

void Save(std::vector<float> x, std::vector<float> y) // Save Macro System.
{
	std::string OutputFilepath = "mouselog.txt";
	std::ofstream writeFile(OutputFilepath.data());
	if (writeFile.is_open())
	{
		for (int i = 0; i < x.size(); i++)
			writeFile << x[i];
		for (int i = 0; i < y.size(); i++)
			writeFile << y[i];
	}
	writeFile.close();
}

void Read(std::vector<float> *x, std::vector<float> *y)
{
	std::string filePath = "mouselog.txt";
	std::vector<float> tmp;
	int mouselog_size;
		// read File
	std::ifstream openFile(filePath.data());
	if (openFile.is_open()) {
		std::string line;
		while (std::getline(openFile, line)) {
			tmp.push_back(stof(line));
		}
		openFile.close();
	}
	mouselog_size = tmp.size();
	//mouselog_size = mouselog_size / 2;
	for (int i = 0; i < mouselog_size; i++)
	{
		if(i < mouselog_size/2)
			x->push_back(tmp[i]);
		if (i >= mouselog_size / 2)
			y->push_back(tmp[i]);
	}
}

void KeyboardDown(WORD vk)
{
	INPUT input;
	WORD vkey = vk;
	input.type = INPUT_KEYBOARD;
	input.ki.wScan = MapVirtualKey(vkey, MAPVK_VK_TO_VSC);
	input.ki.time = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wVk = vkey;
	input.ki.dwFlags = 0; // there is no KEYEVENTF_KEYDOWN
	SendInput(1, &input, sizeof(INPUT));

}

// Source: http://www.cplusplus.com/forum/lounge/17053/