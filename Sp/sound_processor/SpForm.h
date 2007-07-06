#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vcclr.h>
#include "resource.h"
//#include "WinNT.h"
//#include "uxtreme.h"

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

    public ref class SpFormEchoDialog : public System::Windows::Forms::Form
	{
	public:
		SpFormEchoDialog(void)
		{
			InitializeComponent();
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
		void InitializeComponent(void)
		{
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// 
			// BUTTON_OK
			// 
			this->BUTTON_OK->Location = System::Drawing::Point(12, 26);
			this->BUTTON_OK->Name = L"BUTTON_OK";
			this->BUTTON_OK->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OK->TabIndex = 0;
			this->BUTTON_OK->Text = L"Ok";
			this->BUTTON_OK->UseVisualStyleBackColor = true;
			this->BUTTON_OK->Click += gcnew System::EventHandler(this, &SpFormEchoDialog::BUTTON_OK_Click);

		}
#pragma endregion
		private: System::Void BUTTON_OK_Click(System::Object^  sender, System::EventArgs^  e) {
					 MessageBox::Show(L"Echo");
				 }
};




	public ref class SpFormDistortionDialog : public System::Windows::Forms::Form
	{
	public:
		SpFormDistortionDialog(void)
		{
			InitializeComponent();
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
		void InitializeComponent(void)
		{
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();

			// 
			// BUTTON_OK
			// 
			this->BUTTON_OK->Location = System::Drawing::Point(12, 26);
			this->BUTTON_OK->Name = L"BUTTON_OK";
			this->BUTTON_OK->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OK->TabIndex = 0;
			this->BUTTON_OK->Text = L"Ok";
			this->BUTTON_OK->UseVisualStyleBackColor = true;
			this->BUTTON_OK->Click += gcnew System::EventHandler(this, &SpFormDistortionDialog::BUTTON_OK_Click);
		}
#pragma endregion
		private: System::Void BUTTON_OK_Click(System::Object^  sender, System::EventArgs^  e) {
					 MessageBox::Show(L"Distortion");
				 }
};




	public ref class SpForm : public System::Windows::Forms::Form
	{
	public:
		SpForm(void)
		{
			InitializeComponent();
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
		void InitializeComponent(void)
		{
			this->BUTTON_OPEN = (gcnew System::Windows::Forms::Button());
			this->BUTTON_CONVERT = (gcnew System::Windows::Forms::Button());
			this->BUTTON_PREVIEW = (gcnew System::Windows::Forms::Button());
			this->COMPOBOX_EFFECTS = (gcnew System::Windows::Forms::ComboBox());
			this->OPENFILEDIALOG = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SAVEFILEDIALOG = (gcnew System::Windows::Forms::SaveFileDialog());
			this->LABELSTATE = (gcnew System::Windows::Forms::Label());
			this->ECHODIALOG = (gcnew SpFormEchoDialog());

			//видимо, тут надо добавить Visual Styles
			/*HTHEME hTheme = OpenTimeData(SpForm::Handle, this->BUTTON_OPEN->Name);
			if (hTheme) {
				int iStateID;
				 if (fPushed)
					 iStateId = 4;
				 else if (fDisabled)
					 iStateId = 3;
				 else if (fMouseOver)
					 iStateId = 2;
				 else if (fDefault)
					 iStateId = 1;
				 else
					 iStateId = 0;
				 HRESULT hr = DrawThemeBackground(hTheme, hdc, TMT_BUTTON, iStateId, &clientRect, 0);
			}*/

			this->SuspendLayout();
			// 
			// BUTTON_OPEN
			// 
			this->BUTTON_OPEN->Location = System::Drawing::Point(12, 26);
			this->BUTTON_OPEN->Name = L"BUTTON_OPEN";
			this->BUTTON_OPEN->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OPEN->TabIndex = 0;
			this->BUTTON_OPEN->Text = L"Open";
			this->BUTTON_OPEN->UseVisualStyleBackColor = true;
			this->BUTTON_OPEN->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_OPEN_Click);
			// 
			// BUTTON_CONVERT
			// 
			this->BUTTON_CONVERT->Location = System::Drawing::Point(205, 152);
			this->BUTTON_CONVERT->Name = L"BUTTON_CONVERT";
			this->BUTTON_CONVERT->Size = System::Drawing::Size(75, 23);
			this->BUTTON_CONVERT->TabIndex = 1;
			this->BUTTON_CONVERT->Text = L"Convert";
			this->BUTTON_CONVERT->UseVisualStyleBackColor = true;
			this->BUTTON_CONVERT->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_CONVERT_Click);
			// 
			// BUTTON_PREVIEW
			// 
			this->BUTTON_PREVIEW->Location = System::Drawing::Point(205, 95);
			this->BUTTON_PREVIEW->Name = L"BUTTON_PREVIEW";
			this->BUTTON_PREVIEW->Size = System::Drawing::Size(75, 23);
			this->BUTTON_PREVIEW->TabIndex = 2;
			this->BUTTON_PREVIEW->Text = L"Preview";
			this->BUTTON_PREVIEW->UseVisualStyleBackColor = true;
			this->BUTTON_PREVIEW->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_PREVIEW_Click);
			// 
			// COMPOBOX_EFFECTS
			// 
			this->COMPOBOX_EFFECTS->FormattingEnabled = true;
			this->COMPOBOX_EFFECTS->Items->AddRange(gcnew cli::array< System::Object^  >(2) {L"Echo", L"Distortion"});
			this->COMPOBOX_EFFECTS->Location = System::Drawing::Point(12, 95);
			this->COMPOBOX_EFFECTS->Name = L"COMPOBOX_EFFECTS";
			this->COMPOBOX_EFFECTS->Size = System::Drawing::Size(121, 21);
			this->COMPOBOX_EFFECTS->TabIndex = 3;
			this->COMPOBOX_EFFECTS->SelectedIndexChanged += gcnew System::EventHandler(this, &SpForm::COMPOBOX_EFFECTS_SelectedIndexChanged);
			// 
			// LABELSTATE
			// 
			this->LABELSTATE->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->LABELSTATE->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->LABELSTATE->Location = System::Drawing::Point(0, 196);
			this->LABELSTATE->Name = L"LABELSTATE";
			this->LABELSTATE->Size = System::Drawing::Size(292, 18);
			this->LABELSTATE->TabIndex = 4;
			// 
			// SpForm
			// 
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
			 this->LABELSTATE->Text = L"";
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

				read2(NameOfTheOpenedFile);
				fileName = fileName->Remove( 0, fileName->LastIndexOf('\\')+1 );
				outputString = String::Concat("Open ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
		 }
private: System::Void BUTTON_CONVERT_Click(System::Object^  sender, System::EventArgs^  e) {
			 //вызов функции, отвечающей за конвертирование
			 this->LABELSTATE->Text = L"Convert...";
			 String^ outputString = "";
			 if (this->SAVEFILEDIALOG->ShowDialog() == Windows::Forms::DialogResult::OK){ //если нажади Сохранить
				 String^ fileName = this->SAVEFILEDIALOG->FileName; //получение имени файла, куда сохранять
				 fileName = fileName->Remove(0,fileName->LastIndexOf('\\')+1 );
				 outputString = String::Concat("Save as ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
		 }
private: System::Void BUTTON_PREVIEW_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->LABELSTATE->Text = L"Preview...";
		 }
private: System::Void COMPOBOX_EFFECTS_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (this->COMPOBOX_EFFECTS->SelectedItem->Equals("Distortion")){
				this->LABELSTATE->Text = L"Distortion...";
			 }else{
				 if (this->COMPOBOX_EFFECTS->SelectedItem->Equals("Echo")){
					ECHODIALOG->ShowDialog();
					this->LABELSTATE->Text = L"Echo...";
				 }
			 }
		 }
};


}