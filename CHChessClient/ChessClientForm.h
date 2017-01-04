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
	using namespace System::Threading;
	/// <summary>
	/// ChessClientForm 的摘要
	/// </summary>
	public ref class ChessClientForm : public System::Windows::Forms::Form
	{
	public:
		ChessClientForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
			

			AllPB= gcnew array<PictureBox^, 2>(9, 10);

			
			AllPB[0, 0] = PB00; AllPB[0, 1] = PB01; AllPB[0, 2] = PB02; AllPB[0, 3] = PB03; AllPB[0, 4] = PB04; AllPB[0, 5] = PB05; AllPB[0, 6] = PB06; AllPB[0, 7] = PB07; AllPB[0, 8] = PB08; AllPB[0, 9] = PB09;
			AllPB[1, 0] = PB10; AllPB[1, 1] = PB11; AllPB[1, 2] = PB12; AllPB[1, 3] = PB13; AllPB[1, 4] = PB14; AllPB[1, 5] = PB15; AllPB[1, 6] = PB16; AllPB[1, 7] = PB17; AllPB[1, 8] = PB18; AllPB[1, 9] = PB19;
			AllPB[2, 0] = PB20; AllPB[2, 1] = PB21; AllPB[2, 2] = PB22; AllPB[2, 3] = PB23; AllPB[2, 4] = PB24; AllPB[2, 5] = PB25; AllPB[2, 6] = PB26; AllPB[2, 7] = PB27; AllPB[2, 8] = PB28; AllPB[2, 9] = PB29;
			AllPB[3, 0] = PB00; AllPB[3, 1] = PB31; AllPB[3, 2] = PB32; AllPB[3, 3] = PB33; AllPB[3, 4] = PB34; AllPB[3, 5] = PB35; AllPB[3, 6] = PB36; AllPB[3, 7] = PB37; AllPB[3, 8] = PB38; AllPB[3, 9] = PB39;
			AllPB[4, 0] = PB00; AllPB[4, 1] = PB41; AllPB[4, 2] = PB42; AllPB[4, 3] = PB43; AllPB[4, 4] = PB44; AllPB[4, 5] = PB45; AllPB[4, 6] = PB46; AllPB[4, 7] = PB47; AllPB[4, 8] = PB48; AllPB[4, 9] = PB49;
			AllPB[5, 0] = PB00; AllPB[5, 1] = PB51; AllPB[5, 2] = PB52; AllPB[5, 3] = PB53; AllPB[5, 4] = PB54; AllPB[5, 5] = PB55; AllPB[5, 6] = PB56; AllPB[5, 7] = PB57; AllPB[5, 8] = PB58; AllPB[5, 9] = PB59;
			AllPB[6, 0] = PB00; AllPB[6, 1] = PB61; AllPB[6, 2] = PB62; AllPB[6, 3] = PB63; AllPB[6, 4] = PB64; AllPB[6, 5] = PB65; AllPB[6, 6] = PB66; AllPB[6, 7] = PB67; AllPB[6, 8] = PB68; AllPB[6, 9] = PB69;
			AllPB[7, 0] = PB00; AllPB[7, 1] = PB71; AllPB[7, 2] = PB72; AllPB[7, 3] = PB73; AllPB[7, 4] = PB74; AllPB[7, 5] = PB75; AllPB[7, 6] = PB76; AllPB[7, 7] = PB77; AllPB[7, 8] = PB78; AllPB[7, 9] = PB79;
			AllPB[8, 0] = PB00; AllPB[8, 1] = PB81; AllPB[8, 2] = PB82; AllPB[8, 3] = PB83; AllPB[8, 4] = PB84; AllPB[8, 5] = PB85; AllPB[8, 6] = PB86; AllPB[8, 7] = PB87; AllPB[8, 8] = PB88; AllPB[8, 9] = PB89;
		


			
			for (unsigned int i = 0; i < 9; i++) {
				for (unsigned int j = 0; j < 10; j++) {
					AllPB[i, j]->AllowDrop = true;
					AllPB[i, j]->MouseDown += gcnew MouseEventHandler(this, &ChessClientForm::PB00_MouseDown);
					AllPB[i, j]->DragEnter += gcnew DragEventHandler(this, &ChessClientForm::PB00_DragEnter);
					AllPB[i, j]->DragDrop += gcnew DragEventHandler(this, &ChessClientForm::PB00_DragDrop);
				}			
			}
	
			//this->ChessboardPanel->Controls->Add(this->pictureBox1, 8, 4);
			//ChessboardPanel->GetType()->GetProperty("DoubleBuffered", System::Reflection::BindingFlags::Instance | System::Reflection::BindingFlags::NonPublic)->SetValue(ChessboardPanel, true, nullptr);

			//pictureBox1->MouseDown += pictureBox1_MouseDown;
			//pictureBox3->AllowDrop = true;
			//pictureBox3->DragEnter += pictureBox3_DragEnter;
			//pictureBox3->DragDrop += pictureBox3_DragDrop;
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~ChessClientForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// 設計工具所需的變數。

		PictureBox^ MouseDown;
		array<PictureBox^, 2>^ AllPB ;
		Socket^ clientSocket;
		String^ Name;
		array<Byte>^ buffer;
		bool drag = false;   // 記錄是否可拖曳，預設為不可
		int sX, sY;         // 記錄滑鼠按下時的座標値
	private: System::Windows::Forms::Button^  send;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;



	private: System::Windows::Forms::PictureBox^  PB09;




	private: System::Windows::Forms::Panel^  Chessboardpanel;
	private: System::Windows::Forms::PictureBox^  PB80;
	private: System::Windows::Forms::PictureBox^  PB70;
	private: System::Windows::Forms::PictureBox^  PB60;
	private: System::Windows::Forms::PictureBox^  PB50;
	private: System::Windows::Forms::PictureBox^  PB40;
	private: System::Windows::Forms::PictureBox^  PB30;
	private: System::Windows::Forms::PictureBox^  PB20;
	private: System::Windows::Forms::PictureBox^  PB10;
	private: System::Windows::Forms::PictureBox^  PB00;
	private: System::Windows::Forms::PictureBox^  PB81;
	private: System::Windows::Forms::PictureBox^  PB71;
	private: System::Windows::Forms::PictureBox^  PB61;
	private: System::Windows::Forms::PictureBox^  PB51;
	private: System::Windows::Forms::PictureBox^  PB41;
	private: System::Windows::Forms::PictureBox^  PB31;
	private: System::Windows::Forms::PictureBox^  PB21;
	private: System::Windows::Forms::PictureBox^  PB11;
	private: System::Windows::Forms::PictureBox^  PB01;
	private: System::Windows::Forms::PictureBox^  PB82;
























	private: System::Windows::Forms::PictureBox^  PB72;

	private: System::Windows::Forms::PictureBox^  PB62;

	private: System::Windows::Forms::PictureBox^  PB52;

	private: System::Windows::Forms::PictureBox^  PB42;

	private: System::Windows::Forms::PictureBox^  PB32;

	private: System::Windows::Forms::PictureBox^  PB22;

private: System::Windows::Forms::PictureBox^  PB12;

private: System::Windows::Forms::PictureBox^  PB02;
private: System::Windows::Forms::PictureBox^  PB83;


private: System::Windows::Forms::PictureBox^  PB73;

private: System::Windows::Forms::PictureBox^  PB63;

private: System::Windows::Forms::PictureBox^  PB53;

private: System::Windows::Forms::PictureBox^  PB43;

private: System::Windows::Forms::PictureBox^  PB33;

private: System::Windows::Forms::PictureBox^  PB23;

private: System::Windows::Forms::PictureBox^  PB13;

private: System::Windows::Forms::PictureBox^  PB03;
private: System::Windows::Forms::PictureBox^  PB84;


private: System::Windows::Forms::PictureBox^  PB74;

private: System::Windows::Forms::PictureBox^  PB64;

private: System::Windows::Forms::PictureBox^  PB54;

private: System::Windows::Forms::PictureBox^  PB44;

private: System::Windows::Forms::PictureBox^  PB34;

private: System::Windows::Forms::PictureBox^  PB24;

private: System::Windows::Forms::PictureBox^  PB14;

private: System::Windows::Forms::PictureBox^  PB04;
private: System::Windows::Forms::PictureBox^  PB85;


private: System::Windows::Forms::PictureBox^  PB75;

private: System::Windows::Forms::PictureBox^  PB65;

private: System::Windows::Forms::PictureBox^  PB55;

private: System::Windows::Forms::PictureBox^  PB45;

private: System::Windows::Forms::PictureBox^  PB35;

private: System::Windows::Forms::PictureBox^  PB25;

private: System::Windows::Forms::PictureBox^  PB15;

private: System::Windows::Forms::PictureBox^  PB05;
private: System::Windows::Forms::PictureBox^  PB86;


private: System::Windows::Forms::PictureBox^  PB76;

private: System::Windows::Forms::PictureBox^  PB66;

private: System::Windows::Forms::PictureBox^  PB56;

private: System::Windows::Forms::PictureBox^  PB46;

private: System::Windows::Forms::PictureBox^  PB36;

private: System::Windows::Forms::PictureBox^  PB26;

private: System::Windows::Forms::PictureBox^  PB16;

private: System::Windows::Forms::PictureBox^  PB06;
private: System::Windows::Forms::PictureBox^  PB87;


private: System::Windows::Forms::PictureBox^  PB77;

private: System::Windows::Forms::PictureBox^  PB67;

private: System::Windows::Forms::PictureBox^  PB57;

private: System::Windows::Forms::PictureBox^  PB47;

private: System::Windows::Forms::PictureBox^  PB37;

private: System::Windows::Forms::PictureBox^  PB27;

private: System::Windows::Forms::PictureBox^  PB17;

private: System::Windows::Forms::PictureBox^  PB07;
private: System::Windows::Forms::PictureBox^  PB88;


private: System::Windows::Forms::PictureBox^  PB78;

private: System::Windows::Forms::PictureBox^  PB68;

private: System::Windows::Forms::PictureBox^  PB58;

private: System::Windows::Forms::PictureBox^  PB48;

private: System::Windows::Forms::PictureBox^  PB38;

private: System::Windows::Forms::PictureBox^  PB28;

private: System::Windows::Forms::PictureBox^  PB18;

private: System::Windows::Forms::PictureBox^  PB08;
private: System::Windows::Forms::PictureBox^  PB89;


private: System::Windows::Forms::PictureBox^  PB79;

private: System::Windows::Forms::PictureBox^  PB69;

private: System::Windows::Forms::PictureBox^  PB59;

private: System::Windows::Forms::PictureBox^  PB49;

private: System::Windows::Forms::PictureBox^  PB39;

private: System::Windows::Forms::PictureBox^  PB29;

private: System::Windows::Forms::PictureBox^  PB19;







		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ChessClientForm::typeid));
			this->send = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->PB09 = (gcnew System::Windows::Forms::PictureBox());
			this->Chessboardpanel = (gcnew System::Windows::Forms::Panel());
			this->PB80 = (gcnew System::Windows::Forms::PictureBox());
			this->PB70 = (gcnew System::Windows::Forms::PictureBox());
			this->PB60 = (gcnew System::Windows::Forms::PictureBox());
			this->PB50 = (gcnew System::Windows::Forms::PictureBox());
			this->PB40 = (gcnew System::Windows::Forms::PictureBox());
			this->PB30 = (gcnew System::Windows::Forms::PictureBox());
			this->PB20 = (gcnew System::Windows::Forms::PictureBox());
			this->PB10 = (gcnew System::Windows::Forms::PictureBox());
			this->PB00 = (gcnew System::Windows::Forms::PictureBox());
			this->PB81 = (gcnew System::Windows::Forms::PictureBox());
			this->PB71 = (gcnew System::Windows::Forms::PictureBox());
			this->PB61 = (gcnew System::Windows::Forms::PictureBox());
			this->PB51 = (gcnew System::Windows::Forms::PictureBox());
			this->PB41 = (gcnew System::Windows::Forms::PictureBox());
			this->PB31 = (gcnew System::Windows::Forms::PictureBox());
			this->PB21 = (gcnew System::Windows::Forms::PictureBox());
			this->PB11 = (gcnew System::Windows::Forms::PictureBox());
			this->PB01 = (gcnew System::Windows::Forms::PictureBox());
			this->PB82 = (gcnew System::Windows::Forms::PictureBox());
			this->PB72 = (gcnew System::Windows::Forms::PictureBox());
			this->PB62 = (gcnew System::Windows::Forms::PictureBox());
			this->PB52 = (gcnew System::Windows::Forms::PictureBox());
			this->PB42 = (gcnew System::Windows::Forms::PictureBox());
			this->PB32 = (gcnew System::Windows::Forms::PictureBox());
			this->PB22 = (gcnew System::Windows::Forms::PictureBox());
			this->PB12 = (gcnew System::Windows::Forms::PictureBox());
			this->PB02 = (gcnew System::Windows::Forms::PictureBox());
			this->PB83 = (gcnew System::Windows::Forms::PictureBox());
			this->PB73 = (gcnew System::Windows::Forms::PictureBox());
			this->PB63 = (gcnew System::Windows::Forms::PictureBox());
			this->PB53 = (gcnew System::Windows::Forms::PictureBox());
			this->PB43 = (gcnew System::Windows::Forms::PictureBox());
			this->PB33 = (gcnew System::Windows::Forms::PictureBox());
			this->PB23 = (gcnew System::Windows::Forms::PictureBox());
			this->PB13 = (gcnew System::Windows::Forms::PictureBox());
			this->PB03 = (gcnew System::Windows::Forms::PictureBox());
			this->PB84 = (gcnew System::Windows::Forms::PictureBox());
			this->PB74 = (gcnew System::Windows::Forms::PictureBox());
			this->PB64 = (gcnew System::Windows::Forms::PictureBox());
			this->PB54 = (gcnew System::Windows::Forms::PictureBox());
			this->PB44 = (gcnew System::Windows::Forms::PictureBox());
			this->PB34 = (gcnew System::Windows::Forms::PictureBox());
			this->PB24 = (gcnew System::Windows::Forms::PictureBox());
			this->PB14 = (gcnew System::Windows::Forms::PictureBox());
			this->PB04 = (gcnew System::Windows::Forms::PictureBox());
			this->PB85 = (gcnew System::Windows::Forms::PictureBox());
			this->PB75 = (gcnew System::Windows::Forms::PictureBox());
			this->PB65 = (gcnew System::Windows::Forms::PictureBox());
			this->PB55 = (gcnew System::Windows::Forms::PictureBox());
			this->PB45 = (gcnew System::Windows::Forms::PictureBox());
			this->PB35 = (gcnew System::Windows::Forms::PictureBox());
			this->PB25 = (gcnew System::Windows::Forms::PictureBox());
			this->PB15 = (gcnew System::Windows::Forms::PictureBox());
			this->PB05 = (gcnew System::Windows::Forms::PictureBox());
			this->PB86 = (gcnew System::Windows::Forms::PictureBox());
			this->PB76 = (gcnew System::Windows::Forms::PictureBox());
			this->PB66 = (gcnew System::Windows::Forms::PictureBox());
			this->PB56 = (gcnew System::Windows::Forms::PictureBox());
			this->PB46 = (gcnew System::Windows::Forms::PictureBox());
			this->PB36 = (gcnew System::Windows::Forms::PictureBox());
			this->PB26 = (gcnew System::Windows::Forms::PictureBox());
			this->PB16 = (gcnew System::Windows::Forms::PictureBox());
			this->PB06 = (gcnew System::Windows::Forms::PictureBox());
			this->PB87 = (gcnew System::Windows::Forms::PictureBox());
			this->PB77 = (gcnew System::Windows::Forms::PictureBox());
			this->PB67 = (gcnew System::Windows::Forms::PictureBox());
			this->PB57 = (gcnew System::Windows::Forms::PictureBox());
			this->PB47 = (gcnew System::Windows::Forms::PictureBox());
			this->PB37 = (gcnew System::Windows::Forms::PictureBox());
			this->PB27 = (gcnew System::Windows::Forms::PictureBox());
			this->PB17 = (gcnew System::Windows::Forms::PictureBox());
			this->PB07 = (gcnew System::Windows::Forms::PictureBox());
			this->PB88 = (gcnew System::Windows::Forms::PictureBox());
			this->PB78 = (gcnew System::Windows::Forms::PictureBox());
			this->PB68 = (gcnew System::Windows::Forms::PictureBox());
			this->PB58 = (gcnew System::Windows::Forms::PictureBox());
			this->PB48 = (gcnew System::Windows::Forms::PictureBox());
			this->PB38 = (gcnew System::Windows::Forms::PictureBox());
			this->PB28 = (gcnew System::Windows::Forms::PictureBox());
			this->PB18 = (gcnew System::Windows::Forms::PictureBox());
			this->PB08 = (gcnew System::Windows::Forms::PictureBox());
			this->PB89 = (gcnew System::Windows::Forms::PictureBox());
			this->PB79 = (gcnew System::Windows::Forms::PictureBox());
			this->PB69 = (gcnew System::Windows::Forms::PictureBox());
			this->PB59 = (gcnew System::Windows::Forms::PictureBox());
			this->PB49 = (gcnew System::Windows::Forms::PictureBox());
			this->PB39 = (gcnew System::Windows::Forms::PictureBox());
			this->PB29 = (gcnew System::Windows::Forms::PictureBox());
			this->PB19 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB09))->BeginInit();
			this->Chessboardpanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB80))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB70))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB60))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB50))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB40))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB30))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB20))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB00))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB81))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB71))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB61))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB51))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB41))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB31))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB21))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB11))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB01))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB82))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB72))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB62))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB52))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB42))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB32))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB22))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB12))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB02))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB83))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB73))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB63))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB53))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB43))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB33))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB23))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB13))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB03))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB84))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB74))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB64))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB54))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB44))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB34))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB24))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB14))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB04))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB85))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB75))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB65))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB55))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB45))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB35))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB25))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB15))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB05))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB86))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB76))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB66))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB56))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB46))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB36))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB26))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB16))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB06))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB87))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB77))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB67))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB57))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB47))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB37))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB27))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB17))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB07))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB88))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB78))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB68))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB58))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB48))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB38))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB28))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB18))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB08))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB89))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB79))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB69))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB59))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB49))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB39))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB29))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB19))->BeginInit();
			this->SuspendLayout();
			// 
			// send
			// 
			this->send->Location = System::Drawing::Point(911, 396);
			this->send->Name = L"send";
			this->send->Size = System::Drawing::Size(75, 23);
			this->send->TabIndex = 0;
			this->send->Text = L"send";
			this->send->UseVisualStyleBackColor = true;
			this->send->Click += gcnew System::EventHandler(this, &ChessClientForm::send_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(911, 344);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ChessClientForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(803, 30);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(208, 230);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ChessClientForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(886, 443);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 3;
			// 
			// PB09
			// 
			this->PB09->BackColor = System::Drawing::Color::Transparent;
			this->PB09->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB09->Location = System::Drawing::Point(17, 20);
			this->PB09->Name = L"PB09";
			this->PB09->Size = System::Drawing::Size(60, 60);
			this->PB09->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB09->TabIndex = 6;
			this->PB09->TabStop = false;
			// 
			// Chessboardpanel
			// 
			this->Chessboardpanel->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"Chessboardpanel.BackgroundImage")));
			this->Chessboardpanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->Chessboardpanel->Controls->Add(this->PB80);
			this->Chessboardpanel->Controls->Add(this->PB70);
			this->Chessboardpanel->Controls->Add(this->PB60);
			this->Chessboardpanel->Controls->Add(this->PB50);
			this->Chessboardpanel->Controls->Add(this->PB40);
			this->Chessboardpanel->Controls->Add(this->PB30);
			this->Chessboardpanel->Controls->Add(this->PB20);
			this->Chessboardpanel->Controls->Add(this->PB10);
			this->Chessboardpanel->Controls->Add(this->PB00);
			this->Chessboardpanel->Controls->Add(this->PB81);
			this->Chessboardpanel->Controls->Add(this->PB71);
			this->Chessboardpanel->Controls->Add(this->PB61);
			this->Chessboardpanel->Controls->Add(this->PB51);
			this->Chessboardpanel->Controls->Add(this->PB41);
			this->Chessboardpanel->Controls->Add(this->PB31);
			this->Chessboardpanel->Controls->Add(this->PB21);
			this->Chessboardpanel->Controls->Add(this->PB11);
			this->Chessboardpanel->Controls->Add(this->PB01);
			this->Chessboardpanel->Controls->Add(this->PB82);
			this->Chessboardpanel->Controls->Add(this->PB72);
			this->Chessboardpanel->Controls->Add(this->PB62);
			this->Chessboardpanel->Controls->Add(this->PB52);
			this->Chessboardpanel->Controls->Add(this->PB42);
			this->Chessboardpanel->Controls->Add(this->PB32);
			this->Chessboardpanel->Controls->Add(this->PB22);
			this->Chessboardpanel->Controls->Add(this->PB12);
			this->Chessboardpanel->Controls->Add(this->PB02);
			this->Chessboardpanel->Controls->Add(this->PB83);
			this->Chessboardpanel->Controls->Add(this->PB73);
			this->Chessboardpanel->Controls->Add(this->PB63);
			this->Chessboardpanel->Controls->Add(this->PB53);
			this->Chessboardpanel->Controls->Add(this->PB43);
			this->Chessboardpanel->Controls->Add(this->PB33);
			this->Chessboardpanel->Controls->Add(this->PB23);
			this->Chessboardpanel->Controls->Add(this->PB13);
			this->Chessboardpanel->Controls->Add(this->PB03);
			this->Chessboardpanel->Controls->Add(this->PB84);
			this->Chessboardpanel->Controls->Add(this->PB74);
			this->Chessboardpanel->Controls->Add(this->PB64);
			this->Chessboardpanel->Controls->Add(this->PB54);
			this->Chessboardpanel->Controls->Add(this->PB44);
			this->Chessboardpanel->Controls->Add(this->PB34);
			this->Chessboardpanel->Controls->Add(this->PB24);
			this->Chessboardpanel->Controls->Add(this->PB14);
			this->Chessboardpanel->Controls->Add(this->PB04);
			this->Chessboardpanel->Controls->Add(this->PB85);
			this->Chessboardpanel->Controls->Add(this->PB75);
			this->Chessboardpanel->Controls->Add(this->PB65);
			this->Chessboardpanel->Controls->Add(this->PB55);
			this->Chessboardpanel->Controls->Add(this->PB45);
			this->Chessboardpanel->Controls->Add(this->PB35);
			this->Chessboardpanel->Controls->Add(this->PB25);
			this->Chessboardpanel->Controls->Add(this->PB15);
			this->Chessboardpanel->Controls->Add(this->PB05);
			this->Chessboardpanel->Controls->Add(this->PB86);
			this->Chessboardpanel->Controls->Add(this->PB76);
			this->Chessboardpanel->Controls->Add(this->PB66);
			this->Chessboardpanel->Controls->Add(this->PB56);
			this->Chessboardpanel->Controls->Add(this->PB46);
			this->Chessboardpanel->Controls->Add(this->PB36);
			this->Chessboardpanel->Controls->Add(this->PB26);
			this->Chessboardpanel->Controls->Add(this->PB16);
			this->Chessboardpanel->Controls->Add(this->PB06);
			this->Chessboardpanel->Controls->Add(this->PB87);
			this->Chessboardpanel->Controls->Add(this->PB77);
			this->Chessboardpanel->Controls->Add(this->PB67);
			this->Chessboardpanel->Controls->Add(this->PB57);
			this->Chessboardpanel->Controls->Add(this->PB47);
			this->Chessboardpanel->Controls->Add(this->PB37);
			this->Chessboardpanel->Controls->Add(this->PB27);
			this->Chessboardpanel->Controls->Add(this->PB17);
			this->Chessboardpanel->Controls->Add(this->PB07);
			this->Chessboardpanel->Controls->Add(this->PB88);
			this->Chessboardpanel->Controls->Add(this->PB78);
			this->Chessboardpanel->Controls->Add(this->PB68);
			this->Chessboardpanel->Controls->Add(this->PB58);
			this->Chessboardpanel->Controls->Add(this->PB48);
			this->Chessboardpanel->Controls->Add(this->PB38);
			this->Chessboardpanel->Controls->Add(this->PB28);
			this->Chessboardpanel->Controls->Add(this->PB18);
			this->Chessboardpanel->Controls->Add(this->PB08);
			this->Chessboardpanel->Controls->Add(this->PB89);
			this->Chessboardpanel->Controls->Add(this->PB79);
			this->Chessboardpanel->Controls->Add(this->PB69);
			this->Chessboardpanel->Controls->Add(this->PB59);
			this->Chessboardpanel->Controls->Add(this->PB49);
			this->Chessboardpanel->Controls->Add(this->PB39);
			this->Chessboardpanel->Controls->Add(this->PB29);
			this->Chessboardpanel->Controls->Add(this->PB19);
			this->Chessboardpanel->Controls->Add(this->PB09);
			this->Chessboardpanel->Location = System::Drawing::Point(35, 21);
			this->Chessboardpanel->Name = L"Chessboardpanel";
			this->Chessboardpanel->Size = System::Drawing::Size(679, 723);
			this->Chessboardpanel->TabIndex = 7;
			// 
			// PB80
			// 
			this->PB80->BackColor = System::Drawing::Color::Transparent;
			this->PB80->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB80->Location = System::Drawing::Point(597, 647);
			this->PB80->Name = L"PB80";
			this->PB80->Size = System::Drawing::Size(60, 60);
			this->PB80->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB80->TabIndex = 95;
			this->PB80->TabStop = false;
			// 
			// PB70
			// 
			this->PB70->BackColor = System::Drawing::Color::Transparent;
			this->PB70->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB70->Location = System::Drawing::Point(525, 647);
			this->PB70->Name = L"PB70";
			this->PB70->Size = System::Drawing::Size(60, 60);
			this->PB70->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB70->TabIndex = 94;
			this->PB70->TabStop = false;
			// 
			// PB60
			// 
			this->PB60->BackColor = System::Drawing::Color::Transparent;
			this->PB60->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB60->Location = System::Drawing::Point(454, 647);
			this->PB60->Name = L"PB60";
			this->PB60->Size = System::Drawing::Size(60, 60);
			this->PB60->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB60->TabIndex = 93;
			this->PB60->TabStop = false;
			// 
			// PB50
			// 
			this->PB50->BackColor = System::Drawing::Color::Transparent;
			this->PB50->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB50->Location = System::Drawing::Point(382, 647);
			this->PB50->Name = L"PB50";
			this->PB50->Size = System::Drawing::Size(60, 60);
			this->PB50->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB50->TabIndex = 92;
			this->PB50->TabStop = false;
			// 
			// PB40
			// 
			this->PB40->BackColor = System::Drawing::Color::Transparent;
			this->PB40->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB40->Location = System::Drawing::Point(308, 647);
			this->PB40->Name = L"PB40";
			this->PB40->Size = System::Drawing::Size(60, 60);
			this->PB40->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB40->TabIndex = 91;
			this->PB40->TabStop = false;
			// 
			// PB30
			// 
			this->PB30->BackColor = System::Drawing::Color::Transparent;
			this->PB30->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB30->Location = System::Drawing::Point(236, 647);
			this->PB30->Name = L"PB30";
			this->PB30->Size = System::Drawing::Size(60, 60);
			this->PB30->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB30->TabIndex = 90;
			this->PB30->TabStop = false;
			// 
			// PB20
			// 
			this->PB20->BackColor = System::Drawing::Color::Transparent;
			this->PB20->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB20->Location = System::Drawing::Point(165, 647);
			this->PB20->Name = L"PB20";
			this->PB20->Size = System::Drawing::Size(60, 60);
			this->PB20->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB20->TabIndex = 89;
			this->PB20->TabStop = false;
			// 
			// PB10
			// 
			this->PB10->BackColor = System::Drawing::Color::Transparent;
			this->PB10->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB10->Location = System::Drawing::Point(93, 647);
			this->PB10->Name = L"PB10";
			this->PB10->Size = System::Drawing::Size(60, 60);
			this->PB10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB10->TabIndex = 88;
			this->PB10->TabStop = false;
			// 
			// PB00
			// 
			this->PB00->BackColor = System::Drawing::Color::Transparent;
			this->PB00->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB00->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB00.Image")));
			this->PB00->Location = System::Drawing::Point(17, 647);
			this->PB00->Name = L"PB00";
			this->PB00->Size = System::Drawing::Size(60, 60);
			this->PB00->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB00->TabIndex = 87;
			this->PB00->TabStop = false;
			this->PB00->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &ChessClientForm::PB00_DragDrop);
			this->PB00->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &ChessClientForm::PB00_DragEnter);
			this->PB00->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ChessClientForm::PB00_MouseDown);
			// 
			// PB81
			// 
			this->PB81->BackColor = System::Drawing::Color::Transparent;
			this->PB81->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB81->Location = System::Drawing::Point(597, 572);
			this->PB81->Name = L"PB81";
			this->PB81->Size = System::Drawing::Size(60, 60);
			this->PB81->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB81->TabIndex = 86;
			this->PB81->TabStop = false;
			// 
			// PB71
			// 
			this->PB71->BackColor = System::Drawing::Color::Transparent;
			this->PB71->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB71->Location = System::Drawing::Point(525, 572);
			this->PB71->Name = L"PB71";
			this->PB71->Size = System::Drawing::Size(60, 60);
			this->PB71->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB71->TabIndex = 85;
			this->PB71->TabStop = false;
			// 
			// PB61
			// 
			this->PB61->BackColor = System::Drawing::Color::Transparent;
			this->PB61->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB61->Location = System::Drawing::Point(454, 572);
			this->PB61->Name = L"PB61";
			this->PB61->Size = System::Drawing::Size(60, 60);
			this->PB61->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB61->TabIndex = 84;
			this->PB61->TabStop = false;
			// 
			// PB51
			// 
			this->PB51->BackColor = System::Drawing::Color::Transparent;
			this->PB51->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB51->Location = System::Drawing::Point(382, 572);
			this->PB51->Name = L"PB51";
			this->PB51->Size = System::Drawing::Size(60, 60);
			this->PB51->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB51->TabIndex = 83;
			this->PB51->TabStop = false;
			// 
			// PB41
			// 
			this->PB41->BackColor = System::Drawing::Color::Transparent;
			this->PB41->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB41->Location = System::Drawing::Point(308, 572);
			this->PB41->Name = L"PB41";
			this->PB41->Size = System::Drawing::Size(60, 60);
			this->PB41->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB41->TabIndex = 82;
			this->PB41->TabStop = false;
			// 
			// PB31
			// 
			this->PB31->BackColor = System::Drawing::Color::Transparent;
			this->PB31->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB31->Location = System::Drawing::Point(236, 572);
			this->PB31->Name = L"PB31";
			this->PB31->Size = System::Drawing::Size(60, 60);
			this->PB31->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB31->TabIndex = 81;
			this->PB31->TabStop = false;
			// 
			// PB21
			// 
			this->PB21->BackColor = System::Drawing::Color::Transparent;
			this->PB21->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB21->Location = System::Drawing::Point(165, 572);
			this->PB21->Name = L"PB21";
			this->PB21->Size = System::Drawing::Size(60, 60);
			this->PB21->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB21->TabIndex = 80;
			this->PB21->TabStop = false;
			// 
			// PB11
			// 
			this->PB11->BackColor = System::Drawing::Color::Transparent;
			this->PB11->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB11->Location = System::Drawing::Point(93, 572);
			this->PB11->Name = L"PB11";
			this->PB11->Size = System::Drawing::Size(60, 60);
			this->PB11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB11->TabIndex = 79;
			this->PB11->TabStop = false;
			// 
			// PB01
			// 
			this->PB01->BackColor = System::Drawing::Color::Transparent;
			this->PB01->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB01->Location = System::Drawing::Point(17, 572);
			this->PB01->Name = L"PB01";
			this->PB01->Size = System::Drawing::Size(60, 60);
			this->PB01->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB01->TabIndex = 78;
			this->PB01->TabStop = false;
			// 
			// PB82
			// 
			this->PB82->BackColor = System::Drawing::Color::Transparent;
			this->PB82->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB82->Location = System::Drawing::Point(597, 506);
			this->PB82->Name = L"PB82";
			this->PB82->Size = System::Drawing::Size(60, 60);
			this->PB82->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB82->TabIndex = 77;
			this->PB82->TabStop = false;
			// 
			// PB72
			// 
			this->PB72->BackColor = System::Drawing::Color::Transparent;
			this->PB72->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB72->Location = System::Drawing::Point(525, 506);
			this->PB72->Name = L"PB72";
			this->PB72->Size = System::Drawing::Size(60, 60);
			this->PB72->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB72->TabIndex = 76;
			this->PB72->TabStop = false;
			// 
			// PB62
			// 
			this->PB62->BackColor = System::Drawing::Color::Transparent;
			this->PB62->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB62->Location = System::Drawing::Point(454, 506);
			this->PB62->Name = L"PB62";
			this->PB62->Size = System::Drawing::Size(60, 60);
			this->PB62->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB62->TabIndex = 75;
			this->PB62->TabStop = false;
			// 
			// PB52
			// 
			this->PB52->BackColor = System::Drawing::Color::Transparent;
			this->PB52->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB52->Location = System::Drawing::Point(382, 506);
			this->PB52->Name = L"PB52";
			this->PB52->Size = System::Drawing::Size(60, 60);
			this->PB52->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB52->TabIndex = 74;
			this->PB52->TabStop = false;
			// 
			// PB42
			// 
			this->PB42->BackColor = System::Drawing::Color::Transparent;
			this->PB42->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB42->Location = System::Drawing::Point(308, 506);
			this->PB42->Name = L"PB42";
			this->PB42->Size = System::Drawing::Size(60, 60);
			this->PB42->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB42->TabIndex = 73;
			this->PB42->TabStop = false;
			// 
			// PB32
			// 
			this->PB32->BackColor = System::Drawing::Color::Transparent;
			this->PB32->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB32->Location = System::Drawing::Point(236, 506);
			this->PB32->Name = L"PB32";
			this->PB32->Size = System::Drawing::Size(60, 60);
			this->PB32->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB32->TabIndex = 72;
			this->PB32->TabStop = false;
			// 
			// PB22
			// 
			this->PB22->BackColor = System::Drawing::Color::Transparent;
			this->PB22->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB22->Location = System::Drawing::Point(165, 506);
			this->PB22->Name = L"PB22";
			this->PB22->Size = System::Drawing::Size(60, 60);
			this->PB22->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB22->TabIndex = 71;
			this->PB22->TabStop = false;
			// 
			// PB12
			// 
			this->PB12->BackColor = System::Drawing::Color::Transparent;
			this->PB12->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB12->Location = System::Drawing::Point(93, 506);
			this->PB12->Name = L"PB12";
			this->PB12->Size = System::Drawing::Size(60, 60);
			this->PB12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB12->TabIndex = 70;
			this->PB12->TabStop = false;
			// 
			// PB02
			// 
			this->PB02->BackColor = System::Drawing::Color::Transparent;
			this->PB02->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB02->Location = System::Drawing::Point(17, 506);
			this->PB02->Name = L"PB02";
			this->PB02->Size = System::Drawing::Size(60, 60);
			this->PB02->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB02->TabIndex = 69;
			this->PB02->TabStop = false;
			// 
			// PB83
			// 
			this->PB83->BackColor = System::Drawing::Color::Transparent;
			this->PB83->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB83->Location = System::Drawing::Point(597, 431);
			this->PB83->Name = L"PB83";
			this->PB83->Size = System::Drawing::Size(60, 60);
			this->PB83->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB83->TabIndex = 68;
			this->PB83->TabStop = false;
			// 
			// PB73
			// 
			this->PB73->BackColor = System::Drawing::Color::Transparent;
			this->PB73->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB73->Location = System::Drawing::Point(525, 431);
			this->PB73->Name = L"PB73";
			this->PB73->Size = System::Drawing::Size(60, 60);
			this->PB73->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB73->TabIndex = 67;
			this->PB73->TabStop = false;
			// 
			// PB63
			// 
			this->PB63->BackColor = System::Drawing::Color::Transparent;
			this->PB63->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB63->Location = System::Drawing::Point(454, 431);
			this->PB63->Name = L"PB63";
			this->PB63->Size = System::Drawing::Size(60, 60);
			this->PB63->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB63->TabIndex = 66;
			this->PB63->TabStop = false;
			// 
			// PB53
			// 
			this->PB53->BackColor = System::Drawing::Color::Transparent;
			this->PB53->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB53->Location = System::Drawing::Point(382, 431);
			this->PB53->Name = L"PB53";
			this->PB53->Size = System::Drawing::Size(60, 60);
			this->PB53->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB53->TabIndex = 65;
			this->PB53->TabStop = false;
			// 
			// PB43
			// 
			this->PB43->BackColor = System::Drawing::Color::Transparent;
			this->PB43->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB43->Location = System::Drawing::Point(308, 431);
			this->PB43->Name = L"PB43";
			this->PB43->Size = System::Drawing::Size(60, 60);
			this->PB43->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB43->TabIndex = 64;
			this->PB43->TabStop = false;
			// 
			// PB33
			// 
			this->PB33->BackColor = System::Drawing::Color::Transparent;
			this->PB33->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB33->Location = System::Drawing::Point(236, 431);
			this->PB33->Name = L"PB33";
			this->PB33->Size = System::Drawing::Size(60, 60);
			this->PB33->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB33->TabIndex = 63;
			this->PB33->TabStop = false;
			// 
			// PB23
			// 
			this->PB23->BackColor = System::Drawing::Color::Transparent;
			this->PB23->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB23->Location = System::Drawing::Point(165, 431);
			this->PB23->Name = L"PB23";
			this->PB23->Size = System::Drawing::Size(60, 60);
			this->PB23->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB23->TabIndex = 62;
			this->PB23->TabStop = false;
			// 
			// PB13
			// 
			this->PB13->BackColor = System::Drawing::Color::Transparent;
			this->PB13->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB13->Location = System::Drawing::Point(93, 431);
			this->PB13->Name = L"PB13";
			this->PB13->Size = System::Drawing::Size(60, 60);
			this->PB13->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB13->TabIndex = 61;
			this->PB13->TabStop = false;
			// 
			// PB03
			// 
			this->PB03->BackColor = System::Drawing::Color::Transparent;
			this->PB03->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB03->Location = System::Drawing::Point(17, 431);
			this->PB03->Name = L"PB03";
			this->PB03->Size = System::Drawing::Size(60, 60);
			this->PB03->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB03->TabIndex = 60;
			this->PB03->TabStop = false;
			// 
			// PB84
			// 
			this->PB84->BackColor = System::Drawing::Color::Transparent;
			this->PB84->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB84->Location = System::Drawing::Point(597, 365);
			this->PB84->Name = L"PB84";
			this->PB84->Size = System::Drawing::Size(60, 60);
			this->PB84->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB84->TabIndex = 59;
			this->PB84->TabStop = false;
			// 
			// PB74
			// 
			this->PB74->BackColor = System::Drawing::Color::Transparent;
			this->PB74->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB74->Location = System::Drawing::Point(525, 365);
			this->PB74->Name = L"PB74";
			this->PB74->Size = System::Drawing::Size(60, 60);
			this->PB74->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB74->TabIndex = 58;
			this->PB74->TabStop = false;
			// 
			// PB64
			// 
			this->PB64->BackColor = System::Drawing::Color::Transparent;
			this->PB64->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB64->Location = System::Drawing::Point(454, 365);
			this->PB64->Name = L"PB64";
			this->PB64->Size = System::Drawing::Size(60, 60);
			this->PB64->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB64->TabIndex = 57;
			this->PB64->TabStop = false;
			// 
			// PB54
			// 
			this->PB54->BackColor = System::Drawing::Color::Transparent;
			this->PB54->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB54->Location = System::Drawing::Point(382, 365);
			this->PB54->Name = L"PB54";
			this->PB54->Size = System::Drawing::Size(60, 60);
			this->PB54->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB54->TabIndex = 56;
			this->PB54->TabStop = false;
			// 
			// PB44
			// 
			this->PB44->BackColor = System::Drawing::Color::Transparent;
			this->PB44->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB44->Location = System::Drawing::Point(308, 365);
			this->PB44->Name = L"PB44";
			this->PB44->Size = System::Drawing::Size(60, 60);
			this->PB44->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB44->TabIndex = 55;
			this->PB44->TabStop = false;
			// 
			// PB34
			// 
			this->PB34->BackColor = System::Drawing::Color::Transparent;
			this->PB34->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB34->Location = System::Drawing::Point(236, 365);
			this->PB34->Name = L"PB34";
			this->PB34->Size = System::Drawing::Size(60, 60);
			this->PB34->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB34->TabIndex = 54;
			this->PB34->TabStop = false;
			// 
			// PB24
			// 
			this->PB24->BackColor = System::Drawing::Color::Transparent;
			this->PB24->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB24->Location = System::Drawing::Point(165, 365);
			this->PB24->Name = L"PB24";
			this->PB24->Size = System::Drawing::Size(60, 60);
			this->PB24->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB24->TabIndex = 53;
			this->PB24->TabStop = false;
			// 
			// PB14
			// 
			this->PB14->BackColor = System::Drawing::Color::Transparent;
			this->PB14->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB14->Location = System::Drawing::Point(93, 365);
			this->PB14->Name = L"PB14";
			this->PB14->Size = System::Drawing::Size(60, 60);
			this->PB14->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB14->TabIndex = 52;
			this->PB14->TabStop = false;
			// 
			// PB04
			// 
			this->PB04->BackColor = System::Drawing::Color::Transparent;
			this->PB04->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB04->Location = System::Drawing::Point(17, 365);
			this->PB04->Name = L"PB04";
			this->PB04->Size = System::Drawing::Size(60, 60);
			this->PB04->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB04->TabIndex = 51;
			this->PB04->TabStop = false;
			// 
			// PB85
			// 
			this->PB85->BackColor = System::Drawing::Color::Transparent;
			this->PB85->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB85->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"PB85.Image")));
			this->PB85->Location = System::Drawing::Point(597, 297);
			this->PB85->Name = L"PB85";
			this->PB85->Size = System::Drawing::Size(60, 60);
			this->PB85->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB85->TabIndex = 50;
			this->PB85->TabStop = false;
			this->PB85->Click += gcnew System::EventHandler(this, &ChessClientForm::PB85_Click);
			// 
			// PB75
			// 
			this->PB75->BackColor = System::Drawing::Color::Transparent;
			this->PB75->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB75->Location = System::Drawing::Point(525, 297);
			this->PB75->Name = L"PB75";
			this->PB75->Size = System::Drawing::Size(60, 60);
			this->PB75->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB75->TabIndex = 49;
			this->PB75->TabStop = false;
			// 
			// PB65
			// 
			this->PB65->BackColor = System::Drawing::Color::Transparent;
			this->PB65->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB65->Location = System::Drawing::Point(454, 297);
			this->PB65->Name = L"PB65";
			this->PB65->Size = System::Drawing::Size(60, 60);
			this->PB65->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB65->TabIndex = 48;
			this->PB65->TabStop = false;
			// 
			// PB55
			// 
			this->PB55->BackColor = System::Drawing::Color::Transparent;
			this->PB55->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB55->Location = System::Drawing::Point(382, 297);
			this->PB55->Name = L"PB55";
			this->PB55->Size = System::Drawing::Size(60, 60);
			this->PB55->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB55->TabIndex = 47;
			this->PB55->TabStop = false;
			// 
			// PB45
			// 
			this->PB45->BackColor = System::Drawing::Color::Transparent;
			this->PB45->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB45->Location = System::Drawing::Point(308, 297);
			this->PB45->Name = L"PB45";
			this->PB45->Size = System::Drawing::Size(60, 60);
			this->PB45->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB45->TabIndex = 46;
			this->PB45->TabStop = false;
			// 
			// PB35
			// 
			this->PB35->BackColor = System::Drawing::Color::Transparent;
			this->PB35->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB35->Location = System::Drawing::Point(236, 297);
			this->PB35->Name = L"PB35";
			this->PB35->Size = System::Drawing::Size(60, 60);
			this->PB35->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB35->TabIndex = 45;
			this->PB35->TabStop = false;
			// 
			// PB25
			// 
			this->PB25->BackColor = System::Drawing::Color::Transparent;
			this->PB25->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB25->Location = System::Drawing::Point(165, 297);
			this->PB25->Name = L"PB25";
			this->PB25->Size = System::Drawing::Size(60, 60);
			this->PB25->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB25->TabIndex = 44;
			this->PB25->TabStop = false;
			// 
			// PB15
			// 
			this->PB15->BackColor = System::Drawing::Color::Transparent;
			this->PB15->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB15->Location = System::Drawing::Point(93, 297);
			this->PB15->Name = L"PB15";
			this->PB15->Size = System::Drawing::Size(60, 60);
			this->PB15->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB15->TabIndex = 43;
			this->PB15->TabStop = false;
			// 
			// PB05
			// 
			this->PB05->BackColor = System::Drawing::Color::Transparent;
			this->PB05->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB05->Location = System::Drawing::Point(17, 297);
			this->PB05->Name = L"PB05";
			this->PB05->Size = System::Drawing::Size(60, 60);
			this->PB05->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB05->TabIndex = 42;
			this->PB05->TabStop = false;
			// 
			// PB86
			// 
			this->PB86->BackColor = System::Drawing::Color::Transparent;
			this->PB86->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB86->Location = System::Drawing::Point(597, 222);
			this->PB86->Name = L"PB86";
			this->PB86->Size = System::Drawing::Size(60, 60);
			this->PB86->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB86->TabIndex = 41;
			this->PB86->TabStop = false;
			// 
			// PB76
			// 
			this->PB76->BackColor = System::Drawing::Color::Transparent;
			this->PB76->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB76->Location = System::Drawing::Point(525, 222);
			this->PB76->Name = L"PB76";
			this->PB76->Size = System::Drawing::Size(60, 60);
			this->PB76->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB76->TabIndex = 40;
			this->PB76->TabStop = false;
			// 
			// PB66
			// 
			this->PB66->BackColor = System::Drawing::Color::Transparent;
			this->PB66->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB66->Location = System::Drawing::Point(454, 222);
			this->PB66->Name = L"PB66";
			this->PB66->Size = System::Drawing::Size(60, 60);
			this->PB66->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB66->TabIndex = 39;
			this->PB66->TabStop = false;
			// 
			// PB56
			// 
			this->PB56->BackColor = System::Drawing::Color::Transparent;
			this->PB56->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB56->Location = System::Drawing::Point(382, 222);
			this->PB56->Name = L"PB56";
			this->PB56->Size = System::Drawing::Size(60, 60);
			this->PB56->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB56->TabIndex = 38;
			this->PB56->TabStop = false;
			// 
			// PB46
			// 
			this->PB46->BackColor = System::Drawing::Color::Transparent;
			this->PB46->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB46->Location = System::Drawing::Point(308, 222);
			this->PB46->Name = L"PB46";
			this->PB46->Size = System::Drawing::Size(60, 60);
			this->PB46->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB46->TabIndex = 37;
			this->PB46->TabStop = false;
			// 
			// PB36
			// 
			this->PB36->BackColor = System::Drawing::Color::Transparent;
			this->PB36->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB36->Location = System::Drawing::Point(236, 222);
			this->PB36->Name = L"PB36";
			this->PB36->Size = System::Drawing::Size(60, 60);
			this->PB36->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB36->TabIndex = 36;
			this->PB36->TabStop = false;
			// 
			// PB26
			// 
			this->PB26->BackColor = System::Drawing::Color::Transparent;
			this->PB26->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB26->Location = System::Drawing::Point(165, 222);
			this->PB26->Name = L"PB26";
			this->PB26->Size = System::Drawing::Size(60, 60);
			this->PB26->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB26->TabIndex = 35;
			this->PB26->TabStop = false;
			// 
			// PB16
			// 
			this->PB16->BackColor = System::Drawing::Color::Transparent;
			this->PB16->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB16->Location = System::Drawing::Point(93, 222);
			this->PB16->Name = L"PB16";
			this->PB16->Size = System::Drawing::Size(60, 60);
			this->PB16->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB16->TabIndex = 34;
			this->PB16->TabStop = false;
			// 
			// PB06
			// 
			this->PB06->BackColor = System::Drawing::Color::Transparent;
			this->PB06->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB06->Location = System::Drawing::Point(17, 222);
			this->PB06->Name = L"PB06";
			this->PB06->Size = System::Drawing::Size(60, 60);
			this->PB06->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB06->TabIndex = 33;
			this->PB06->TabStop = false;
			// 
			// PB87
			// 
			this->PB87->BackColor = System::Drawing::Color::Transparent;
			this->PB87->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB87->Location = System::Drawing::Point(597, 155);
			this->PB87->Name = L"PB87";
			this->PB87->Size = System::Drawing::Size(60, 60);
			this->PB87->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB87->TabIndex = 32;
			this->PB87->TabStop = false;
			// 
			// PB77
			// 
			this->PB77->BackColor = System::Drawing::Color::Transparent;
			this->PB77->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB77->Location = System::Drawing::Point(525, 155);
			this->PB77->Name = L"PB77";
			this->PB77->Size = System::Drawing::Size(60, 60);
			this->PB77->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB77->TabIndex = 31;
			this->PB77->TabStop = false;
			// 
			// PB67
			// 
			this->PB67->BackColor = System::Drawing::Color::Transparent;
			this->PB67->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB67->Location = System::Drawing::Point(454, 155);
			this->PB67->Name = L"PB67";
			this->PB67->Size = System::Drawing::Size(60, 60);
			this->PB67->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB67->TabIndex = 30;
			this->PB67->TabStop = false;
			// 
			// PB57
			// 
			this->PB57->BackColor = System::Drawing::Color::Transparent;
			this->PB57->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB57->Location = System::Drawing::Point(382, 155);
			this->PB57->Name = L"PB57";
			this->PB57->Size = System::Drawing::Size(60, 60);
			this->PB57->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB57->TabIndex = 29;
			this->PB57->TabStop = false;
			// 
			// PB47
			// 
			this->PB47->BackColor = System::Drawing::Color::Transparent;
			this->PB47->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB47->Location = System::Drawing::Point(308, 155);
			this->PB47->Name = L"PB47";
			this->PB47->Size = System::Drawing::Size(60, 60);
			this->PB47->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB47->TabIndex = 28;
			this->PB47->TabStop = false;
			// 
			// PB37
			// 
			this->PB37->BackColor = System::Drawing::Color::Transparent;
			this->PB37->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB37->Location = System::Drawing::Point(236, 155);
			this->PB37->Name = L"PB37";
			this->PB37->Size = System::Drawing::Size(60, 60);
			this->PB37->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB37->TabIndex = 27;
			this->PB37->TabStop = false;
			// 
			// PB27
			// 
			this->PB27->BackColor = System::Drawing::Color::Transparent;
			this->PB27->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB27->Location = System::Drawing::Point(165, 155);
			this->PB27->Name = L"PB27";
			this->PB27->Size = System::Drawing::Size(60, 60);
			this->PB27->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB27->TabIndex = 26;
			this->PB27->TabStop = false;
			// 
			// PB17
			// 
			this->PB17->BackColor = System::Drawing::Color::Transparent;
			this->PB17->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB17->Location = System::Drawing::Point(93, 155);
			this->PB17->Name = L"PB17";
			this->PB17->Size = System::Drawing::Size(60, 60);
			this->PB17->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB17->TabIndex = 25;
			this->PB17->TabStop = false;
			// 
			// PB07
			// 
			this->PB07->BackColor = System::Drawing::Color::Transparent;
			this->PB07->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB07->Location = System::Drawing::Point(17, 155);
			this->PB07->Name = L"PB07";
			this->PB07->Size = System::Drawing::Size(60, 60);
			this->PB07->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB07->TabIndex = 24;
			this->PB07->TabStop = false;
			// 
			// PB88
			// 
			this->PB88->BackColor = System::Drawing::Color::Transparent;
			this->PB88->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB88->Location = System::Drawing::Point(597, 86);
			this->PB88->Name = L"PB88";
			this->PB88->Size = System::Drawing::Size(60, 60);
			this->PB88->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB88->TabIndex = 23;
			this->PB88->TabStop = false;
			// 
			// PB78
			// 
			this->PB78->BackColor = System::Drawing::Color::Transparent;
			this->PB78->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB78->Location = System::Drawing::Point(525, 86);
			this->PB78->Name = L"PB78";
			this->PB78->Size = System::Drawing::Size(60, 60);
			this->PB78->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB78->TabIndex = 22;
			this->PB78->TabStop = false;
			// 
			// PB68
			// 
			this->PB68->BackColor = System::Drawing::Color::Transparent;
			this->PB68->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB68->Location = System::Drawing::Point(454, 86);
			this->PB68->Name = L"PB68";
			this->PB68->Size = System::Drawing::Size(60, 60);
			this->PB68->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB68->TabIndex = 21;
			this->PB68->TabStop = false;
			// 
			// PB58
			// 
			this->PB58->BackColor = System::Drawing::Color::Transparent;
			this->PB58->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB58->Location = System::Drawing::Point(382, 86);
			this->PB58->Name = L"PB58";
			this->PB58->Size = System::Drawing::Size(60, 60);
			this->PB58->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB58->TabIndex = 20;
			this->PB58->TabStop = false;
			// 
			// PB48
			// 
			this->PB48->BackColor = System::Drawing::Color::Transparent;
			this->PB48->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB48->Location = System::Drawing::Point(308, 86);
			this->PB48->Name = L"PB48";
			this->PB48->Size = System::Drawing::Size(60, 60);
			this->PB48->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB48->TabIndex = 19;
			this->PB48->TabStop = false;
			// 
			// PB38
			// 
			this->PB38->BackColor = System::Drawing::Color::Transparent;
			this->PB38->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB38->Location = System::Drawing::Point(236, 86);
			this->PB38->Name = L"PB38";
			this->PB38->Size = System::Drawing::Size(60, 60);
			this->PB38->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB38->TabIndex = 18;
			this->PB38->TabStop = false;
			// 
			// PB28
			// 
			this->PB28->BackColor = System::Drawing::Color::Transparent;
			this->PB28->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB28->Location = System::Drawing::Point(165, 86);
			this->PB28->Name = L"PB28";
			this->PB28->Size = System::Drawing::Size(60, 60);
			this->PB28->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB28->TabIndex = 17;
			this->PB28->TabStop = false;
			// 
			// PB18
			// 
			this->PB18->BackColor = System::Drawing::Color::Transparent;
			this->PB18->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB18->Location = System::Drawing::Point(93, 86);
			this->PB18->Name = L"PB18";
			this->PB18->Size = System::Drawing::Size(60, 60);
			this->PB18->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB18->TabIndex = 16;
			this->PB18->TabStop = false;
			// 
			// PB08
			// 
			this->PB08->BackColor = System::Drawing::Color::Transparent;
			this->PB08->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB08->Location = System::Drawing::Point(17, 86);
			this->PB08->Name = L"PB08";
			this->PB08->Size = System::Drawing::Size(60, 60);
			this->PB08->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB08->TabIndex = 15;
			this->PB08->TabStop = false;
			// 
			// PB89
			// 
			this->PB89->BackColor = System::Drawing::Color::Transparent;
			this->PB89->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB89->Location = System::Drawing::Point(597, 20);
			this->PB89->Name = L"PB89";
			this->PB89->Size = System::Drawing::Size(60, 60);
			this->PB89->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB89->TabIndex = 14;
			this->PB89->TabStop = false;
			// 
			// PB79
			// 
			this->PB79->BackColor = System::Drawing::Color::Transparent;
			this->PB79->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB79->Location = System::Drawing::Point(525, 20);
			this->PB79->Name = L"PB79";
			this->PB79->Size = System::Drawing::Size(60, 60);
			this->PB79->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB79->TabIndex = 13;
			this->PB79->TabStop = false;
			// 
			// PB69
			// 
			this->PB69->BackColor = System::Drawing::Color::Transparent;
			this->PB69->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB69->Location = System::Drawing::Point(454, 20);
			this->PB69->Name = L"PB69";
			this->PB69->Size = System::Drawing::Size(60, 60);
			this->PB69->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB69->TabIndex = 12;
			this->PB69->TabStop = false;
			// 
			// PB59
			// 
			this->PB59->BackColor = System::Drawing::Color::Transparent;
			this->PB59->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB59->Location = System::Drawing::Point(382, 20);
			this->PB59->Name = L"PB59";
			this->PB59->Size = System::Drawing::Size(60, 60);
			this->PB59->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB59->TabIndex = 11;
			this->PB59->TabStop = false;
			// 
			// PB49
			// 
			this->PB49->BackColor = System::Drawing::Color::Transparent;
			this->PB49->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB49->Location = System::Drawing::Point(308, 20);
			this->PB49->Name = L"PB49";
			this->PB49->Size = System::Drawing::Size(60, 60);
			this->PB49->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB49->TabIndex = 10;
			this->PB49->TabStop = false;
			// 
			// PB39
			// 
			this->PB39->BackColor = System::Drawing::Color::Transparent;
			this->PB39->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB39->Location = System::Drawing::Point(236, 20);
			this->PB39->Name = L"PB39";
			this->PB39->Size = System::Drawing::Size(60, 60);
			this->PB39->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB39->TabIndex = 9;
			this->PB39->TabStop = false;
			// 
			// PB29
			// 
			this->PB29->BackColor = System::Drawing::Color::Transparent;
			this->PB29->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB29->Location = System::Drawing::Point(165, 20);
			this->PB29->Name = L"PB29";
			this->PB29->Size = System::Drawing::Size(60, 60);
			this->PB29->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB29->TabIndex = 8;
			this->PB29->TabStop = false;
			// 
			// PB19
			// 
			this->PB19->BackColor = System::Drawing::Color::Transparent;
			this->PB19->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->PB19->Location = System::Drawing::Point(93, 20);
			this->PB19->Name = L"PB19";
			this->PB19->Size = System::Drawing::Size(60, 60);
			this->PB19->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->PB19->TabIndex = 7;
			this->PB19->TabStop = false;
			// 
			// ChessClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1084, 811);
			this->Controls->Add(this->Chessboardpanel);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->send);
			this->DoubleBuffered = true;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ChessClientForm";
			this->Text = L"ChessClientForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB09))->EndInit();
			this->Chessboardpanel->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB80))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB70))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB60))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB50))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB40))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB30))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB20))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB00))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB81))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB71))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB61))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB51))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB41))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB31))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB21))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB11))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB01))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB82))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB72))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB62))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB52))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB42))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB32))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB22))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB12))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB02))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB83))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB73))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB63))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB53))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB43))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB33))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB23))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB13))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB03))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB84))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB74))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB64))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB54))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB44))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB34))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB24))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB14))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB04))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB85))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB75))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB65))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB55))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB45))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB35))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB25))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB15))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB05))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB86))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB76))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB66))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB56))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB46))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB36))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB26))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB16))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB06))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB87))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB77))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB67))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB57))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB47))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB37))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB27))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB17))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB07))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB88))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB78))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB68))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB58))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB48))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB38))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB28))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB18))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB08))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB89))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB79))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB69))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB59))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB49))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB39))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB29))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PB19))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	delegate void MyCallback(String^ message);
	
	public: void UpdataTB(String^ message)
	{
		textBox2->Clear();
		textBox1->Text += Environment::NewLine + message;
	}

	private: void ReceiveCallback(IAsyncResult^ AR)
	{
		try
		{
			int received = clientSocket->EndReceive(AR);

			if (received == 0)
			{
				return;
			}


			String^ message = Encoding::ASCII->GetString(buffer);
			buffer = gcnew array<Byte>(clientSocket->ReceiveBufferSize);
			MyCallback^ callback = gcnew MyCallback(this, &ChessClientForm::UpdataTB);
			//callback(message);
			this->Invoke(callback, message);
			
			

			clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessClientForm::ReceiveCallback), nullptr);
		}
		// Avoid Pokemon exception handling in cases like these.
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
	}

	private: void ConnectCallback(IAsyncResult^ AR)
	{
		try
		{
			clientSocket->EndConnect(AR);
			UpdateControlStates(true);
			buffer = gcnew array<Byte>(clientSocket->ReceiveBufferSize);
			clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessClientForm::ReceiveCallback), nullptr);
		}
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
	}

	private: void SendCallback(IAsyncResult^ AR)
	{
		try
		{
			clientSocket->EndSend(AR);
		}
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
	}

	private:static void ShowErrorDialog(String^ message)
	{
		MessageBox::Show(message, Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	
	private: void UpdateControlStates(bool toggle)
	{
		/*Action<string> messageTarget;
		this->Invoke(delegate^ ()  
		{
			buttonSend.Enabled = toggle;
			buttonConnect.Enabled = !toggle;
			labelIP.Visible = textBoxAddress.Visible = !toggle;
		});*/
	}

	private: System::Void send_Click(System::Object^  sender, System::EventArgs^  e) {
		array<unsigned char>^ sendData = Encoding::ASCII->GetBytes(textBox2->Text);


		MyCallback^ callback = gcnew MyCallback(this, &ChessClientForm::UpdataTB);
		
		this->Invoke(callback, textBox2->Text);

		clientSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessClientForm::SendCallback), nullptr);
		//clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessClientForm::ReceiveCallback), nullptr);


	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		try
		{
			clientSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			// Connect to the specified host.
			
			auto endPoint = gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 1234);
			clientSocket->BeginConnect(endPoint, gcnew AsyncCallback(this, &ChessClientForm::ConnectCallback), nullptr);
		}
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}

	}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void ChessboardPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void pictureBox1_MouseEnter(System::Object^  sender, System::EventArgs^  e) {


}




private: System::Void PB00_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	PictureBox^ PicBox = (PictureBox^)sender;
	MouseDown = PicBox;

	Image^ img = PicBox->Image;
	if (img == nullptr) return;
	if (DoDragDrop(img, DragDropEffects::Move) == DragDropEffects::Move) {
		PicBox->Image = nullptr;
	}
}
private: System::Void PB00_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	PictureBox^ PicBox = (PictureBox^)sender;
	if (PicBox != MouseDown)
	{
		if (e->Data->GetDataPresent(DataFormats::Bitmap))
			e->Effect = DragDropEffects::Move;
	}
}
private: System::Void PB00_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
	PictureBox^ PicBox = (PictureBox^)sender;

	if (PicBox != MouseDown)
	{
		auto bmp = (Bitmap^)e->Data->GetData(DataFormats::Bitmap);
		PicBox->Image = bmp;
	}
}
	
private: System::Void PB85_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("aasdf");
}
};
}
