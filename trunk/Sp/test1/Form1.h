
#pragma once


namespace test1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	int const n = 2;
	int a[10];
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(int n)
		{
			tabPage = gcnew array<System::Windows::Forms::TabPage^>(n);
			InitializeComponent(n);
			//
			//TODO: Add the constructor code here
			//
		}

		void pagePaint(Object^ /*sender*/, System::Windows::Forms::PaintEventArgs^ e)
		{
			Graphics^ g = e->Graphics;     
			//g->DrawLine( System::Drawing::Pens::Black, Point(30,30), Point(40,30));
			
			a[0] = 40; a[1] = 36; a[2] = 56; a[3] = 45; a[4] = 80;
			int k = 0;
			for (int j = 1; j <= 5; j++)
			{			
				g->FillEllipse(System::Drawing::Brushes::Black, System::Drawing::Rectangle(j+k,a[j-1],4,4));
				k = k+15;
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

	protected: 

	private: System::Windows::Forms::PrintDialog^  printDialog1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: array<System::Windows::Forms::TabPage^> ^ tabPage;









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
		void InitializeComponent(int n)
		{
			int i;
			this->printDialog1 = (gcnew System::Windows::Forms::PrintDialog());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			for (i = 0; i < n; i++)
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
			
			for(i = 0; i < n; i++)
			{
				this->tabControl1->Controls->Add(this->tabPage[i]);
			};

			this->tabControl1->Location = System::Drawing::Point(1, 1);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(1700, 1350);
			this->tabControl1->TabIndex = 0;
			
			for(i = 0; i < n; i++){
			this->tabPage[i]->Location = System::Drawing::Point(4, 22);
			this->tabPage[i]->Name = L"myTab";
			this->tabPage[i]->Padding = System::Windows::Forms::Padding(3);
			this->tabPage[i]->Size = System::Drawing::Size(284, 238);
			this->tabPage[i]->TabIndex = 0;
			this->tabPage[i]->Text = "myTab "+ (char)(i+1);
			this->tabPage[i]->UseVisualStyleBackColor = true;
			this->tabPage[i]->Click += gcnew System::EventHandler(this, &Form1::tabPage1_Click);
			};
			
			
			// Form1
			 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
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
private: System::Void Form1_Load_3(System::Object^  sender, System::EventArgs^  e) {
		 }
};
}

