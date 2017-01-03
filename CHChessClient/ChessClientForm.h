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

		Socket^ clientSocket;
		String^ Name;
		array<Byte>^ buffer;
	private: System::Windows::Forms::Button^  send;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;




		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->send = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// send
			// 
			this->send->Location = System::Drawing::Point(256, 297);
			this->send->Name = L"send";
			this->send->Size = System::Drawing::Size(75, 23);
			this->send->TabIndex = 0;
			this->send->Text = L"send";
			this->send->UseVisualStyleBackColor = true;
			this->send->Click += gcnew System::EventHandler(this, &ChessClientForm::send_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(272, 234);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ChessClientForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 48);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(208, 230);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &ChessClientForm::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(28, 297);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 22);
			this->textBox2->TabIndex = 3;
			// 
			// ChessClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(427, 395);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->send);
			this->Name = L"ChessClientForm";
			this->Text = L"ChessClientForm";
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
};
}
