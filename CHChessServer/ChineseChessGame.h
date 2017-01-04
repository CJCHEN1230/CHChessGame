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

	public ref class Player
	{
	public:
		

	private:
		
		String Name;
		Socket^ socket;

	};
	public ref class Game
	{
	public: 
		

	private:
		String Winner;


	};


	public ref class Chessman abstract
	{
	private:
		String ^ Name;

	public:


		enum class Chessman : int {
			King,
			Advisors,
			Elephants,
			Rooks,
			Knights,
			Cannons,
			soldiers
		};
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
}