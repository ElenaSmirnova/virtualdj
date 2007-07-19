#pragma once
#include "resource.h"



namespace sound_processor {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SpForm
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>

	int const NumberTabs = 2;
	int const NumberGraphics = 2;
	const int SizeFormH = 6;
	const int SizeFormW = 13;
	public ref class Form1 : public System::Windows::Forms::Form
	{
    	public:
			SoundBuffer *buffer;
			SoundBuffer *exampleBuffer;
			

		Form1(SoundBuffer *buffer, SoundBuffer *exampleBuffer)
		{
			this->buffer = buffer;
			this->exampleBuffer = exampleBuffer;
          	tabPage = gcnew array<System::Windows::Forms::TabPage^>(NumberTabs);
            InitializeComponent(NumberTabs,buffer->getLength());
        }

		void pagePaint(Object^ sender, PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;  
			int const indent = 30;
			double k = indent;
			double w = 0, h = 0;
			System::Drawing::Rectangle rect = e->ClipRectangle;
			w = (rect.Width);
			h = (rect.Height)/NumberGraphics;
			g->FillRectangle(Brushes::White, 0, 0, w, h);
			
			// to make a calculation coefficient of stretching and pressing
			//double koefW = w/double(buffer->getLength());
			double koefW = 1;
			double koefH;
			int max = buffer->buff[0][0];
			for (int i = 1; i < buffer->getLength(); i++)
			{
				if (buffer->buff[i][0] > max)
				{
					max = buffer->buff[i][0];
				}
			}
			if (max != 0)
			{
				koefH = (h-h/20)/double(max*2);
			}

            // draw graphics
			for (int j = 1; j < buffer->getLength(); j++)
			{	
				g->FillEllipse(Brushes::Black, System::Drawing::Rectangle(k,h-indent-(h-indent-10)/2-koefH*buffer->buff[j-1][0],4,4));
				g->DrawLine(Pens::Black, Point(k,h-indent-(h-indent-10)/2-koefH*buffer->buff[j-1][0]), Point(k+koefW, h-indent-(h-indent-10)/2-koefH*buffer->buff[j][0]));
				k = k+koefW;
			}

			// draw coordinate line
			for ( int counter = 1; counter <= NumberGraphics; counter++)
			{
				g->DrawLine(Pens::Black, Point(indent, h*counter-indent), Point(indent,h*(counter-1)+10));
				g->DrawLine(Pens::Black, Point(indent, h*counter-indent-(h-indent-10)/2), Point(w-10,h*counter-indent-(h-indent-10)/2));

			// draw direction of coordinate line
				g->DrawLine(Pens::Black, Point(w-10-5, h*counter-indent-(h-indent-10)/2-2), Point(w-10,h*counter-(h-indent-10)/2-indent));
				g->DrawLine(Pens::Black, Point(w-10-5, h*counter-indent-(h-indent-10)/2+2), Point(w-10,h*counter-indent-(h-indent-10)/2));
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
			drawString = "height " + str2;
			
			drawPoint = Point(w-w/5,15);
			e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   

			// signature of value
			for(int i = 1; i < buffer->getLength(); i++)
			{
				System::Drawing::Font^ drawFont = gcnew System::Drawing::Font( "Arial",7 );
				g->DrawLine(Pens::Black, Point(indent+i*koefW,h-(indent-2)-(h-indent-10)/2), Point(indent+i*koefW, h-(indent+2)-(h-indent-10)/2));
				itoa(i, &str, 10);
				str2 = gcnew String(&str);
				drawString = str2;
				drawPoint = Point(indent+i*koefW, h-indent-(h-indent-10)/2);
				e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   

				g->DrawLine(Pens::Black, Point(indent-2, h-buffer->buff[i][0]*koefH), Point(indent+2, h-buffer->buff[i][0]*koefH));
				itoa(buffer->buff[i][0], &str, 10);
				str2 = gcnew String(&str);
				drawString = str2;
				drawPoint = Point(indent-20, h-indent-(h-indent-10)/2-koefH*buffer->buff[i][0]);
				e->Graphics->DrawString( drawString, drawFont, drawBrush, drawPoint );   
			}
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

		virtual void OnScroll(ScrollEventArgs^se) override
        {
            Invalidate();
			Form::OnScroll(se);
        }

	protected: 
	
	private: PrintDialog^  printDialog1;
	private: TabControl^  tabControl1;
	private: array<TabPage^> ^ tabPage;
	private: Label^ label1;
	
	    

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
		void InitializeComponent(int NumberTabs, int arraySize)
		{
		    int i;
			this->printDialog1 = (gcnew System::Windows::Forms::PrintDialog());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());

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


			this->tabPage[0]->Paint += gcnew System::Windows::Forms::PaintEventHandler( this, &Form1::pagePaint);
			
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
			};

					
			// Form1
			 
			this->AutoScaleDimensions = System::Drawing::SizeF(SizeFormH, SizeFormW);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 266);
			this->Controls->Add(this->tabControl1);
            
            
			this->Name = L"Sound processor";
			this->Text = L"Sound processor";
			this->tabControl1->ResumeLayout(false);
			this->ResumeLayout(false);

			System::Windows::Forms::Form::AutoScroll = true;
            this->VScroll = false;

			//IsInitialize = true;

		}
#pragma endregion
};
	public ref class SpFormEchoDialog : public System::Windows::Forms::Form
	{
	public:
		SpFormEchoDialog(Global *global)
		{
			InitializeComponent(global);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SpFormEchoDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 



	private: System::Windows::Forms::Label^  LABELLOUDNESS;
			 System::Windows::Forms::Label^  LABELDELAY;
			 System::Windows::Forms::Label^  LABELHELP;
	private: System::Windows::Forms::TextBox^  TEXTBOXLOUDNESS;
			 System::Windows::Forms::TextBox^  TEXTBOXDELAY;
	private: System::Windows::Forms::Button^  BUTTON_OK;
			 Global *global;

	
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
		void InitializeComponent(Global *global)
		{
			this->global = global;
			this->LABELLOUDNESS = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXLOUDNESS = (gcnew System::Windows::Forms::TextBox());
			this->LABELDELAY = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXDELAY = (gcnew System::Windows::Forms::TextBox());
			this->LABELHELP = (gcnew System::Windows::Forms::Label());
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// LABELLOUDNESS
			// 
			this->LABELLOUDNESS->Location = System::Drawing::Point(13, 35);
			this->LABELLOUDNESS->Name = L"LABELLOUDNESS";
			this->LABELLOUDNESS->Size = System::Drawing::Size(122, 17);
			this->LABELLOUDNESS->Text = L"Coefficient of the echo";
			// 
			// TEXTBOXLOUDNESS
			// 
			this->TEXTBOXLOUDNESS->Location = System::Drawing::Point(160, 30);
			this->TEXTBOXLOUDNESS->Name = L"TEXTBOXLOUDNESS";
			this->TEXTBOXLOUDNESS->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXLOUDNESS->TabIndex = 1;
			// 
			// LABELDELAY
			// 
			this->LABELDELAY->Location = System::Drawing::Point(13, 65);
			this->LABELDELAY->Name = L"LABELDELAY";
			this->LABELDELAY->Size = System::Drawing::Size(122, 17);
			this->LABELDELAY->Text = L"Delay";
			// 
			// TEXTBOXDELAY
			// 
			this->TEXTBOXDELAY->Location = System::Drawing::Point(160, 60);
			this->TEXTBOXDELAY->Name = L"TEXTBOXDELAY";
			this->TEXTBOXDELAY->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXDELAY->TabIndex = 2;
			// 
			// LABELHELP
			// 
			this->LABELHELP->Location = System::Drawing::Point(13, 83);
			this->LABELHELP->Name = L"LABELHELP";
			this->LABELHELP->Size = System::Drawing::Size(300, 17);
			if (global->exampleBuffer != NULL){
				this->LABELHELP->Text = L"(It would be better, if it is equals "+global->exampleBuffer->titleWave.freq/2+L", maximum="+global->exampleBuffer->getLength()+L")";
			}
			// 
			// BUTTON_OK
			// 
			this->BUTTON_OK->Location = System::Drawing::Point(196, 111);
			this->BUTTON_OK->Name = L"BUTTON_OK";
			this->BUTTON_OK->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OK->TabIndex = 3;
			this->BUTTON_OK->Text = L"OK";
			this->BUTTON_OK->UseVisualStyleBackColor = true;
			this->BUTTON_OK->Click += gcnew System::EventHandler(this, &SpFormEchoDialog::BUTTON_OK_Click);
			
			// 
			// SpFormEchoDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 159);
			this->Controls->Add(this->BUTTON_OK);
			this->Controls->Add(this->LABELLOUDNESS);
			this->Controls->Add(this->TEXTBOXLOUDNESS);
			this->Controls->Add(this->LABELDELAY);
			this->Controls->Add(this->TEXTBOXDELAY);
			this->Controls->Add(this->LABELHELP);
			this->MaximizeBox = false;
			this->Name = L"SpFormEchoDialog";
			this->Text = L"Echo parameters";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BUTTON_OK_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = System::Windows::Forms::DialogResult::None;
				 
				 String^ text = this->TEXTBOXLOUDNESS->Text;
				 //перевод System::String в char*
				 pin_ptr<const wchar_t> wch = PtrToStringChars(text);
				 size_t convertedChars = 0;
				 errno_t err = 0;
				 size_t  sizeInBytes = ((text->Length + 1) * 2);
				 char* coefficientInChar = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
					coefficientInChar, sizeInBytes,
					wch, sizeInBytes);

				 long delay = 0;
				 String^ textDelay = this->TEXTBOXDELAY->Text;
				 //перевод System::String в char*
				 wch = PtrToStringChars(textDelay);
				 convertedChars = 0;
				 err = 0;
				 sizeInBytes = ((textDelay->Length + 1) * 2);
				 char* delayInChar = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
					delayInChar, sizeInBytes,
					wch, sizeInBytes);
				 if (delayInChar != NULL){
					 //перевод из char* в long
					 int length = 0;
					 while (delayInChar[length] != '\0') {length++;}
					 for (int i=0; i<length; i++){
						 delay = delay*10 + (delayInChar[i]-48);
					 }
				 }

				 if (coefficientInChar != NULL) {
					 //перевод из char* в float
					 int intCoefficient = 0;
					 int placeOfPoint = 0;
					 int length = 0;
					 while (coefficientInChar[length] != '\0') {length++;}
					 for (int i=0; i<length; i++){
						 if (coefficientInChar[i] != '.'){
							intCoefficient = intCoefficient*10 + (coefficientInChar[i]-48);
						 }else{
							 placeOfPoint = i;
						 }
					 }
					 float coefficient = intCoefficient;
					 for (int i=0; i < (length-placeOfPoint-1); i++){
						 coefficient = coefficient/10;
					 }

					 if ((coefficient < 1)&&(coefficient > 0)) {
						 if ((delay > 0)&&(delay < global->exampleBuffer->getLength())){//корректные данные
							bool flagOfFirstUse = true;
							mainEcho(global->exampleBuffer, coefficient, delay); //вызов процедуры Echo с нужными параметрами
							this->DialogResult = System::Windows::Forms::DialogResult::OK;
							Close();
						 }else{
							 MessageBox::Show(L"Delay must be positive and lesser then the length of the native buffer", L"Sound processor", 
								MessageBoxButtons::OK, MessageBoxIcon::Error);
							 this->TEXTBOXDELAY->Text = L"";
						 }
					 }else{
						 MessageBox::Show(L"The coefficient must be between 0 and 1", L"Sound processor", 
							 MessageBoxButtons::OK, MessageBoxIcon::Error);
						 this->TEXTBOXLOUDNESS->Text = L"";
					 }
				 }
			 }
};




	public ref class SpFormDistortionDialog : public System::Windows::Forms::Form
	{
	public:
		SpFormDistortionDialog(Global *global)
		{
			InitializeComponent(global);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SpFormDistortionDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  LABELHIGHLIMIT;
	private: System::Windows::Forms::TextBox^  TEXTBOXHIGHLIMIT;
			 Global *global;
	protected: 

	protected: 






	private: System::Windows::Forms::Label^  LABELLOWLIMIT;
			 System::Windows::Forms::Label^  LABELHELP;
	private: System::Windows::Forms::TextBox^  TEXTBOXLOWLIMIT;
	private: System::Windows::Forms::Button^  BUTTON_OK;

	
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
		void InitializeComponent(Global *global)
		{
			this->global = global;
			this->LABELHIGHLIMIT = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXHIGHLIMIT = (gcnew System::Windows::Forms::TextBox());
			this->LABELLOWLIMIT = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXLOWLIMIT = (gcnew System::Windows::Forms::TextBox());
			this->LABELHELP = (gcnew System::Windows::Forms::Label());
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			this->LABELHIGHLIMIT->Location = System::Drawing::Point(34, 25);
			this->LABELHIGHLIMIT->Name = L"LABELHIGHLIMIT";
			this->LABELHIGHLIMIT->Size = System::Drawing::Size(93, 17);
			this->LABELHIGHLIMIT->Text = L"High limit";

			this->TEXTBOXHIGHLIMIT->Location = System::Drawing::Point(149, 20);
			this->TEXTBOXHIGHLIMIT->Name = L"TEXTBOXHIGHLIMIT";
			this->TEXTBOXHIGHLIMIT->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXHIGHLIMIT->TabIndex = 2;

			this->LABELLOWLIMIT->Location = System::Drawing::Point(34, 55);
			this->LABELLOWLIMIT->Name = L"LABELLOWLIMIT";
			this->LABELLOWLIMIT->Size = System::Drawing::Size(93, 16);
			this->LABELLOWLIMIT->Text = L"Low limit";

			this->TEXTBOXLOWLIMIT->Location = System::Drawing::Point(149, 50);
			this->TEXTBOXLOWLIMIT->Name = L"TEXTBOXLOWLIMIT";
			this->TEXTBOXLOWLIMIT->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXLOWLIMIT->TabIndex = 5;

			this->LABELHELP->Location = System::Drawing::Point(34, 85);
			this->LABELHELP->Name = L"LABELHELP";
			this->LABELHELP->Size = System::Drawing::Size(300, 17);
			if (global->exampleBuffer != NULL){
				int max = 0, min = 0;
				for (int i=0; i<global->exampleBuffer->getLength(); i++){
					for (int j=0; j<2; j++){
						if (max < global->exampleBuffer->buff[i][j]){
							max = global->exampleBuffer->buff[i][j];
						}
						if (min > global->exampleBuffer->buff[i][j]){
							min = global->exampleBuffer->buff[i][j];
						}
					}
				}
				this->LABELHELP->Text = L"(maximum="+max+L", minimum="+min+L")";
			}

			this->BUTTON_OK->Location = System::Drawing::Point(184, 108);
			this->BUTTON_OK->Name = L"BUTTON_OK";
			this->BUTTON_OK->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OK->TabIndex = 6;
			this->BUTTON_OK->Text = L"OK";
			this->BUTTON_OK->UseVisualStyleBackColor = true;
			this->BUTTON_OK->Click += gcnew System::EventHandler(this, &SpFormDistortionDialog::BUTTON_OK_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 159);
			this->Controls->Add(this->BUTTON_OK);
			this->Controls->Add(this->TEXTBOXLOWLIMIT);
			this->Controls->Add(this->LABELLOWLIMIT);
			this->Controls->Add(this->TEXTBOXHIGHLIMIT);
			this->Controls->Add(this->LABELHIGHLIMIT);
			this->Controls->Add(this->LABELHELP);
			this->MaximizeBox = false;
			this->Name = L"SpForm";
			this->Text = L"Distortion parameters";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void BUTTON_OK_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = System::Windows::Forms::DialogResult::None;
				 String^ highLimitStr = this->TEXTBOXHIGHLIMIT->Text;
				 String^ lowLimitStr = this->TEXTBOXLOWLIMIT->Text;

				 //перевод System::String в char*
				 pin_ptr<const wchar_t> wch = PtrToStringChars(highLimitStr);
				 size_t convertedChars = 0;
				 errno_t err = 0;
				 size_t  sizeInBytes = ((highLimitStr->Length + 1) * 2);
				 char* highLimitInChar = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
					highLimitInChar, sizeInBytes,
					wch, sizeInBytes);

				 //перевод System::String в char*
				 wch = PtrToStringChars(lowLimitStr);
				 convertedChars = 0;
				 err = 0;
				 sizeInBytes = ((lowLimitStr->Length + 1) * 2);
				 char* lowLimitInChar = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
					lowLimitInChar, sizeInBytes,
					wch, sizeInBytes);

				 int lengthHighLimit = 0, lengthLowLimit = 0;
				 while (highLimitInChar[lengthHighLimit] != '\0') lengthHighLimit++;
				 while (lowLimitInChar[lengthLowLimit] != '\0') lengthLowLimit++;

				 int highLimit = 0;
				 for (int i=0; i<lengthHighLimit; i++){
					 highLimit = highLimit*10 + (highLimitInChar[i]-48);
				 }

				 int lowLimit = 0;
				 for (int i=0; i<lengthLowLimit; i++){
					 lowLimit = lowLimit*10 + (lowLimitInChar[i]-48);
				 }

				 if (lowLimit < highLimit) { //корректные данные
					 mainDistortion(highLimit, lowLimit, global->exampleBuffer); //вызов процедуры Distortion с нужными параметрами
					 this->DialogResult = System::Windows::Forms::DialogResult::OK;
					 Close();
				 }else{
					 MessageBox::Show(L"You have entered wrong limits", L"Sound processor", 
							 MessageBoxButtons::OK, MessageBoxIcon::Error);
				 }
			 }
	};

	public ref class SpForm : public System::Windows::Forms::Form
	{
	public:
		SpForm(Global *global)
		{
			InitializeComponent(global);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SpForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  BUTTON_OPEN;
	private: System::Windows::Forms::Button^  BUTTON_CONVERT;
	private: System::Windows::Forms::Button^  BUTTON_PREVIEW;
	private: System::Windows::Forms::ComboBox^  COMPOBOX_EFFECTS;
	private: System::Windows::Forms::OpenFileDialog^  OPENFILEDIALOG;
	private: System::Windows::Forms::SaveFileDialog^  SAVEFILEDIALOG;
	private: System::Windows::Forms::Label^  LABELSTATE;
			 SpFormEchoDialog^ ECHODIALOG;
			 SpFormDistortionDialog^ DISTORTIONDIALOG;
			 Form1^ GRAPHICS;
			 Global *global;
			 	
	protected: 

	protected: 





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

		void InitializeComponent(Global *global)
		{
			this->global = global;
			this->BUTTON_OPEN = (gcnew System::Windows::Forms::Button());
			this->BUTTON_CONVERT = (gcnew System::Windows::Forms::Button());
			this->BUTTON_PREVIEW = (gcnew System::Windows::Forms::Button());
			this->COMPOBOX_EFFECTS = (gcnew System::Windows::Forms::ComboBox());
			this->OPENFILEDIALOG = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SAVEFILEDIALOG = (gcnew System::Windows::Forms::SaveFileDialog());
			this->LABELSTATE = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			//
			//BUTTON_OPEN
			//
			this->BUTTON_OPEN->Location = System::Drawing::Point(12, 26);
			this->BUTTON_OPEN->Name = L"BUTTON_OPEN";
			this->BUTTON_OPEN->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OPEN->Text = L"Open file";
			this->BUTTON_OPEN->UseVisualStyleBackColor = true;
			this->BUTTON_OPEN->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_OPEN_Click);
			this->BUTTON_OPEN->TabIndex = 0;
			this->BUTTON_OPEN->DialogResult = System::Windows::Forms::DialogResult::None;
			//
			//BUTTON_CONVERT
			//
			this->BUTTON_CONVERT->Location = System::Drawing::Point(205, 152);
			this->BUTTON_CONVERT->Name = L"BUTTON_CONVERT";
			this->BUTTON_CONVERT->Size = System::Drawing::Size(75, 23);
			this->BUTTON_CONVERT->Text = L"Convert";
			this->BUTTON_CONVERT->UseVisualStyleBackColor = true;
			this->BUTTON_CONVERT->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_CONVERT_Click);
			this->BUTTON_CONVERT->DialogResult = System::Windows::Forms::DialogResult::None;
			this->BUTTON_CONVERT->TabIndex = 3;
			this->BUTTON_CONVERT->Visible = FALSE;
			//
			//BUTTON_PREVIEW
			//
			this->BUTTON_PREVIEW->Location = System::Drawing::Point(205, 95);
			this->BUTTON_PREVIEW->Name = L"BUTTON_PREVIEW";
			this->BUTTON_PREVIEW->Size = System::Drawing::Size(75, 23);
			this->BUTTON_PREVIEW->TabIndex = 2;
			this->BUTTON_PREVIEW->Text = L"Preview";
			this->BUTTON_PREVIEW->UseVisualStyleBackColor = true;
			this->BUTTON_PREVIEW->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_PREVIEW_Click);
			this->BUTTON_PREVIEW->Visible = FALSE;
			//
			//COMPOBOX_EFFECTS
			//
			this->COMPOBOX_EFFECTS->FormattingEnabled = true;
			this->COMPOBOX_EFFECTS->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Echo", L"Distortion"});
			this->COMPOBOX_EFFECTS->Location = System::Drawing::Point(12, 95);
			this->COMPOBOX_EFFECTS->Name = L"COMPOBOX_EFFECTS";
			this->COMPOBOX_EFFECTS->Size = System::Drawing::Size(121, 21);
			this->COMPOBOX_EFFECTS->TabIndex = 1;
			this->COMPOBOX_EFFECTS->SelectedIndexChanged += gcnew System::EventHandler(this, &SpForm::COMPOBOX_EFFECTS_SelectedIndexChanged);
			this->COMPOBOX_EFFECTS->Visible = FALSE;
			//
			//LABELSTATE
			//
			this->LABELSTATE->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->LABELSTATE->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->LABELSTATE->Location = System::Drawing::Point(0, 196);
			this->LABELSTATE->Name = L"LABELSTATE";
			this->LABELSTATE->Size = System::Drawing::Size(292, 18);
			this->LABELSTATE->TabIndex = 4;

			this->Closing += gcnew CancelEventHandler(this,&SpForm::formOnClosing);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(292, 213);
			this->Controls->Add(this->LABELSTATE);
			this->Controls->Add(this->COMPOBOX_EFFECTS);
			this->Controls->Add(this->BUTTON_PREVIEW);
			this->Controls->Add(this->BUTTON_CONVERT);
			this->Controls->Add(this->BUTTON_OPEN);
			this->MaximizeBox = false;
			this->Name = L"SpForm";
			this->Text = L"Sound Processor";
			this->ResumeLayout(false);
		}
#pragma endregion
private: System::Void BUTTON_OPEN_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->LABELSTATE->Text = L"Opening...";
			 String^ outputString ="";
			 if (this->OPENFILEDIALOG->ShowDialog() == Windows::Forms::DialogResult::OK){ //если нажали Открыть
				String^ fileName = this->OPENFILEDIALOG->FileName; //получение имени файла, который надо открыть

				//перевод System::String в char*
				pin_ptr<const wchar_t> wch = PtrToStringChars(fileName);
				size_t convertedChars = 0;
				errno_t err = 0;
				size_t  sizeInBytes = ((fileName->Length + 1) * 2);
			    char* NameOfTheOpenedFile = (char *)malloc(sizeInBytes);
				err = wcstombs_s(&convertedChars, 
                    NameOfTheOpenedFile, sizeInBytes,
                    wch, sizeInBytes);

				read2(global->buffer, NameOfTheOpenedFile);
				global->exampleBuffer = new SoundBuffer(NULL, global->buffer->getLength());
				appropriate(global->exampleBuffer, global->buffer);
				global->exampleMemoryBuffer = new SoundBuffer(NULL, global->buffer->getLength());
				this->ECHODIALOG = (gcnew SpFormEchoDialog(this->global));
				this->DISTORTIONDIALOG = (gcnew SpFormDistortionDialog(this->global));

				fileName = fileName->Remove( 0, fileName->LastIndexOf('\\')+1 );
				outputString = String::Concat("Opened ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
			 this->BUTTON_OPEN->DialogResult = System::Windows::Forms::DialogResult::Yes;
			 this->BUTTON_CONVERT->Visible = TRUE;
			 this->BUTTON_PREVIEW->Visible = TRUE;
			 this->COMPOBOX_EFFECTS->Visible = TRUE;
		 }
private: System::Void BUTTON_CONVERT_Click(System::Object^  sender, System::EventArgs^  e) {
			 appropriate(global->buffer, global->exampleBuffer);//вызов функции, отвечающей за конвертирование
			 this->LABELSTATE->Text = L"Convert...";
			 String^ outputString = "";
			 if (this->SAVEFILEDIALOG->ShowDialog() == Windows::Forms::DialogResult::OK){ //если нажади Сохранить
				 String^ fileName = this->SAVEFILEDIALOG->FileName; //получение имени файла, куда сохранять
				 fileName = fileName->Remove(0,fileName->LastIndexOf('\\')+1 );

				 //перевод System::String в char*
				 pin_ptr<const wchar_t> wch = PtrToStringChars(this->SAVEFILEDIALOG->FileName);
				 size_t convertedChars = 0;
				 errno_t err = 0;
				 size_t  sizeInBytes = ((this->SAVEFILEDIALOG->FileName->Length + 1) * 2);
			     char* NameOfTheSavedFile = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
                     NameOfTheSavedFile, sizeInBytes,
                     wch, sizeInBytes);

				 write2(global->buffer, NameOfTheSavedFile);
				 outputString = String::Concat("Save as ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
			 this->BUTTON_CONVERT->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }
private: System::Void BUTTON_PREVIEW_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->GRAPHICS = (gcnew Form1(this->global->buffer,this->global->exampleBuffer));
			 GRAPHICS->ShowDialog();
			 this->LABELSTATE->Text = L"Preview...";
		 }
private: System::Void COMPOBOX_EFFECTS_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->LABELSTATE->Text = L"";
			 if (this->COMPOBOX_EFFECTS->SelectedItem->Equals("Distortion")){
				DISTORTIONDIALOG->ShowDialog();
				System::Windows::Forms::DialogResult dlgResult = DISTORTIONDIALOG->DialogResult;
				if (dlgResult == System::Windows::Forms::DialogResult::OK) {
					this->LABELSTATE->Text = L"Distortion...";
				}
			 }else{
				 if (this->COMPOBOX_EFFECTS->SelectedItem->Equals("Echo")){
					ECHODIALOG->ShowDialog();
					System::Windows::Forms::DialogResult dlgResult = ECHODIALOG->DialogResult;
					if (dlgResult == System::Windows::Forms::DialogResult::OK) {
						this->LABELSTATE->Text = L"Echo...";
					}
				 }
			 }
		 }
private: System::Void formOnClosing(System::Object^ sender,CancelEventArgs^  e) {
			 if (this->BUTTON_OPEN->DialogResult == System::Windows::Forms::DialogResult::Yes){
				 if (this->BUTTON_CONVERT->DialogResult != System::Windows::Forms::DialogResult::OK){
					 System::Windows::Forms::DialogResult dlgResult = MessageBox::Show(L"You haven't saved changes.\n Would you like to save it?", L"Sound processor", 
						 MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
					 if (dlgResult == System::Windows::Forms::DialogResult::Yes){
						 BUTTON_CONVERT_Click(sender, e);
					 }else{
						 if (dlgResult == System::Windows::Forms::DialogResult::Cancel){
							 e->Cancel = true;
						 }
					 }
				 }
			 }
		}
		 void appropriate(SoundBuffer *toBuffer, SoundBuffer *fromBuffer){
				 if (toBuffer->getLength() != fromBuffer->getLength()){
					 return;
				 }else{
					 for (int i=0; i<toBuffer->getLength(); i++){
						 for (int j=0; j<CANALS; j++){
							 toBuffer->buff[i][j] = fromBuffer->buff[i][j];
						 }
					 }
					 toBuffer->titleWave = fromBuffer->titleWave;
				 }
		 }
};


}