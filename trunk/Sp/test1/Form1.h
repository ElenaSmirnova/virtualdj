


#pragma once
#include <string>




const int SizeFormH = 6;
const int SizeFormW = 13;


namespace test1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int const NumberTabs = 2;
	int const NumberGraphics = 2;
	int const arraySise = 5;
	int _array[arraySise];
    
	public ref class hScrollBar1 : public System::Windows::Forms::HScrollBar
	{
	public:
		hScrollBar1(int width, int height){
		//InitializeScroll();
		Size = System::Drawing::Size(width, 10);
		Location = System::Drawing::Point(0, height-10);

		}

		//void pagePaint(Object^ /*sender*/, PaintEventArgs^ e);
		//void MouseMove(Object^/*sender*/, MouseEventArgs^ e);
		 virtual void OnSizeChanged (EventArgs^ e) override
		{
            
			Invalidate();
			HScrollBar::OnSizeChanged(e);
		}

		// void InitializeScroll(){
			 //this->Paint += gcnew System::Windows::Forms::PaintEventHandler( this, &hScrollBar1::pagePaint );

		 //}
		
	};
	public ref class Form1 : public System::Windows::Forms::Form
	{
    

			

	public:
		Form1(int NumberTabs)
		{
           
			tabPage = gcnew array<System::Windows::Forms::TabPage^>(NumberTabs);
            InitializeComponent(NumberTabs, arraySise);
            
		}
        


		void pagePaint(Object^ /*sender*/, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;     
			_array[0] = 40; _array[1] = 36; _array[2] = 56; _array[3] = 45; _array[4] = 80;
			int const indent = 30;
			int k = indent;
			int w,h;
			Rectangle rect = e->ClipRectangle;
			w = (rect.Width);
			h = (rect.Height)/NumberGraphics;
			g->FillRectangle(Brushes::White, 0, 0, w, h);
		
			
			// to make a calculation coefficient of stretching and pressing
			float koefW = w/arraySise;
			float koefH;
			int max = _array[0];
			for (int i = 1; i < arraySise; i++)
			{
				if (_array[i] > max)
				{
					max = _array[i];
				}
			}
			if (max != 0)
			{
				koefH = (h-h/20)/max;
			}

            // draw graphics
			for (int j = 1; j < arraySise; j++)
			{	
				g->FillEllipse(Brushes::Black, Rectangle((j+k),(h-koefH*_array[j-1]),4,4));
				g->DrawLine(Pens::Black, Point((j+k),(h-koefH*_array[j-1])), Point((j+k+koefW), (h-koefH*_array[j])));
				k = k+koefW;
			}

			// draw coordinate line
			for ( int counter = 1; counter <= NumberGraphics; counter++)
			{
				g->DrawLine(Pens::Black, Point(indent, h*counter-indent), Point(indent,h*(counter-1)+10));
				g->DrawLine(Pens::Black, Point(indent, h*counter-indent), Point(w-10,h*counter-indent));

			// draw direction of coordinate line
				g->DrawLine(Pens::Black, Point(w-10-5, h*counter-indent-2), Point(w-10,h*counter-indent));
				g->DrawLine(Pens::Black, Point(w-10-5, h*counter-indent+2), Point(w-10,h*counter-indent));
				g->DrawLine(Pens::Black, Point(indent-2,h*(counter-1)+10+5), Point(indent,h*(counter-1)+10));
				g->DrawLine(Pens::Black, Point(indent+2,h*(counter-1)+10+5), Point(indent,h*(counter-1)+10));
			}
			
			//output width
			char str ;
			itoa(w, &str, 10);
			String^ str2 = gcnew String(&str);
			String^ drawString = "width " + str2;
			
			System::Drawing::Font^ drawFont = gcnew System::Drawing::Font( "Arial",10 );
			SolidBrush^ drawBrush = gcnew SolidBrush( Color::Black );
			Point drawPoint = Point(w-w/5,0);
			e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   
			
			//output height
			itoa(h, &str, 10);
			str2 = gcnew String(&str);
			drawString = " height" + str2;
			
			drawPoint = Point(w-w/5,15);
			e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   

			// signature of value
			for(int i = 1; i < arraySise; i++)
			{
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font( "Arial",7 );
				g->DrawLine(Pens::Black, Point(indent+i*koefW,h-(indent-2)), Point(indent+i*koefW, h-(indent+2)));
				itoa(i, &str, 10);
				str2 = gcnew String(&str);
				drawString = str2;
				drawPoint = Point(indent+i*koefW, h-(indent));
				e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   

				g->DrawLine(Pens::Black, Point(indent-2, h-_array[i]*koefH), Point(indent+2, h-_array[i]*koefH));
				itoa(_array[i], &str, 10);
				str2 = gcnew String(&str);
				drawString = str2;
				drawPoint = Point(indent-20, h-_array[i]*koefH);
				e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   
			}

			/*System::Drawing::Size preferredSize = tabPage[0]->ClientSize::get();
          
			hScrollBar1^ hScrollBar = (gcnew hScrollBar1(preferredSize.Width,preferredSize.Height));
           
            this->tabPage[0]->Controls->Add(hScrollBar);*/
				
			//	hScrollBar->Size = System::Drawing::Size(w, 5);
			//	hScrollBar->Location = System::Drawing::Point(0, h*NumberGraphics - 5);
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

        virtual void OnSizeChanged (EventArgs^ e) override
		{
            
			
            Invalidate();
			Form::OnSizeChanged(e);
		}


	protected: 
	


	private: PrintDialog^  printDialog1;
	private: TabControl^  tabControl1;
	private: array<TabPage^> ^ tabPage;
	private: hScrollBar1^  hScrollBar;
	
	    

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
    

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(int NumberTabs, int arraySise)
		{
			int i;
			this->printDialog1 = (gcnew System::Windows::Forms::PrintDialog());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			
			//hScrollBar1^ hScrollBar = (gcnew hScrollBar1(Drawing::Size::Width,Drawing::Size::Height));
			
			for (i = 0; i < NumberTabs; i++)
			{
				this->tabPage[i] = (gcnew System::Windows::Forms::TabPage());
			};
            

			
			this->tabControl1->SuspendLayout();
			this->SuspendLayout();


			// 
			// printDialog1
			// 
			this->printDialog1->UseEXDialog = true;
            
			// 
			// tabControl1
			// 


			this->tabPage[0]->Paint += gcnew System::Windows::Forms::PaintEventHandler( this, &Form1::pagePaint );
			
			for(i = 0; i < NumberTabs; i++)
			{
				this->tabControl1->Controls->Add(this->tabPage[i]);
			};
            
            
			this->tabControl1->Location = System::Drawing::Point(1, 1);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1700, 1350);
			this->tabControl1->TabIndex = 0;

            
			
			for(i = 0; i < NumberTabs; i++)
			{
				this->tabPage[i]->Location = System::Drawing::Point(4, 22);
				this->tabPage[i]->Name = L"myTab";
				this->tabPage[i]->Padding = System::Windows::Forms::Padding(3);
				this->tabPage[i]->Size = System::Drawing::Size(284, 238);
				this->tabPage[i]->TabIndex = 0;
				this->tabPage[i]->Text = "myTab "+ (char)(i+1);
				this->tabPage[i]->UseVisualStyleBackColor = true;
				this->tabPage[i]->Click += gcnew System::EventHandler(this, &Form1::tabPage1_Click);
			};

			//drawing hScrollBar with the size of the client part of the window
			System::Drawing::Size preferredSize = tabPage[0]->ClientSize::get();
          
			hScrollBar1^ hScrollBar = (gcnew hScrollBar1(preferredSize.Width,preferredSize.Height));
           
            this->tabPage[0]->Controls->Add(hScrollBar);
			
			// Form1
			 
			this->AutoScaleDimensions = System::Drawing::SizeF(SizeFormH, SizeFormW);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->tabControl1);
            
            
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void tabPage1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load_1(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void Form1_Load_2(System::Object^  sender, System::EventArgs^  e) {
		 }

private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load_3(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void Form1_Load_4(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}


