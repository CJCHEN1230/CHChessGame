#pragma once
#include "ChineseChessGame.h"
#include <string>
#include <iostream>
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


	/// <summary>
	/// ChessServerForm ���K�n
	/// </summary>

	

	public ref class ChessServerForm : public System::Windows::Forms::Form
	{
	public:
		ChessServerForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
			
			
			StartServer();
		}

	protected:
		/// <summary>
		/// �M������ϥΤ����귽�C
		/// </summary>
		~ChessServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  Sendbutton;
	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		array<Byte>^ buffer;
		List<Socket^>^ clientSockets;// = gcnew List<String^>();	
		List<array<Byte>^>^ bufferList;
		Socket^ serverSocket;
		Socket^ clientSocket;
		Player^ player1;
		Player^ player2;
		int namelength;
		String^ name1;
		int namelength2;
		String^ name2;


	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;

		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			this->Sendbutton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// Sendbutton
			// 
			this->Sendbutton->Location = System::Drawing::Point(374, 298);
			this->Sendbutton->Name = L"Sendbutton";
			this->Sendbutton->Size = System::Drawing::Size(75, 23);
			this->Sendbutton->TabIndex = 0;
			this->Sendbutton->Text = L"Send";
			this->Sendbutton->UseVisualStyleBackColor = true;
			this->Sendbutton->Click += gcnew System::EventHandler(this, &ChessServerForm::Sendbutton_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(167, 27);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(230, 244);
			this->textBox1->TabIndex = 3;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(213, 298);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 4;
			// 
			// ChessServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(511, 416);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->Sendbutton);
			this->Name = L"ChessServerForm";
			this->Text = L"ChessServerForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//�i��U�ػPserver����l�Ƹj�w
	private: System::Void StartServer() {
		
		try
		{
			clientSockets = gcnew List<Socket^>();
			bufferList = gcnew List<array<Byte>^>();
			serverSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			serverSocket->Bind(gcnew IPEndPoint(IPAddress::Any, 1234));//IPEndPoint���@�өw�q���㪺server��m�A�]�tip��port
			serverSocket->Listen(10);//�@�ӵ��ݳs�u��queue���סA���O�u��10�ӳs�u
			serverSocket->BeginAccept(gcnew AsyncCallback(this, &ChessServerForm::AcceptCallback), serverSocket); //AsyncCallback(AcceptCallback),�@���s���W�᪺�^�ը�Ƭ�AcceptCallback�C��t�νեγo�Ө�ƮɡA�۰ʽᤩ����J�ѼƬ�IAsyncResult�����ܶqar�C
		}
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
	
	};
	
	private:static void ShowErrorDialog(String^ message)
	{
		MessageBox::Show(message, Application::ProductName, MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	
	private: void AcceptCallback(IAsyncResult^ AR)
	{
		try
		{
			
			clientSocket = serverSocket->EndAccept(AR); //�����s���A�ê�^���ɪ�socket�q�D
			clientSockets->Add(clientSocket);
			buffer =gcnew array<Byte>(clientSocket->ReceiveBufferSize);
			bufferList->Add(buffer);
			String^ temp = "Hello Client";
			List<Byte>^ byteMessageList = gcnew List<Byte>();
			byteMessageList->AddRange(BitConverter::GetBytes((Int16)1));
			byteMessageList->AddRange(BitConverter::GetBytes(temp->Length));
			byteMessageList->AddRange(Encoding::ASCII->GetBytes(temp));

			array<unsigned char>^ sendData = byteMessageList->ToArray();
			clientSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), clientSocket);			
			clientSocket->BeginReceive(buffer, 0, buffer->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::ReceiveCallback), clientSocket);			
			serverSocket->BeginAccept(gcnew AsyncCallback(this, &ChessServerForm::AcceptCallback), serverSocket);
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
	//�]�wSendCallback
	private: void SendCallback(IAsyncResult^ AR)
	{
		Socket^ current = (Socket^)AR->AsyncState;
		
		try
		{
			current->EndSend(AR);//�פ�Send
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

	delegate void MyCallback(String^ message);

	public: void UpdataTB(String^ message)
	{
		
		textBox2->Clear();
		textBox1->Text += message+ Environment::NewLine ;
		
	}

	private: void ReceiveCallback(IAsyncResult^ AR)
	{

		Socket^ current = (Socket^)AR->AsyncState;

		//int index = clientSockets->FindIndex(current->);
		try
		{
			
			int received = current->EndReceive(AR);// �����D�P�BŪ���A�æ^�Ǧ���X��Byte

			
			if (received == 0)
			{
				return;
			}
			int index;
			index=clientSockets->IndexOf(current);


			int code = BitConverter::ToInt16(bufferList[index], 0);
			MyCallback^ callback = gcnew MyCallback(this, &ChessServerForm::UpdataTB);


			this->BeginInvoke(callback, "�ثe���ެ�" + index + "�H�s�u");
			
			

			this->BeginInvoke(callback, "�ثe��"+ clientSockets->Count+"�H�s�u");

			if (code == 10 &&clientSockets->Count<3) {

				if (clientSockets->Count == 1) {					
					namelength = BitConverter::ToInt32(bufferList[0], 2);
					name1=Encoding::ASCII->GetString(bufferList[0], 6, namelength);

					
				}
				if (clientSockets->Count == 2) {
					int temp;
					namelength2 = BitConverter::ToInt32(bufferList[1], 2);
					name2 = Encoding::ASCII->GetString(bufferList[1], 6, namelength2);
					String^ temp222;
					temp = namelength2;
					temp222 = name2;


					List<Byte>^ byteMessageList = gcnew List<Byte>();
					byteMessageList->AddRange(BitConverter::GetBytes((short)10));
					byteMessageList->AddRange(BitConverter::GetBytes(namelength));
					byteMessageList->AddRange(Encoding::ASCII->GetBytes(name1));
					byteMessageList->AddRange(BitConverter::GetBytes((int)PlayerState::Player1));					
					byteMessageList->AddRange(BitConverter::GetBytes(namelength2));
					byteMessageList->AddRange(Encoding::ASCII->GetBytes(name2));
					byteMessageList->AddRange(BitConverter::GetBytes((int)PlayerState::Player2));
					array<unsigned char>^ sendData = byteMessageList->ToArray();					
					clientSockets[0]->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), clientSockets[0]);

					byteMessageList = gcnew List<Byte>();
					byteMessageList->AddRange(BitConverter::GetBytes((short)10));
					byteMessageList->AddRange(BitConverter::GetBytes(namelength2));
					byteMessageList->AddRange(Encoding::ASCII->GetBytes(name2));
					byteMessageList->AddRange(BitConverter::GetBytes((int)PlayerState::Player2));
					byteMessageList->AddRange(BitConverter::GetBytes(namelength));
					byteMessageList->AddRange(Encoding::ASCII->GetBytes(name1));
					byteMessageList->AddRange(BitConverter::GetBytes((int)PlayerState::Player1));
					sendData = byteMessageList->ToArray();


					clientSockets[1]->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), clientSockets[1]);

				}






			}



			if (code == 1) {
				int MessageLength = BitConverter::ToInt32(bufferList[index], 2);
				String^ message = Encoding::ASCII->GetString(bufferList[index], 6, MessageLength);
				MyCallback^ callback = gcnew MyCallback(this, &ChessServerForm::UpdataTB);
				this->Invoke(callback, message);


				List<Byte>^ byteMessageList = gcnew List<Byte>();
				byteMessageList->AddRange(BitConverter::GetBytes((short)1));
				byteMessageList->AddRange(BitConverter::GetBytes(MessageLength));
				byteMessageList->AddRange(Encoding::ASCII->GetBytes(message));

				array<unsigned char>^ sendData = byteMessageList->ToArray();

				
				
				for each(Socket^ EachSocket in clientSockets) {
					if (current != EachSocket) {
						EachSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), EachSocket/*nullptr*/);
					}
				}
			}
			/*String^ message = Encoding::ASCII->GetString(buffer);

			array<unsigned char>^ sendData = Encoding::ASCII->GetBytes(message);

			
			MyCallback^ callback = gcnew MyCallback(this, &ChessServerForm::UpdataTB);
			
			this->Invoke(callback, message);*/
			
			

			
			
			bufferList[index] = gcnew array<Byte>(current->ReceiveBufferSize);
			current->BeginReceive(bufferList[index], 0, bufferList[index]->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::ReceiveCallback), current);
			
		}
		catch (SocketException^ ex)
		{
			ShowErrorDialog(ex->Message);
			current->Close();
			clientSockets->Remove(current);
			return;
		}
		catch (ObjectDisposedException^ ex)
		{
			ShowErrorDialog(ex->Message);
		}
	}

	private: System::Void Sendbutton_Click(System::Object^  sender, System::EventArgs^  e) {
		

		List<Byte>^ byteMessageList = gcnew List<Byte>();
		byteMessageList->AddRange(BitConverter::GetBytes((Int16)1));
		byteMessageList->AddRange(BitConverter::GetBytes(textBox2->Text->Length));
		byteMessageList->AddRange(Encoding::ASCII->GetBytes(textBox2->Text));

		array<unsigned char>^ sendData = byteMessageList->ToArray();

		MyCallback^ callback = gcnew MyCallback(this, &ChessServerForm::UpdataTB);
	
		this->BeginInvoke(callback, textBox2->Text);

		//clientSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), nullptr);
		for each(Socket^ EachSocket in clientSockets){
			//�̫�@�ӰѼƤ��i��nullptr�A��]�����M����Ƭݰ_�Ӥw�g���T�w����client�I�s���A
			//���O�̭���callback function�ä����D�O����client�A�]�����i��P�ɦh�Өƥ�Ĳ�o��callback function�A�ҥH�n�w�q���A�ӧi�Dcallback�{�b�O����client
			EachSocket->BeginSend(sendData, 0, sendData->Length, SocketFlags::None, gcnew AsyncCallback(this, &ChessServerForm::SendCallback), EachSocket/*nullptr*/);
																																				
		}

	}
	};
}
