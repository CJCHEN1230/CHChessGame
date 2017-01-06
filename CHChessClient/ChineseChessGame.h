#pragma once

namespace CHChessClient {

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

	public ref class Chessman abstract
	{

	protected:
		String ^ Name;
		unsigned short x;
		unsigned short y;
		bool color;
	public:
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) = 0;

		unsigned short GetX() { return x; }
		void SetX(unsigned short X) { this->x = X; }

		/*unsigned short GetY() { return y; }
		void SetY(unsigned short Y) { this->y = Y; }*/

		void SetXY(unsigned short X, unsigned short Y) { 
			this->x = X; 
			this->y = Y;
		};

		bool GetColor() { return color; }
		void SetColor(bool COLOR) { this->color = COLOR; }


		Chessman(unsigned short x, unsigned short y, bool color) {
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

			return byteList->ToArray();
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
	//將
	public ref class Chessman_King :public Chessman
	{
	public:
		Chessman_King(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "King"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override{

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 1, this->y));
			TempList->Add(Point(this->x - 1, this->y));
			TempList->Add(Point(this->x, this->y + 1));
			TempList->Add(Point(this->x, this->y - 1));

			
			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X>2 && EachPoint->X<6 && EachPoint->Y<3 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr||ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						CoordinateList->Add(*EachPoint);
					}
				}
			}
			
			return CoordinateList;
		}
	};
	//士
	public ref class Chessman_Advisors :public Chessman
	{
	public:
		Chessman_Advisors(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Advisors"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override{

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 1, this->y + 1));
			TempList->Add(Point(this->x - 1, this->y - 1));
			TempList->Add(Point(this->x + 1, this->y - 1));
			TempList->Add(Point(this->x - 1, this->y + 1));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X>2 && EachPoint->X<6 && EachPoint->Y<3 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						CoordinateList->Add(*EachPoint);
					}
				}
			}
			
			return CoordinateList;
		}
	};
	//象
	public ref class Chessman_Elephants :public Chessman
	{
	public:
		Chessman_Elephants(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Elephants"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 2, this->y + 2));
			TempList->Add(Point(this->x - 2, this->y - 2));
			TempList->Add(Point(this->x + 2, this->y - 2));
			TempList->Add(Point(this->x - 2, this->y + 2));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X>-1 && EachPoint->X<9 && EachPoint->Y<5 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						if (ChessboardState[(EachPoint->X + this->x) / 2, (EachPoint->Y + this->y) / 2] == nullptr)//檢查拐象腳
							CoordinateList->Add(*EachPoint);
					}
				}
			}
			
			return CoordinateList;
		}

		
	};
	//馬
	public ref class Chessman_Knights :public Chessman
	{
	public:
		Chessman_Knights(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Knights"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 2, this->y - 1));
			TempList->Add(Point(this->x + 2, this->y + 1));
			TempList->Add(Point(this->x - 2, this->y - 1));
			TempList->Add(Point(this->x - 2, this->y + 1));
			TempList->Add(Point(this->x + 1, this->y + 2));
			TempList->Add(Point(this->x - 1, this->y + 2));
			TempList->Add(Point(this->x + 1, this->y - 2));
			TempList->Add(Point(this->x - 1, this->y - 2));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X>-1 && EachPoint->X<9 && EachPoint->Y<10 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置


					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						if (Math::Abs(EachPoint->X - this->x) == 2) {//檢查拐馬腳
							if (ChessboardState[(EachPoint->X + this->x) / 2, this->y] == nullptr) {
								CoordinateList->Add(*EachPoint);
							}
						}
						else {
							if (ChessboardState[this->x,(EachPoint->Y + this->y) / 2 ] == nullptr) {
								CoordinateList->Add(*EachPoint);
							}
						}
					}
				}
			}
			
			return CoordinateList;
		}
	};
	//車
	public ref class Chessman_Rooks :public Chessman
	{
	public:
		Chessman_Rooks(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Rooks"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			for (int i = this->x + 1; i < 9; i++) {
				if (ChessboardState[i, this->y] == nullptr) {
					CoordinateList->Add(Point(i, this->y));
				}
				else if (ChessboardState[i, this->y]->GetColor() != this->GetColor())
				{
					CoordinateList->Add(Point(i, this->y));
					break;
				}
				else
					break;
			}

			for (int i = this->x - 1; i > -1; i--) {
				if (ChessboardState[i, this->y] == nullptr) {
					CoordinateList->Add(Point(i, this->y));
				}
				else if (ChessboardState[i, this->y]->GetColor() != this->GetColor())
				{
					CoordinateList->Add(Point(i, this->y));
					break;
				}
				else
					break;
			}

			for (int j = this->y + 1; j < 10; j++) {
				if (ChessboardState[this->x, j] == nullptr) {
					CoordinateList->Add(Point(this->x, j));
				}
				else if (ChessboardState[this->x, j]->GetColor() != this->GetColor())
				{
					CoordinateList->Add(Point(this->x, j));
					break;
				}
				else
					break;
			}

			for (int j = this->y - 1; j > -1; j--) {
				if (ChessboardState[this->x, j] == nullptr) {
					CoordinateList->Add(Point(this->x, j));
				}
				else if (ChessboardState[this->x, j]->GetColor() != this->GetColor())
				{
					CoordinateList->Add(Point(this->x, j));
					break;
				}
				else
					break;
			}
			

			return CoordinateList;
		}
	};
	//炮
	public ref class Chessman_Cannons :public Chessman
	{
	public:
		Chessman_Cannons(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "Cannons"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			for (int i = this->x + 1; i < 9; i++) {
				if (ChessboardState[i, this->y] == nullptr) {
					CoordinateList->Add(Point(i, this->y));
				}
				else {
					for (i = i + 1; i < 9; i++) {
						if (ChessboardState[i, this->y] == nullptr)
							continue;
						else if (ChessboardState[i, this->y]->GetColor() != this->GetColor()) {
							CoordinateList->Add(Point(i, this->y));
							i = 9;
							break;
						}
					}
					break;
				}				
			}

			for (int i = this->x - 1; i > -1; i--) {
				if (ChessboardState[i, this->y] == nullptr) {
					CoordinateList->Add(Point(i, this->y));
				}
				else 
				{
					for (i = i - 1; i > -1; i--) {
						if (ChessboardState[i, this->y] == nullptr)
							continue;
						else if(ChessboardState[i, this->y]->GetColor() != this->GetColor()) {														
							CoordinateList->Add(Point(i, this->y));
							i = -1;
							break;
						}
					}
					break;
				}				
			}

			for (int j = this->y + 1; j < 10; j++) {
				if (ChessboardState[this->x, j] == nullptr) {
					CoordinateList->Add(Point(this->x, j));
				}
				else {
					for (j = j + 1; j <10; j++) {
						if (ChessboardState[this->x, j] == nullptr)
							continue;
						else if (ChessboardState[this->x, j]->GetColor() != this->GetColor()) {
							CoordinateList->Add(Point(this->x, j));
							j = 10;
							break;
						}
					}
					break;
				
				}
			}

			for (int j = this->y - 1; j > -1; j--) {
				if (ChessboardState[this->x, j] == nullptr) {
					CoordinateList->Add(Point(this->x, j));
				}
				else {
					for (j = j - 1; j > -1; j--) {
						if (ChessboardState[this->x, j] == nullptr)
							continue;
						else if (ChessboardState[this->x, j]->GetColor() != this->GetColor()) {
							CoordinateList->Add(Point(this->x, j));
							j = -1;
							break;
						}
					}
					break;

				}
			}


			return CoordinateList;
		}
	};
	//卒兵
	public ref class Chessman_Soldiers :public Chessman
	{
	public:
		Chessman_Soldiers(unsigned short X, unsigned short Y, bool COLOR) :Chessman(X, Y, COLOR) { Name = "soldiers"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();

			List<Point>^ TempList = gcnew List<Point>();

			if (this->y >= 5) {
				TempList->Add(Point(this->x + 1, this->y));
				TempList->Add(Point(this->x - 1, this->y));
				TempList->Add(Point(this->x, this->y + 1));				
			}
			else
				TempList->Add(Point(this->x, this->y + 1));

			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X>-1 && EachPoint->X<9 && EachPoint->Y<10 && EachPoint->Y>2) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						CoordinateList->Add(*EachPoint);
					}
				}
			}

			return CoordinateList;
		}
	};

	public enum class PlayerState : int { Player1, Player2, Watching};

	public enum class ChessCharacter : int { BKing, BAdvisors, BElephants, BRooks, BKnights, BCannons, Bsoldiers, GKing, GAdvisors, GElephants, GRooks, GKnights, GCannons, Gsoldiers };

	public ref class Player
	{
	private:
		String^ Name;
		Socket^ socket;
		PlayerState State;
		bool ISMoving;
	public:
		Player(String^ name2, Socket^ socket2, PlayerState playerstate, bool CanMoving):Name(name2), socket(socket2), State(playerstate), ISMoving(CanMoving){}

		PlayerState GetPlayerState() { return State; }
		void SetPlayerState(PlayerState State2) { State = State2; }

		bool GetISMoving() { return ISMoving; }
		void SetISMoving(bool ISMoving2) { ISMoving = ISMoving2; }

		String^ GetName() { return Name; }
		void SetName(String^ Name2) { Name = Name2; }

		Socket^ GetSocket() { return socket; }
		void SetSocket(Socket^ socket2) { socket = socket2; }
	};

	public ref class Game
	{
	


	private:
		//String Winner;
		/*Player player1;
		Player player2;*/
	
	public:
		array<Chessman^, 2>^ ChessboardState ; //整個棋盤狀況

		Game() {
			ChessboardState = gcnew array<Chessman^, 2>(9, 10); //整個棋盤狀況
			ChessboardState[3, 0] = gcnew Chessman_Advisors(3, 0, true);
			ChessboardState[5, 0] = gcnew Chessman_Advisors(5, 0, true);/**/
			ChessboardState[4, 0] = gcnew Chessman_King(4, 0, true);
			ChessboardState[8, 5] = gcnew Chessman_Advisors(8, 5, true);
			ChessboardState[2, 0] = gcnew Chessman_Elephants(2, 0, true);
			ChessboardState[1, 0] = gcnew Chessman_Knights(1, 0, true);
			ChessboardState[0, 0] = gcnew Chessman_Rooks(0, 0, true);
			ChessboardState[1, 2] = gcnew Chessman_Cannons(1, 2, true);
			ChessboardState[0, 3] = gcnew Chessman_Soldiers(0, 3, true);
			ChessboardState[2, 3] = gcnew Chessman_Soldiers(2, 3, true);
			ChessboardState[4, 3] = gcnew Chessman_Soldiers(4, 3, true);
			ChessboardState[6, 3] = gcnew Chessman_Soldiers(6, 3, true);

			ChessboardState[3, 4] = gcnew Chessman_Rooks(3, 4, false);

			ChessboardState[5, 4] = gcnew Chessman_Knights(5, 4, false);
		}


	};

	


	

	//將軍

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