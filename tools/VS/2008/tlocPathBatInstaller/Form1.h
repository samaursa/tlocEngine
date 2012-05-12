#pragma once

#include <fstream>
#include <vcclr.h>
#include <iostream>
#include <direct.h>

#include "PathBatManager.h"

namespace PathBatInstaller {

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
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::Button^  loadBtn;
  protected: 

  protected: 

  protected: 



  





  private: System::Windows::Forms::TextBox^  textBox1;
  private: System::Windows::Forms::TextBox^  variable1;
  private: System::Windows::Forms::TextBox^  variable2;
  private: System::Windows::Forms::TextBox^  variable3;
  private: System::Windows::Forms::TextBox^  variable4;
  private: System::Windows::Forms::TextBox^  variable5;
  private: System::Windows::Forms::TextBox^  variable6;
  private: System::Windows::Forms::TextBox^  variable7;
  private: System::Windows::Forms::TextBox^  variable8;
  private: System::Windows::Forms::TextBox^  variable9;









  private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
  private: System::Windows::Forms::TextBox^  variable10;











  private: System::Windows::Forms::Button^  cancelBtn;

  private: System::Windows::Forms::Button^  saveBtn;


  private: System::Windows::Forms::Button^  browseBtn;

  private: System::Windows::Forms::TextBox^  variableName1;
  private: System::Windows::Forms::TextBox^  variableName2;
  private: System::Windows::Forms::TextBox^  variableName3;
  private: System::Windows::Forms::TextBox^  variableName4;
  private: System::Windows::Forms::TextBox^  variableName5;
  private: System::Windows::Forms::TextBox^  variableName6;
  private: System::Windows::Forms::TextBox^  variableName7;
  private: System::Windows::Forms::TextBox^  variableName8;
  private: System::Windows::Forms::TextBox^  variableName9;
  private: System::Windows::Forms::TextBox^  variableName10;
  private: System::Windows::Forms::Button^  browseBtn1;

  private: System::Windows::Forms::Button^  browseBtn2;











  private: System::Windows::Forms::Button^  browseBtn3;

  private: System::Windows::Forms::Button^  browseBtn4;

  private: System::Windows::Forms::Button^  browseBtn5;
private: System::Windows::Forms::Button^  browseBtn6;
private: System::Windows::Forms::Button^  browseBtn7;
private: System::Windows::Forms::Button^  browseBtn8;
private: System::Windows::Forms::Button^  browseBtn9;
private: System::Windows::Forms::Button^  browseBtn10;









  private: System::Collections::Generic::List<System::Windows::Forms::TextBox^> ^m_variableName;
  private: System::Collections::Generic::List<System::Windows::Forms::TextBox^> ^m_variable;
  private: System::Collections::Generic::List<System::Windows::Forms::Button^> ^m_browseButtons;
private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserVariable;
private: System::Windows::Forms::RadioButton^  PathBatPriorityBtn;
private: System::Windows::Forms::RadioButton^  PathBatTemplatePriorityBtn;


private: System::Windows::Forms::StatusStrip^  statusStrip1;
private: System::Windows::Forms::ToolStripStatusLabel^  messageLbl;














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
      this->loadBtn = (gcnew System::Windows::Forms::Button());
      this->textBox1 = (gcnew System::Windows::Forms::TextBox());
      this->variable1 = (gcnew System::Windows::Forms::TextBox());
      this->variable2 = (gcnew System::Windows::Forms::TextBox());
      this->variable3 = (gcnew System::Windows::Forms::TextBox());
      this->variable4 = (gcnew System::Windows::Forms::TextBox());
      this->variable5 = (gcnew System::Windows::Forms::TextBox());
      this->variable6 = (gcnew System::Windows::Forms::TextBox());
      this->variable7 = (gcnew System::Windows::Forms::TextBox());
      this->variable8 = (gcnew System::Windows::Forms::TextBox());
      this->variable9 = (gcnew System::Windows::Forms::TextBox());
      this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
      this->variable10 = (gcnew System::Windows::Forms::TextBox());
      this->cancelBtn = (gcnew System::Windows::Forms::Button());
      this->saveBtn = (gcnew System::Windows::Forms::Button());
      this->browseBtn = (gcnew System::Windows::Forms::Button());
      this->variableName1 = (gcnew System::Windows::Forms::TextBox());
      this->variableName2 = (gcnew System::Windows::Forms::TextBox());
      this->variableName3 = (gcnew System::Windows::Forms::TextBox());
      this->variableName4 = (gcnew System::Windows::Forms::TextBox());
      this->variableName5 = (gcnew System::Windows::Forms::TextBox());
      this->variableName6 = (gcnew System::Windows::Forms::TextBox());
      this->variableName7 = (gcnew System::Windows::Forms::TextBox());
      this->variableName8 = (gcnew System::Windows::Forms::TextBox());
      this->variableName9 = (gcnew System::Windows::Forms::TextBox());
      this->variableName10 = (gcnew System::Windows::Forms::TextBox());
      this->browseBtn1 = (gcnew System::Windows::Forms::Button());
      this->browseBtn2 = (gcnew System::Windows::Forms::Button());
      this->browseBtn3 = (gcnew System::Windows::Forms::Button());
      this->browseBtn4 = (gcnew System::Windows::Forms::Button());
      this->browseBtn5 = (gcnew System::Windows::Forms::Button());
      this->browseBtn6 = (gcnew System::Windows::Forms::Button());
      this->browseBtn7 = (gcnew System::Windows::Forms::Button());
      this->browseBtn8 = (gcnew System::Windows::Forms::Button());
      this->browseBtn9 = (gcnew System::Windows::Forms::Button());
      this->browseBtn10 = (gcnew System::Windows::Forms::Button());
      this->folderBrowserVariable = (gcnew System::Windows::Forms::FolderBrowserDialog());
      this->PathBatPriorityBtn = (gcnew System::Windows::Forms::RadioButton());
      this->PathBatTemplatePriorityBtn = (gcnew System::Windows::Forms::RadioButton());
      this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
      this->messageLbl = (gcnew System::Windows::Forms::ToolStripStatusLabel());
      this->statusStrip1->SuspendLayout();
      this->SuspendLayout();
      // 
      // loadBtn
      // 
      this->loadBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->loadBtn->Location = System::Drawing::Point(335, 12);
      this->loadBtn->Name = L"loadBtn";
      this->loadBtn->Size = System::Drawing::Size(75, 23);
      this->loadBtn->TabIndex = 0;
      this->loadBtn->Text = L"Load";
      this->loadBtn->UseVisualStyleBackColor = true;
      this->loadBtn->Click += gcnew System::EventHandler(this, &Form1::loadBtn_Click);
      // 
      // textBox1
      // 
      this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->textBox1->Location = System::Drawing::Point(12, 14);
      this->textBox1->Name = L"textBox1";
      this->textBox1->Size = System::Drawing::Size(236, 20);
      this->textBox1->TabIndex = 10;
      // 
      // variable1
      // 
      this->variable1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable1->Location = System::Drawing::Point(117, 77);
      this->variable1->Name = L"variable1";
      this->variable1->Size = System::Drawing::Size(212, 20);
      this->variable1->TabIndex = 11;
      this->variable1->TextChanged += gcnew System::EventHandler(this, &Form1::variable1_TextChanged);
      // 
      // variable2
      // 
      this->variable2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable2->Location = System::Drawing::Point(117, 106);
      this->variable2->Name = L"variable2";
      this->variable2->RightToLeft = System::Windows::Forms::RightToLeft::No;
      this->variable2->Size = System::Drawing::Size(212, 20);
      this->variable2->TabIndex = 12;
      this->variable2->TextChanged += gcnew System::EventHandler(this, &Form1::variable2_TextChanged);
      // 
      // variable3
      // 
      this->variable3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable3->Location = System::Drawing::Point(117, 135);
      this->variable3->Name = L"variable3";
      this->variable3->Size = System::Drawing::Size(212, 20);
      this->variable3->TabIndex = 13;
      this->variable3->TextChanged += gcnew System::EventHandler(this, &Form1::variable3_TextChanged);
      // 
      // variable4
      // 
      this->variable4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable4->Location = System::Drawing::Point(117, 164);
      this->variable4->Name = L"variable4";
      this->variable4->Size = System::Drawing::Size(212, 20);
      this->variable4->TabIndex = 14;
      this->variable4->TextChanged += gcnew System::EventHandler(this, &Form1::variable4_TextChanged);
      // 
      // variable5
      // 
      this->variable5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable5->Location = System::Drawing::Point(117, 193);
      this->variable5->Name = L"variable5";
      this->variable5->Size = System::Drawing::Size(212, 20);
      this->variable5->TabIndex = 15;
      this->variable5->TextChanged += gcnew System::EventHandler(this, &Form1::variable5_TextChanged);
      // 
      // variable6
      // 
      this->variable6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable6->Location = System::Drawing::Point(117, 222);
      this->variable6->Name = L"variable6";
      this->variable6->Size = System::Drawing::Size(212, 20);
      this->variable6->TabIndex = 16;
      this->variable6->TextChanged += gcnew System::EventHandler(this, &Form1::variable6_TextChanged);
      // 
      // variable7
      // 
      this->variable7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable7->Location = System::Drawing::Point(117, 251);
      this->variable7->Name = L"variable7";
      this->variable7->Size = System::Drawing::Size(212, 20);
      this->variable7->TabIndex = 17;
      this->variable7->TextChanged += gcnew System::EventHandler(this, &Form1::variable7_TextChanged);
      // 
      // variable8
      // 
      this->variable8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable8->Location = System::Drawing::Point(117, 280);
      this->variable8->Name = L"variable8";
      this->variable8->Size = System::Drawing::Size(212, 20);
      this->variable8->TabIndex = 18;
      this->variable8->TextChanged += gcnew System::EventHandler(this, &Form1::variable8_TextChanged);
      // 
      // variable9
      // 
      this->variable9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable9->Location = System::Drawing::Point(117, 309);
      this->variable9->Name = L"variable9";
      this->variable9->Size = System::Drawing::Size(212, 20);
      this->variable9->TabIndex = 19;
      this->variable9->TextChanged += gcnew System::EventHandler(this, &Form1::variable9_TextChanged);
      // 
      // variable10
      // 
      this->variable10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
        | System::Windows::Forms::AnchorStyles::Right));
      this->variable10->Location = System::Drawing::Point(117, 335);
      this->variable10->Name = L"variable10";
      this->variable10->Size = System::Drawing::Size(212, 20);
      this->variable10->TabIndex = 29;
      this->variable10->TextChanged += gcnew System::EventHandler(this, &Form1::variable10_TextChanged);
      // 
      // cancelBtn
      // 
      this->cancelBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->cancelBtn->Location = System::Drawing::Point(335, 378);
      this->cancelBtn->Name = L"cancelBtn";
      this->cancelBtn->Size = System::Drawing::Size(75, 23);
      this->cancelBtn->TabIndex = 31;
      this->cancelBtn->Text = L"Close";
      this->cancelBtn->UseVisualStyleBackColor = true;
      this->cancelBtn->Click += gcnew System::EventHandler(this, &Form1::closeBtn_Click);
      // 
      // saveBtn
      // 
      this->saveBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->saveBtn->Location = System::Drawing::Point(254, 378);
      this->saveBtn->Name = L"saveBtn";
      this->saveBtn->Size = System::Drawing::Size(75, 23);
      this->saveBtn->TabIndex = 32;
      this->saveBtn->Text = L"Save";
      this->saveBtn->UseVisualStyleBackColor = true;
      this->saveBtn->Click += gcnew System::EventHandler(this, &Form1::saveBtn_Click);
      // 
      // browseBtn
      // 
      this->browseBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn->Location = System::Drawing::Point(254, 12);
      this->browseBtn->Name = L"browseBtn";
      this->browseBtn->Size = System::Drawing::Size(75, 23);
      this->browseBtn->TabIndex = 33;
      this->browseBtn->Text = L"Browse";
      this->browseBtn->UseVisualStyleBackColor = true;
      this->browseBtn->Click += gcnew System::EventHandler(this, &Form1::browseBtn_Click);
      // 
      // variableName1
      // 
      this->variableName1->Location = System::Drawing::Point(12, 77);
      this->variableName1->Name = L"variableName1";
      this->variableName1->Size = System::Drawing::Size(100, 20);
      this->variableName1->TabIndex = 35;
      this->variableName1->TextChanged += gcnew System::EventHandler(this, &Form1::variableName1_TextChanged);
      // 
      // variableName2
      // 
      this->variableName2->Location = System::Drawing::Point(12, 106);
      this->variableName2->Name = L"variableName2";
      this->variableName2->Size = System::Drawing::Size(100, 20);
      this->variableName2->TabIndex = 36;
      this->variableName2->TextChanged += gcnew System::EventHandler(this, &Form1::variableName2_TextChanged);
      // 
      // variableName3
      // 
      this->variableName3->Location = System::Drawing::Point(12, 135);
      this->variableName3->Name = L"variableName3";
      this->variableName3->Size = System::Drawing::Size(100, 20);
      this->variableName3->TabIndex = 37;
      this->variableName3->TextChanged += gcnew System::EventHandler(this, &Form1::variableName3_TextChanged);
      // 
      // variableName4
      // 
      this->variableName4->Location = System::Drawing::Point(12, 164);
      this->variableName4->Name = L"variableName4";
      this->variableName4->Size = System::Drawing::Size(100, 20);
      this->variableName4->TabIndex = 38;
      this->variableName4->TextChanged += gcnew System::EventHandler(this, &Form1::variableName4_TextChanged);
      // 
      // variableName5
      // 
      this->variableName5->Location = System::Drawing::Point(12, 193);
      this->variableName5->Name = L"variableName5";
      this->variableName5->Size = System::Drawing::Size(100, 20);
      this->variableName5->TabIndex = 39;
      this->variableName5->TextChanged += gcnew System::EventHandler(this, &Form1::variableName5_TextChanged);
      // 
      // variableName6
      // 
      this->variableName6->Location = System::Drawing::Point(12, 222);
      this->variableName6->Name = L"variableName6";
      this->variableName6->Size = System::Drawing::Size(100, 20);
      this->variableName6->TabIndex = 40;
      this->variableName6->TextChanged += gcnew System::EventHandler(this, &Form1::variableName6_TextChanged);
      // 
      // variableName7
      // 
      this->variableName7->Location = System::Drawing::Point(12, 251);
      this->variableName7->Name = L"variableName7";
      this->variableName7->Size = System::Drawing::Size(100, 20);
      this->variableName7->TabIndex = 41;
      this->variableName7->TextChanged += gcnew System::EventHandler(this, &Form1::variableName7_TextChanged);
      // 
      // variableName8
      // 
      this->variableName8->Location = System::Drawing::Point(12, 280);
      this->variableName8->Name = L"variableName8";
      this->variableName8->Size = System::Drawing::Size(100, 20);
      this->variableName8->TabIndex = 42;
      this->variableName8->TextChanged += gcnew System::EventHandler(this, &Form1::variableName8_TextChanged);
      // 
      // variableName9
      // 
      this->variableName9->Location = System::Drawing::Point(12, 309);
      this->variableName9->Name = L"variableName9";
      this->variableName9->Size = System::Drawing::Size(100, 20);
      this->variableName9->TabIndex = 43;
      this->variableName9->TextChanged += gcnew System::EventHandler(this, &Form1::variableName9_TextChanged);
      // 
      // variableName10
      // 
      this->variableName10->Location = System::Drawing::Point(12, 335);
      this->variableName10->Name = L"variableName10";
      this->variableName10->Size = System::Drawing::Size(100, 20);
      this->variableName10->TabIndex = 44;
      this->variableName10->TextChanged += gcnew System::EventHandler(this, &Form1::variableName10_TextChanged);
      // 
      // browseBtn1
      // 
      this->browseBtn1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn1->Location = System::Drawing::Point(335, 75);
      this->browseBtn1->Name = L"browseBtn1";
      this->browseBtn1->Size = System::Drawing::Size(75, 23);
      this->browseBtn1->TabIndex = 45;
      this->browseBtn1->Text = L"Browse";
      this->browseBtn1->UseVisualStyleBackColor = true;
      this->browseBtn1->Click += gcnew System::EventHandler(this, &Form1::browseBtn1_Click);
      // 
      // browseBtn2
      // 
      this->browseBtn2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn2->Location = System::Drawing::Point(335, 104);
      this->browseBtn2->Name = L"browseBtn2";
      this->browseBtn2->Size = System::Drawing::Size(75, 23);
      this->browseBtn2->TabIndex = 46;
      this->browseBtn2->Text = L"Browse";
      this->browseBtn2->UseVisualStyleBackColor = true;
      this->browseBtn2->Click += gcnew System::EventHandler(this, &Form1::browseBtn2_Click);
      // 
      // browseBtn3
      // 
      this->browseBtn3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn3->Location = System::Drawing::Point(335, 133);
      this->browseBtn3->Name = L"browseBtn3";
      this->browseBtn3->Size = System::Drawing::Size(75, 23);
      this->browseBtn3->TabIndex = 47;
      this->browseBtn3->Text = L"Browse";
      this->browseBtn3->UseVisualStyleBackColor = true;
      this->browseBtn3->Click += gcnew System::EventHandler(this, &Form1::browseBtn3_Click);
      // 
      // browseBtn4
      // 
      this->browseBtn4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn4->Location = System::Drawing::Point(335, 162);
      this->browseBtn4->Name = L"browseBtn4";
      this->browseBtn4->Size = System::Drawing::Size(75, 23);
      this->browseBtn4->TabIndex = 48;
      this->browseBtn4->Text = L"Browse";
      this->browseBtn4->UseVisualStyleBackColor = true;
      this->browseBtn4->Click += gcnew System::EventHandler(this, &Form1::browseBtn4_Click);
      // 
      // browseBtn5
      // 
      this->browseBtn5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn5->Location = System::Drawing::Point(335, 191);
      this->browseBtn5->Name = L"browseBtn5";
      this->browseBtn5->Size = System::Drawing::Size(75, 23);
      this->browseBtn5->TabIndex = 49;
      this->browseBtn5->Text = L"Browse";
      this->browseBtn5->UseVisualStyleBackColor = true;
      this->browseBtn5->Click += gcnew System::EventHandler(this, &Form1::browseBtn5_Click);
      // 
      // browseBtn6
      // 
      this->browseBtn6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn6->Location = System::Drawing::Point(335, 220);
      this->browseBtn6->Name = L"browseBtn6";
      this->browseBtn6->Size = System::Drawing::Size(75, 23);
      this->browseBtn6->TabIndex = 50;
      this->browseBtn6->Text = L"Browse";
      this->browseBtn6->UseVisualStyleBackColor = true;
      this->browseBtn6->Click += gcnew System::EventHandler(this, &Form1::browseBtn6_Click);
      // 
      // browseBtn7
      // 
      this->browseBtn7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn7->Location = System::Drawing::Point(335, 249);
      this->browseBtn7->Name = L"browseBtn7";
      this->browseBtn7->Size = System::Drawing::Size(75, 23);
      this->browseBtn7->TabIndex = 51;
      this->browseBtn7->Text = L"Browse";
      this->browseBtn7->UseVisualStyleBackColor = true;
      this->browseBtn7->Click += gcnew System::EventHandler(this, &Form1::browseBtn7_Click);
      // 
      // browseBtn8
      // 
      this->browseBtn8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn8->Location = System::Drawing::Point(335, 278);
      this->browseBtn8->Name = L"browseBtn8";
      this->browseBtn8->Size = System::Drawing::Size(75, 23);
      this->browseBtn8->TabIndex = 52;
      this->browseBtn8->Text = L"Browse";
      this->browseBtn8->UseVisualStyleBackColor = true;
      this->browseBtn8->Click += gcnew System::EventHandler(this, &Form1::browseBtn8_Click);
      // 
      // browseBtn9
      // 
      this->browseBtn9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn9->Location = System::Drawing::Point(335, 307);
      this->browseBtn9->Name = L"browseBtn9";
      this->browseBtn9->Size = System::Drawing::Size(75, 23);
      this->browseBtn9->TabIndex = 53;
      this->browseBtn9->Text = L"Browse";
      this->browseBtn9->UseVisualStyleBackColor = true;
      this->browseBtn9->Click += gcnew System::EventHandler(this, &Form1::browseBtn9_Click);
      // 
      // browseBtn10
      // 
      this->browseBtn10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
      this->browseBtn10->Location = System::Drawing::Point(335, 333);
      this->browseBtn10->Name = L"browseBtn10";
      this->browseBtn10->Size = System::Drawing::Size(75, 23);
      this->browseBtn10->TabIndex = 54;
      this->browseBtn10->Text = L"Browse";
      this->browseBtn10->UseVisualStyleBackColor = true;
      this->browseBtn10->Click += gcnew System::EventHandler(this, &Form1::browseBtn10_Click);
      // 
      // PathBatPriorityBtn
      // 
      this->PathBatPriorityBtn->AutoSize = true;
      this->PathBatPriorityBtn->Checked = true;
      this->PathBatPriorityBtn->Location = System::Drawing::Point(12, 41);
      this->PathBatPriorityBtn->Name = L"PathBatPriorityBtn";
      this->PathBatPriorityBtn->Size = System::Drawing::Size(178, 17);
      this->PathBatPriorityBtn->TabIndex = 55;
      this->PathBatPriorityBtn->TabStop = true;
      this->PathBatPriorityBtn->Text = L"Path.Bat and Path.Bat.Template";
      this->PathBatPriorityBtn->UseVisualStyleBackColor = true;
      // 
      // PathBatTemplatePriorityBtn
      // 
      this->PathBatTemplatePriorityBtn->AutoSize = true;
      this->PathBatTemplatePriorityBtn->Location = System::Drawing::Point(196, 41);
      this->PathBatTemplatePriorityBtn->Name = L"PathBatTemplatePriorityBtn";
      this->PathBatTemplatePriorityBtn->Size = System::Drawing::Size(135, 17);
      this->PathBatTemplatePriorityBtn->TabIndex = 56;
      this->PathBatTemplatePriorityBtn->Text = L"Path.Bat.Template only";
      this->PathBatTemplatePriorityBtn->UseVisualStyleBackColor = true;
      // 
      // statusStrip1
      // 
      this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->messageLbl});
      this->statusStrip1->Location = System::Drawing::Point(0, 410);
      this->statusStrip1->Name = L"statusStrip1";
      this->statusStrip1->Size = System::Drawing::Size(422, 22);
      this->statusStrip1->TabIndex = 57;
      this->statusStrip1->Text = L"statusStrip1";
      // 
      // Form1
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(422, 432);
      this->Controls->Add(this->statusStrip1);
      this->Controls->Add(this->loadBtn);
      this->Controls->Add(this->PathBatTemplatePriorityBtn);
      this->Controls->Add(this->PathBatPriorityBtn);
      this->Controls->Add(this->browseBtn10);
      this->Controls->Add(this->browseBtn9);
      this->Controls->Add(this->browseBtn8);
      this->Controls->Add(this->browseBtn7);
      this->Controls->Add(this->browseBtn6);
      this->Controls->Add(this->browseBtn5);
      this->Controls->Add(this->browseBtn4);
      this->Controls->Add(this->browseBtn3);
      this->Controls->Add(this->browseBtn2);
      this->Controls->Add(this->browseBtn1);
      this->Controls->Add(this->variableName10);
      this->Controls->Add(this->variableName9);
      this->Controls->Add(this->variableName8);
      this->Controls->Add(this->variableName7);
      this->Controls->Add(this->variableName6);
      this->Controls->Add(this->variableName5);
      this->Controls->Add(this->variableName4);
      this->Controls->Add(this->variableName3);
      this->Controls->Add(this->variableName2);
      this->Controls->Add(this->variableName1);
      this->Controls->Add(this->browseBtn);
      this->Controls->Add(this->saveBtn);
      this->Controls->Add(this->cancelBtn);
      this->Controls->Add(this->variable10);
      this->Controls->Add(this->variable9);
      this->Controls->Add(this->variable8);
      this->Controls->Add(this->variable7);
      this->Controls->Add(this->variable6);
      this->Controls->Add(this->variable5);
      this->Controls->Add(this->variable4);
      this->Controls->Add(this->variable3);
      this->Controls->Add(this->variable2);
      this->Controls->Add(this->variable1);
      this->Controls->Add(this->textBox1);
      this->MaximizeBox = false;
      this->MaximumSize = System::Drawing::Size(6000, 470);
      this->MinimumSize = System::Drawing::Size(300, 470);
      this->Name = L"Form1";
      this->Text = L"Path.Bat Installer";
      this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
      this->statusStrip1->ResumeLayout(false);
      this->statusStrip1->PerformLayout();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion

private: System::String^ m_pathDir;

private: PathBatManager* m_pathBatManager;


private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);

private: System::Void KeyPressInitialization();

private: void PreventSpacebar_KeyPress(Object^ sender, KeyPressEventArgs^ e);

private: System::Void loadBtn_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void browseBtn_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void saveBtn_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void closeBtn_Click(System::Object^  sender, System::EventArgs^  e);


private: System::Void browseBtn1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn4_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn5_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn6_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn7_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn8_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn9_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void browseBtn10_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void variableName1_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName2_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName3_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName4_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName5_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName6_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName7_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName8_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName9_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variableName10_TextChanged(System::Object^  sender, System::EventArgs^  e);

private: System::Void variable1_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable2_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable3_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable4_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable5_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable6_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable7_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable8_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable9_TextChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void variable10_TextChanged(System::Object^  sender, System::EventArgs^  e);

private: void DoInitializeWindowList();

private: void DoReset();

private: void DoEnableVariableInputs(bool a_enableAll);

private: void DoSetInitialDirectory();

private: void DoHandleBrowserBtnClick(size_t a_buttonNumber);

private: void DoHandleVariableValueTextChange(System::Object^ a_modifiedObject);

private: void DoHandleVariableNameTextChange(int a_objectNum);

private: void DoConvertSystemStringToCharString(System::String^ a_input, char* a_output);

private: System::String ^ DoConvertCharStringToSystemString(const char* a_input);

};


}
