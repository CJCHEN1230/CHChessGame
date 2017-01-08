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



	public enum class ChessColor : bool { Blue = true, Green = false };

	public ref class Chessman abstract
	{

	protected:
		String ^ Name;
		unsigned short x;
		unsigned short y;
		ChessColor color;
	public:
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) = 0;

		/*unsigned short GetX() { return x; }
		void SetX(unsigned short X) { this->x = X; }*/

		/*unsigned short GetY() { return y; }
		void SetY(unsigned short Y) { this->y = Y; }*/

		String ^ GetName() { return Name; }
		void SetName(String^ Name2) { this->Name = Name2; }

		void SetXY(unsigned short X, unsigned short Y) {
			this->x = X;
			this->y = Y;
		};

		ChessColor GetColor() { return color; }
		void SetColor(ChessColor COLOR) { this->color = COLOR; }


		Chessman(unsigned short x, unsigned short y, ChessColor color) {
			this->x = x;
			this->y = y;
			this->color = color;
		}

		Chessman(array<Byte>^ data) {
			this->x = BitConverter::ToUInt16(data, 0);
			this->y = BitConverter::ToUInt16(data, 2);
			this->color = (ChessColor)BitConverter::ToBoolean(data, 4);
		}

		array<Byte>^ ToByteArray()
		{
			List<Byte>^ byteList = gcnew List<Byte>();
			byteList->AddRange(BitConverter::GetBytes(this->x));
			byteList->AddRange(BitConverter::GetBytes(this->y));
			byteList->AddRange(BitConverter::GetBytes((bool)this->color));
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

	};
	//將
	public ref class Chessman_King :public Chessman
	{
	public:
		Chessman_King(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "King"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 1, this->y));
			TempList->Add(Point(this->x - 1, this->y));
			TempList->Add(Point(this->x, this->y + 1));
			TempList->Add(Point(this->x, this->y - 1));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X > 2 && EachPoint->X < 6 && EachPoint->Y<3 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || (ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor())) {
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
		Chessman_Advisors(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "Advisors"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 1, this->y + 1));
			TempList->Add(Point(this->x - 1, this->y - 1));
			TempList->Add(Point(this->x + 1, this->y - 1));
			TempList->Add(Point(this->x - 1, this->y + 1));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X > 2 && EachPoint->X < 6 && EachPoint->Y<3 && EachPoint->Y>-1) {
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
		Chessman_Elephants(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "Elephants"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			List<Point>^ TempList = gcnew List<Point>();

			TempList->Add(Point(this->x + 2, this->y + 2));
			TempList->Add(Point(this->x - 2, this->y - 2));
			TempList->Add(Point(this->x + 2, this->y - 2));
			TempList->Add(Point(this->x - 2, this->y + 2));


			for each(Point^ EachPoint in TempList) {
				//篩選候選位置的範圍
				if (EachPoint->X > -1 && EachPoint->X < 9 && EachPoint->Y<5 && EachPoint->Y>-1) {
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
		Chessman_Knights(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "Knights"; }
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
				if (EachPoint->X > -1 && EachPoint->X < 9 && EachPoint->Y<10 && EachPoint->Y>-1) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置


					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor()) {
						if (Math::Abs(EachPoint->X - this->x) == 2) {//檢查拐馬腳
							if (ChessboardState[(EachPoint->X + this->x) / 2, this->y] == nullptr) {
								CoordinateList->Add(*EachPoint);
							}
						}
						else {
							if (ChessboardState[this->x, (EachPoint->Y + this->y) / 2] == nullptr) {
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
		Chessman_Rooks(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "Rooks"; }
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
		Chessman_Cannons(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "Cannons"; }
		virtual List<Point>^ GetMoveList(array<Chessman^, 2>^ ChessboardState) override {

			List<Point>^ CoordinateList = gcnew List<Point>();
			

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
						else if (ChessboardState[i, this->y]->GetColor() != this->GetColor()) {
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
					for (j = j + 1; j < 10; j++) {
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
		Chessman_Soldiers(unsigned short X, unsigned short Y, ChessColor COLOR) :Chessman(X, Y, COLOR) { Name = "soldiers"; }
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
				if (EachPoint->X > -1 && EachPoint->X < 9 && EachPoint->Y < 10 && EachPoint->Y>2) {
					//檢查候選位置有沒有空，如果沒有空則判斷顏色必須要不同才能放置
					if (ChessboardState[EachPoint->X, EachPoint->Y] == nullptr || (ChessboardState[EachPoint->X, EachPoint->Y]->GetColor() != this->GetColor())) {
						CoordinateList->Add(*EachPoint);
					}
				}
			}

			return CoordinateList;
		}
	};

	public enum class PlayerState : int { Player1, Player2, Watching };

	public enum class ChessCharacter : int { BKing, BAdvisors, BElephants, BRooks, BKnights, BCannons, Bsoldiers, GKing, GAdvisors, GElephants, GRooks, GKnights, GCannons, Gsoldiers };

	public ref class Player
	{
	private:
		String^ Name;
		Socket^ socket;
		PlayerState State;
		ChessColor Color;
		bool ISMoving;
	public:


		Player() {};
		Player(String^ name2, Socket^ socket2, PlayerState playerstate, ChessColor color2, bool CanMoving) :Name(name2), socket(socket2), State(playerstate), Color(color2), ISMoving(CanMoving) {}

		PlayerState GetPlayerState() { return State; }
		void SetPlayerState(PlayerState State2) { State = State2; }

		ChessColor GetChessColor() { return Color; }
		void SetChessColor(ChessColor Color2) { Color = Color2; }

		bool GetISMoving() { return ISMoving; }
		void SetISMoving(bool ISMoving2) { ISMoving = ISMoving2; }

		String^ GetName() { return Name; }
		void SetName(String^ Name2) { Name = Name2; }

		Socket^ GetSocket() { return socket; }
		void SetSocket(Socket^ socket2) { socket = socket2; }
	};

	public ref class Game
	{



		//private:
	public:
		//String Winner;
		Player^ Player1;
		Player^ Player2;

		array<PictureBox^, 2>^ AllPB;	//所有PB
		array<Chessman^, 2>^ ChessboardState; //整個棋盤狀況

		Game(Player^ player1, Player^ player2) {

			AllPB = gcnew array<PictureBox^, 2>(9, 10);
			ChessboardState = gcnew array<Chessman^, 2>(9, 10);

			/*	Player1 = gcnew Player(player1->GetName(),nullptr,player1->GetPlayerState(), ChessColor::Blue, true);
				Player2 = gcnew Player(player2->GetName(), nullptr, player2->GetPlayerState(), ChessColor::Green, false);*/
				//
				//ChessboardState = gcnew array<Chessman^, 2>(9, 10); //整個棋盤狀況
				//ChessboardState[3, 0] = gcnew Chessman_Advisors(3, 0, true);
				//ChessboardState[5, 0] = gcnew Chessman_Advisors(5, 0, true);/**/
				//ChessboardState[4, 0] = gcnew Chessman_King(4, 0, true);
				//ChessboardState[8, 5] = gcnew Chessman_Advisors(8, 5, true);
				//ChessboardState[2, 0] = gcnew Chessman_Elephants(2, 0, true);
				//ChessboardState[1, 0] = gcnew Chessman_Knights(1, 0, true);
				//ChessboardState[0, 0] = gcnew Chessman_Rooks(0, 0, true);
				//ChessboardState[1, 2] = gcnew Chessman_Cannons(1, 2, true);
				//ChessboardState[0, 3] = gcnew Chessman_Soldiers(0, 3, true);
				//ChessboardState[2, 3] = gcnew Chessman_Soldiers(2, 3, true);
				//ChessboardState[4, 3] = gcnew Chessman_Soldiers(4, 3, true);
				//ChessboardState[6, 3] = gcnew Chessman_Soldiers(6, 3, true);

				//ChessboardState[3, 4] = gcnew Chessman_Rooks(3, 4, false);

				//ChessboardState[5, 4] = gcnew Chessman_Knights(5, 4, false);
		}


		array<Point^>^ ChangeView(Point^ src, Point^ des) {
			array<Point^>^  path = gcnew array<Point^>(2);
			path[0]->X = 8 - src->X;
			path[0]->Y = 9 - src->Y;
			path[1]->X = 8 - des->X;
			path[1]->Y = 9 - des->Y;
			return path;
		}

	};

	public ref class PacketProcessing {

	public:
		static short PacketNum;

		PacketProcessing() {

		}
		static void  ReceiveMoveInfo(Point^ src, Point^ des, array<Byte>^ data) {


			src->X = BitConverter::ToUInt32(data, 6);
			src->Y = BitConverter::ToUInt32(data, 10);
			des->X = BitConverter::ToUInt32(data, 14);
			des->Y = BitConverter::ToUInt32(data, 18);

		}
		static void  ReceiveMoveInfo(Point^ src, Point^ des, array<Byte>^ data, PlayerState% ReceiveState) {


			PacketNum = BitConverter::ToInt16(data, 0);
			ReceiveState = (PlayerState)BitConverter::ToInt32(data, 2);
			src->X = BitConverter::ToUInt32(data, 6);
			src->Y = BitConverter::ToUInt32(data, 10);
			des->X = BitConverter::ToUInt32(data, 14);
			des->Y = BitConverter::ToUInt32(data, 18);

		}

		static array<Byte>^ MoveInfoToByteArray(Player^ player, Point^ src, Point^ des)
		{
			List<Byte>^ byteList = gcnew List<Byte>();

			byteList->AddRange(BitConverter::GetBytes((short)-5));
			byteList->AddRange(BitConverter::GetBytes((Int32)(player->GetPlayerState())));
			byteList->AddRange(BitConverter::GetBytes(src->X));
			byteList->AddRange(BitConverter::GetBytes(src->Y));
			byteList->AddRange(BitConverter::GetBytes(des->X));
			byteList->AddRange(BitConverter::GetBytes(des->Y));
			return byteList->ToArray();
		}


		static array<Byte>^ WatchingInfoToByteArray(List<Point>^ ChessRecord) {
			List<Byte>^ byteList = gcnew List<Byte>();
			byteList->AddRange(BitConverter::GetBytes(ChessRecord->Count));//先塞陣列長度

			for (int i = 0; i < ChessRecord->Count; i++) {

				byteList->AddRange(BitConverter::GetBytes(ChessRecord[i].X));
				byteList->AddRange(BitConverter::GetBytes(ChessRecord[i].Y));
			}

			return byteList->ToArray();
		}

		static List<Point>^ ReceiveWatchingInfo(array<Byte>^ data, int& count) {


			List<Point>^ MoveArray = gcnew List<Point>();

			count= BitConverter::ToInt32(data, 0);


			for (int i = 0;i<count;i++) {
			
				Point^ temp = gcnew Point(BitConverter::ToInt32(data, 4 + i * 8), BitConverter::ToInt32(data, 8 + i * 8));
				MoveArray->Add(*temp);
			
			}

			return MoveArray;
		};




	};

};