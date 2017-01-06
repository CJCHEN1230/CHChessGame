#pragma once

namespace CHChessServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Text;
	using namespace System::Collections::Generic;

	
	public ref class Game
	{
	public: 		
		array<Chessman^,2>^ AllChess=gcnew array<Chessman^, 2>(9, 10); //整個棋盤狀況
			
	private:
		String Winner;


	};
	
	public ref class Player
	{
	private:		
		String^ Name;
		Socket^ socket;
		bool State; //可不可以移動棋子
	public:
		String^ GetName()  { return Name; }
		void SetName(String^ Name2) { Name = Name2; }

		Socket^ GetSocket() { return socket; }
		void SetSocket(Socket^ socket2) { socket = socket2; }
	};


	public ref class Chessman abstract
	{
	
	protected:
		String ^ Name;
		unsigned short x;
		unsigned short y;
		bool color;
	public:	
		virtual bool Move(int x,int y)=0;
		/*String^ GetName()  { return Name; }
		void SetName(String^ Name2) { Name = Name2; }*/
		unsigned short GetX() { return x; }
		void SetX(unsigned short X) { this->x = X; }

		unsigned short GetY() { return y; }
		void SetX(unsigned short Y) { this->y = Y; }

		bool GetState() { return color; }
		void SetState(bool COLOR) { this->color = COLOR; }


		Chessman(unsigned short x,unsigned short y,bool color) {
			this->x = x;
			this->y = y;
			this->color = color;
		}

		Chessman(array<Byte>^ data) {
			this->x = BitConverter::ToUInt16(data, 0);
			this->y = BitConverter::ToUInt16(data, 2);
			this->color = BitConverter::ToBoolean(data, 4);
		}

		array<Byte>^ ToByteArray()
		{
			List<Byte>^ byteList = gcnew List<Byte>();
			byteList->AddRange(BitConverter::GetBytes(this->x));
			byteList->AddRange(BitConverter::GetBytes(this->y));
			byteList->AddRange(BitConverter::GetBytes(this->color));
			//byteList->AddRange(Encoding::ASCII::GetBytes(Name));
			return byteList->ToArray;
		}

		/*enum class Chessman : int {
			King,
			Advisors,
			Elephants,
			Rooks,
			Knights,
			Cannons,
			soldiers
		};*/
		/*virtual property double Base
		{
			double get() { return bs; }
			void set(double b)
			{
				if (b <= 0)
					bs = 0.00;
				else
					bs = b;
			}
		}
		virtual String ^ Description();
		virtual double Perimeter() = 0;
		virtual double Area() = 0;
		virtual void   Display() = 0;
		CQuadrilateral();*/
	};

	//將軍
	public ref class Chessman_King :public Chessman
	{		
	public:
		Chessman_King(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "King"; }
		virtual bool Move(unsigned short desX,unsigned short desY) {
			if (desX < 3 || desX>5 || desY > 2) { //檢查範圍
				if ((desX == this->x) && Math::Abs(desY - this->y) == 1) {//檢查位置
					return true;
				}
				else if ((desY == this->y) && Math::Abs(desX - this->x) == 1) {
					return true;
				}
				else {
					return false;
				}
			}
			else
				return false;
		}
	};

	//士
	public ref class Chessman_Advisors :public Chessman
	{
	public:
		Chessman_Advisors(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Advisors"; }
		virtual bool Move(unsigned short desX, unsigned short desY) {
			if (desX < 3 || desX>5 || desY > 2) { //檢查範圍
				if ((desX == this->x) && Math::Abs(desY - this->y) == 1) {//檢查位置
					return true;
				}
				else if ((desY == this->y) && Math::Abs(desX - this->x) == 1) {
					return true;
				}
				else {
					return false;
				}
			}
			else
				return false;
		}
	};
	/*enum class Chessman : int {
	King,
	Advisors,
	Elephants,
	Rooks,
	Knights,
	Cannons,
	soldiers
	};*/

}