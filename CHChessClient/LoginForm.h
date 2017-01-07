#pragma once
#include "ChineseChessGame.h"
#include "ChessClientForm.h"
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
	/// LoginForm 的摘要
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:
		LoginForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  LoginBT;
	protected:

	private: System::Windows::Forms::TextBox^  LoginTB;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		Socket^ clientSocket;
		String^ Name;
		array<Byte>^ buffer;
		ChessClientForm^ clientform;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->LoginBT = (gcnew System::Windows::Forms::Button());
			this->LoginTB = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label1->Location = System::Drawing::Point(199, 133);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 61);
			this->label1->TabIndex = 0;
			this->label1->Text = L"名字";
			// 
			// LoginBT
			// 
			this->LoginBT->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LoginBT->Location = System::Drawing::Point(184, 285);
			this->LoginBT->Name = L"LoginBT";
			this->LoginBT->Size = System::Drawing::Size(153, 91);
			this->LoginBT->TabIndex = 1;
			this->LoginBT->Text = L"登入";
			this->LoginBT->UseVisualStyleBackColor = true;
			this->LoginBT->Click += gcnew System::EventHandler(this, &LoginForm::LoginBT_Click);
			// 
			// LoginTB
			// 
			this->LoginTB->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->LoginTB->Location = System::Drawing::Point(184, 211);
			this->LoginTB->Name = L"LoginTB";
			this->LoginTB->Size = System::Drawing::Size(153, 54);
			this->LoginTB->TabIndex = 2;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label2->Location = System::Drawing::Point(106, 49);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(315, 61);
			this->label2->TabIndex = 3;
			this->label2->Text = L"歡迎進入遊戲";
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(523, 420);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->LoginTB);
			this->Controls->Add(this->LoginBT);
			this->Controls->Add(this->label1);
			this->Name = L"LoginForm";
			this->Text = L"LoginForm";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &LoginForm::LoginForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &LoginForm::LoginForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:static void ShowErrorDialog(String^ message)
	{
		MessageBox::Show(message, Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
	}

	private: System::Void LoginBT_Click(System::Object^  sender, System::EventArgs^  e) {

		if (LoginTB->Text != "") {
			try
			{
				clientSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
				// Connect to the specified host.
				auto endPoint = gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 1234);
				clientSocket->BeginConnect(endPoint, gcnew AsyncCallback(this, &LoginForm::ConnectCallback), clientSocket);

			/*	for (int i = 0;i<2;i++) {
					if (i==0) {
						array<Byte>^ buffer2=gcnew array<Byte>(1024);
						clientSocket->BeginSend(buffer2, 0, buffer2->Length, SocketFlags::None, gcnew AsyncCallback(this, &LoginForm::SendCallback), clientSocket);
						
					}
					else if (i == 1) {*/

					/*List<Byte>^ byteMessageList = gcnew List<Byte>();

					byteMessageList->AddRange(BitConverter::GetBytes((short)10));
					byteMessageList->AddRange(BitConverter::GetBytes(LoginTB->Text->Length));
					byteMessageList->AddRange(Encoding::ASCII->GetBytes(LoginTB->Text));

					array<unsigned char>^ sendData = byteMessageList->ToArray();
					

					clientSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &LoginForm::SendCallback), clientSocket);*/
					/*}
				}*/

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
		else {
			MessageBox::Show("欄位不得為空");
		}
	}

	delegate void MyCallback2(Player^, Player^, Socket^, array<Byte>^);
	

	public: void GameStart(Player^ player1, Player^ player2, Socket^ clientSocke , array<Byte>^ buffer) {
		clientform = gcnew ChessClientForm(player1, player2, clientSocket, buffer);

		clientform->FormClosed += gcnew FormClosedEventHandler(this, &LoginForm::LoginForm_FormClosed);//this, &ChessServerForm::Sendbutton_Click

		clientform->Show();//開啟子視窗
		this->Hide();//隱藏父視窗
					 //this->Visible = false;
		MessageBox::Show("歡迎登入!" + LoginTB->Text);
	}


	private: void ReceiveCallback(IAsyncResult^ AR)
	{
		Socket^ current = (Socket^)AR->AsyncState;


		try
		{
			int received = clientSocket->EndReceive(AR);

			if (received == 0)
			{
				return;
			}
			int code = BitConverter::ToInt16(buffer, 0);
			if (code == 10) {

				int MessageLength1 = BitConverter::ToInt32(buffer, 2);
				String^ name1 = Encoding::ASCII->GetString(buffer, 6, MessageLength1);
				PlayerState temp1=(PlayerState)BitConverter::ToInt32(buffer, 6 + MessageLength1);


				int MessageLength2 = BitConverter::ToInt32(buffer, 10 + MessageLength1);
				String^ name2 = Encoding::ASCII->GetString(buffer, 14 + MessageLength1, MessageLength2);
				PlayerState temp2 = (PlayerState)BitConverter::ToInt32(buffer, 14 + MessageLength1+ MessageLength2);


				ChessColor tempcolor = (temp1 == PlayerState::Player1 ? ChessColor::Blue: ChessColor::Green);
				ChessColor tempcolor2 = (temp2 == PlayerState::Player1 ? ChessColor::Blue : ChessColor::Green);


				Player^ player1 = gcnew Player(name1, nullptr, temp1, tempcolor, temp1 == PlayerState::Player1);
				Player^ player2 = gcnew Player(name2, nullptr, temp2, tempcolor2, temp2 == PlayerState::Player1);

				MyCallback2^ callback2 = gcnew MyCallback2(this, &LoginForm::GameStart);
				
				this->Invoke(callback2,player1,player2,clientSocket,buffer);

			}

			
			


			buffer = gcnew array<Byte>(clientSocket->ReceiveBufferSize);
			clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &LoginForm::ReceiveCallback), clientSocket);
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
			buffer = gcnew array<Byte>(clientSocket->ReceiveBufferSize);
			clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &LoginForm::ReceiveCallback), clientSocket);


			//receive 完傳送

			List<Byte>^ byteMessageList = gcnew List<Byte>();

			byteMessageList->AddRange(BitConverter::GetBytes((short)10));
			byteMessageList->AddRange(BitConverter::GetBytes(LoginTB->Text->Length));
			byteMessageList->AddRange(Encoding::ASCII->GetBytes(LoginTB->Text));

			array<unsigned char>^ sendData = byteMessageList->ToArray();


			clientSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &LoginForm::SendCallback), clientSocket);




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

	private: System::Void LoginForm_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
		this->Close();		
	}

	private: System::Void LoginForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
