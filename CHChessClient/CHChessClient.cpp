// CHChessClient.cpp: 主要專案檔。

#include "stdafx.h"
#include "ChessClientForm.h"
#include "LoginForm.h"
using namespace System;
using namespace CHChessClient;

[STAThread]
int main(array<System::String ^> ^args)
{

	/*Player^ thisplayer2 = gcnew Player();
	Player^ enemy2 = gcnew Player(); 
	
	
	array<Byte>^ buffer2 = gcnew array<Byte>(1027);
    Console::WriteLine(L"Hello World");
	Application::Run(gcnew ChessClientForm(thisplayer2, enemy2,nullptr, buffer2));*/

	Console::WriteLine(L"Hello World");
	Application::Run(gcnew LoginForm()); 
    return 0;
}
