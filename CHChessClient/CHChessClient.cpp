// CHChessClient.cpp: �D�n�M���ɡC

#include "stdafx.h"
#include "ChessClientForm.h"
#include "LoginForm.h"
using namespace System;
using namespace CHChessClient;

[STAThread]
int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	Application::Run(gcnew LoginForm());
    return 0;
}
