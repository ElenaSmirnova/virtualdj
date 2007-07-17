#pragma once
#include "resource.h"

SoundBuffer *buffer;
SoundBuffer *exampleBuffer;
SoundBuffer *exampleMemoryBuffer;

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

	protected: 



	private: System::Windows::Forms::Label^  LABEL;
	private: System::Windows::Forms::TextBox^  TEXTBOX;
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
			this->LABEL = (gcnew System::Windows::Forms::Label());
			this->TEXTBOX = (gcnew System::Windows::Forms::TextBox());
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// LABEL
			// 
			this->LABEL->Location = System::Drawing::Point(13, 63);
			this->LABEL->Name = L"LABEL";
			this->LABEL->Size = System::Drawing::Size(122, 17);
			this->LABEL->TabIndex = 1;
			this->LABEL->Text = L"Coefficient of the echo";
			// 
			// TEXTBOX
			// 
			this->TEXTBOX->Location = System::Drawing::Point(160, 60);
			this->TEXTBOX->Name = L"TEXTBOX";
			this->TEXTBOX->Size = System::Drawing::Size(111, 20);
			this->TEXTBOX->TabIndex = 2;
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
			this->Controls->Add(this->TEXTBOX);
			this->Controls->Add(this->LABEL);
			this->MaximizeBox = false;
			this->Name = L"SpFormEchoDialog";
			this->Text = L"Echo parameters";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BUTTON_OK_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = System::Windows::Forms::DialogResult::None;
				 String^ text = this->TEXTBOX->Text;

				 //перевод System::String в char*
				 pin_ptr<const wchar_t> wch = PtrToStringChars(text);
				 size_t convertedChars = 0;
				 errno_t err = 0;
				 size_t  sizeInBytes = ((text->Length + 1) * 2);
				 char* coefficientInChar = (char *)malloc(sizeInBytes);
				 err = wcstombs_s(&convertedChars, 
					coefficientInChar, sizeInBytes,
					wch, sizeInBytes);

				 if (coefficientInChar != NULL) {
					 //перевод из char* в float
					 int intCoefficient = 0;
					 int placeOfPoint = 0;
					 int length = 0;
					 while (coefficientInChar[length] != '\0') length++;
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

					 if ((coefficient < 1)&&(coefficient > 0)) { //корректные данные
						 bool flagOfFirstUse = true;
						 mainEcho(exampleBuffer, coefficient, flagOfFirstUse, exampleMemoryBuffer); //вызов процедуры Echo с нужными параметрами
						 this->DialogResult = System::Windows::Forms::DialogResult::OK;
						 Close();
					 }else{
						 MessageBox::Show(L"The coefficient must be between 0 and 1", L"Sound processor", 
							 MessageBoxButtons::OK, MessageBoxIcon::Error);
						 this->TEXTBOX->Text = L"";
					 }
				 }
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
	private: System::Windows::Forms::Label^  LABELHIGHLIMIT;
	private: System::Windows::Forms::TextBox^  TEXTBOXHIGHLIMIT;
	protected: 

	protected: 






	private: System::Windows::Forms::Label^  LABELLOWLIMIT;
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
		void InitializeComponent(void)
		{
			this->LABELHIGHLIMIT = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXHIGHLIMIT = (gcnew System::Windows::Forms::TextBox());
			this->LABELLOWLIMIT = (gcnew System::Windows::Forms::Label());
			this->TEXTBOXLOWLIMIT = (gcnew System::Windows::Forms::TextBox());
			this->BUTTON_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->LABELHIGHLIMIT->Location = System::Drawing::Point(34, 29);
			this->LABELHIGHLIMIT->Name = L"LABELHIGHLIMIT";
			this->LABELHIGHLIMIT->Size = System::Drawing::Size(93, 17);
			this->LABELHIGHLIMIT->TabIndex = 1;
			this->LABELHIGHLIMIT->Text = L"High limit";
			this->TEXTBOXHIGHLIMIT->Location = System::Drawing::Point(149, 26);
			this->TEXTBOXHIGHLIMIT->Name = L"TEXTBOXHIGHLIMIT";
			this->TEXTBOXHIGHLIMIT->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXHIGHLIMIT->TabIndex = 2;
			this->LABELLOWLIMIT->Location = System::Drawing::Point(34, 68);
			this->LABELLOWLIMIT->Name = L"LABELLOWLIMIT";
			this->LABELLOWLIMIT->Size = System::Drawing::Size(93, 16);
			this->LABELLOWLIMIT->TabIndex = 4;
			this->LABELLOWLIMIT->Text = L"Low limit";
			this->TEXTBOXLOWLIMIT->Location = System::Drawing::Point(149, 68);
			this->TEXTBOXLOWLIMIT->Name = L"TEXTBOXLOWLIMIT";
			this->TEXTBOXLOWLIMIT->Size = System::Drawing::Size(111, 20);
			this->TEXTBOXLOWLIMIT->TabIndex = 5;
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
					 mainDistortion(highLimit, lowLimit, exampleBuffer); //вызов процедуры Distortion с нужными параметрами
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
			 SpFormDistortionDialog^ DISTORTIONDIALOG;
			 	
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
			buffer = new SoundBuffer(NULL, 0, 0);
			this->BUTTON_OPEN = (gcnew System::Windows::Forms::Button());
			this->BUTTON_CONVERT = (gcnew System::Windows::Forms::Button());
			this->BUTTON_PREVIEW = (gcnew System::Windows::Forms::Button());
			this->COMPOBOX_EFFECTS = (gcnew System::Windows::Forms::ComboBox());
			this->OPENFILEDIALOG = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SAVEFILEDIALOG = (gcnew System::Windows::Forms::SaveFileDialog());
			this->LABELSTATE = (gcnew System::Windows::Forms::Label());
			this->ECHODIALOG = (gcnew SpFormEchoDialog());
			this->DISTORTIONDIALOG = (gcnew SpFormDistortionDialog());
			this->SuspendLayout();
			//
			//BUTTON_OPEN
			//
			this->BUTTON_OPEN->Location = System::Drawing::Point(12, 26);
			this->BUTTON_OPEN->Name = L"BUTTON_OPEN";
			this->BUTTON_OPEN->Size = System::Drawing::Size(75, 23);
			this->BUTTON_OPEN->Text = L"Open";
			this->BUTTON_OPEN->UseVisualStyleBackColor = true;
			this->BUTTON_OPEN->Click += gcnew System::EventHandler(this, &SpForm::BUTTON_OPEN_Click);
			this->BUTTON_OPEN->TabIndex = 0;
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
			//
			//LABELSTATE
			//
			this->LABELSTATE->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->LABELSTATE->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->LABELSTATE->Location = System::Drawing::Point(0, 196);
			this->LABELSTATE->Name = L"LABELSTATE";
			this->LABELSTATE->Size = System::Drawing::Size(292, 18);
			this->LABELSTATE->TabIndex = 4;

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

				read2(buffer,NameOfTheOpenedFile);
				exampleBuffer = new SoundBuffer(NULL, buffer->getLength(), buffer->frequency);
				appropriate(exampleBuffer, buffer);
				exampleMemoryBuffer = new SoundBuffer(NULL, buffer->getLength(), buffer->frequency);
				fileName = fileName->Remove( 0, fileName->LastIndexOf('\\')+1 );
				outputString = String::Concat("Open ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
		 }
private: System::Void BUTTON_CONVERT_Click(System::Object^  sender, System::EventArgs^  e) {
			 appropriate(buffer, exampleBuffer);//вызов функции, отвечающей за конвертирование
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

				 write2(buffer, NameOfTheSavedFile);
				 outputString = String::Concat("Save as ",fileName);
			 }
			 this->LABELSTATE->Text = outputString;
			 this->BUTTON_CONVERT->DialogResult = System::Windows::Forms::DialogResult::OK;
		 }
private: System::Void BUTTON_PREVIEW_Click(System::Object^  sender, System::EventArgs^  e) {
			 //вызов соответствующей функции
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
/*private: virtual System::Void OnClosed(System::EventArgs^  e) override {
			 if (this->BUTTON_CONVERT->DialogResult != System::Windows::Forms::DialogResult::OK){
				 System::Windows::Forms::DialogResult dlgResult = MessageBox::Show(L"You haven't saved changes.\n Would you like to save it?", L"Sound processor", 
					 MessageBoxButtons::YesNoCancel, MessageBoxIcon::Warning);
				 if (dlgResult == System::Windows::Forms::DialogResult::Yes){
					 System::Object^ sender = gcnew System::Object();
					 BUTTON_CONVERT_Click(sender, e);
				 }else{
					 if (dlgResult == System::Windows::Forms::DialogResult::Cancel){
						 return;
					 }else{
						 if (dlgResult == System::Windows::Forms::DialogResult::No){
							 this->Close();
						 }
					 }
				 }
			 }
		}*/
		 void appropriate(SoundBuffer *toBuffer, SoundBuffer *fromBuffer){
				 if (toBuffer->getLength() != fromBuffer->getLength()){
					 return;
				 }else{
					 for (int i=0; i<toBuffer->getLength(); i++){
						 for (int j=0; j<CANALS; j++){
							 toBuffer->buff[i][j] = fromBuffer->buff[i][j];
						 }
					 }
				 }
			 }
};


}