// CHChessServer.cpp: �D�n�M���ɡC

#include "stdafx.h"
#include "ChessServerForm.h"
using namespace System;
using namespace CHChessServer;

[STAThread]
int main(array<System::String ^> ^args)
{
    //Console::WriteLine(L"Hello World");
	Application::Run(gcnew ChessServerForm());
    return 0;
}
