// CHChessClient.cpp: 主要專案檔。

#include "stdafx.h"
#include "ChessClientForm.h"
using namespace System;
using namespace CHChessClient;

int main(array<System::String ^> ^args)
{
    Console::WriteLine(L"Hello World");
	Application::Run(gcnew ChessClientForm());
    return 0;
}
