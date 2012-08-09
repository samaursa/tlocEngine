#pragma once

//#include <fstream>
#include <vcclr.h>
#include <iostream>
#include <direct.h>
#include <algorithm>

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
  private: System::Windows::Forms::TextBox^  textBox2;
  private: System::Windows::Forms::TextBox^  textBox3;
  private: System::Windows::Forms::TextBox^  textBox4;
  private: System::Windows::Forms::TextBox^  textBox5;
  private: System::Windows::Forms::TextBox^  textBox6;
  private: System::Windows::Forms::TextBox^  textBox7;
  private: System::Windows::Forms::TextBox^  textBox8;
  private: System::Windows::Forms::TextBox^  textBox9;
  private: System::Windows::Forms::TextBox^  textBox10;
  private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
  private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Label^  label3;
  private: System::Windows::Forms::Label^  label4;
  private: System::Windows::Forms::Label^  label5;
  private: System::Windows::Forms::Label^  label6;
  private: System::Windows::Forms::Label^  label7;
  private: System::Windows::Forms::Label^  label8;
  private: System::Windows::Forms::Label^  label9;
  private: System::Windows::Forms::TextBox^  textBox11;
  private: System::Windows::Forms::Label^  label10;
  private: System::Windows::Forms::Button^  cancelBtn;

  private: System::Windows::Forms::Button^  saveBtn;


  private: System::Windows::Forms::Button^  browseBtn;
  private: System::Windows::Forms::Label^  messageLbl;







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
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->cancelBtn = (gcnew System::Windows::Forms::Button());
			this->saveBtn = (gcnew System::Windows::Forms::Button());
			this->browseBtn = (gcnew System::Windows::Forms::Button());
			this->messageLbl = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// loadBtn
			// 
			this->loadBtn->Location = System::Drawing::Point(12, 24);
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
			this->textBox1->Location = System::Drawing::Point(101, 26);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(251, 20);
			this->textBox1->TabIndex = 10;
			// 
			// textBox2
			// 
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(101, 75);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(332, 20);
			this->textBox2->TabIndex = 11;
			// 
			// textBox3
			// 
			this->textBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox3->Location = System::Drawing::Point(101, 104);
			this->textBox3->Name = L"textBox3";
			this->textBox3->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->textBox3->Size = System::Drawing::Size(332, 20);
			this->textBox3->TabIndex = 12;
			// 
			// textBox4
			// 
			this->textBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox4->Location = System::Drawing::Point(101, 133);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(332, 20);
			this->textBox4->TabIndex = 13;
			// 
			// textBox5
			// 
			this->textBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox5->Location = System::Drawing::Point(101, 162);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(332, 20);
			this->textBox5->TabIndex = 14;
			// 
			// textBox6
			// 
			this->textBox6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox6->Location = System::Drawing::Point(101, 191);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(332, 20);
			this->textBox6->TabIndex = 15;
			// 
			// textBox7
			// 
			this->textBox7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox7->Location = System::Drawing::Point(101, 220);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(332, 20);
			this->textBox7->TabIndex = 16;
			// 
			// textBox8
			// 
			this->textBox8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox8->Location = System::Drawing::Point(101, 249);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(332, 20);
			this->textBox8->TabIndex = 17;
			// 
			// textBox9
			// 
			this->textBox9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox9->Location = System::Drawing::Point(101, 278);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(332, 20);
			this->textBox9->TabIndex = 18;
			// 
			// textBox10
			// 
			this->textBox10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox10->Location = System::Drawing::Point(101, 307);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(332, 20);
			this->textBox10->TabIndex = 19;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(21, 78);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 20;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(21, 107);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 21;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(21, 136);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 22;
			this->label3->Text = L"label3";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(21, 165);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 23;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(21, 194);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 13);
			this->label5->TabIndex = 24;
			this->label5->Text = L"label5";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(21, 223);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 25;
			this->label6->Text = L"label6";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(21, 252);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(35, 13);
			this->label7->TabIndex = 26;
			this->label7->Text = L"label7";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(21, 281);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(35, 13);
			this->label8->TabIndex = 27;
			this->label8->Text = L"label8";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(21, 310);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(35, 13);
			this->label9->TabIndex = 28;
			this->label9->Text = L"label9";
			// 
			// textBox11
			// 
			this->textBox11->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox11->Location = System::Drawing::Point(101, 333);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(332, 20);
			this->textBox11->TabIndex = 29;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(21, 336);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(41, 13);
			this->label10->TabIndex = 30;
			this->label10->Text = L"label10";
			// 
			// cancelBtn
			// 
			this->cancelBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->cancelBtn->Location = System::Drawing::Point(358, 373);
			this->cancelBtn->Name = L"cancelBtn";
			this->cancelBtn->Size = System::Drawing::Size(75, 23);
			this->cancelBtn->TabIndex = 31;
			this->cancelBtn->Text = L"Cancel";
			this->cancelBtn->UseVisualStyleBackColor = true;
			this->cancelBtn->Click += gcnew System::EventHandler(this, &Form1::cancelBtn_Click);
			// 
			// saveBtn
			// 
			this->saveBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->saveBtn->Location = System::Drawing::Point(277, 373);
			this->saveBtn->Name = L"saveBtn";
			this->saveBtn->Size = System::Drawing::Size(75, 23);
			this->saveBtn->TabIndex = 32;
			this->saveBtn->Text = L"Save";
			this->saveBtn->UseVisualStyleBackColor = true;
			// 
			// browseBtn
			// 
			this->browseBtn->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->browseBtn->Location = System::Drawing::Point(358, 24);
			this->browseBtn->Name = L"browseBtn";
			this->browseBtn->Size = System::Drawing::Size(75, 23);
			this->browseBtn->TabIndex = 33;
			this->browseBtn->Text = L"Browse";
			this->browseBtn->UseVisualStyleBackColor = true;
			this->browseBtn->Click += gcnew System::EventHandler(this, &Form1::browseBtn_Click);
			// 
			// messageLbl
			// 
			this->messageLbl->AutoSize = true;
			this->messageLbl->Location = System::Drawing::Point(101, 53);
			this->messageLbl->Name = L"messageLbl";
			this->messageLbl->Size = System::Drawing::Size(0, 13);
			this->messageLbl->TabIndex = 34;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(461, 410);
			this->Controls->Add(this->messageLbl);
			this->Controls->Add(this->browseBtn);
			this->Controls->Add(this->saveBtn);
			this->Controls->Add(this->cancelBtn);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->textBox11);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->loadBtn);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::String ^pathDir;
private: System::String ^header;
private: System::String ^footer;

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
{
  saveBtn->Enabled = false;
  char currentDirectory[512];
  _getcwd(currentDirectory,512);
  System::String ^_temp;
  _temp = ConvertCharStringToSystemString(currentDirectory);
  this->textBox1->Text = _temp;
  this->folderBrowserDialog1->SelectedPath = _temp;
}

private: System::Void loadBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
  if ((pathDir = this->textBox1->Text) != "")
  {
    /*char pathTemplateLoc[512];
    ConvertSystemStringToCharString(pathDir, pathTemplateLoc);
    strcat_s(pathTemplateLoc, "/Paths.bat.template");
    
    char pathLoc[512];    
    ConvertSystemStringToCharString(pathDir, pathLoc);
    strcat_s(pathLoc, "/Paths.bat");*/

    System::String ^pathTemplateLoc = gcnew System::String(pathDir);
    pathTemplateLoc->Concat(gcnew System::String("/Paths.bat.template"));

    System::String ^pathLoc = gcnew System::String(pathDir);
    pathLoc->Concat(gcnew System::String("/Paths.bat"));

    /*std::ifstream pathTemplateFile(pathTemplateLoc);
    std::ifstream pathFile(pathLoc);*/

    IO::StreamReader ^pathTemplateFile = gcnew IO::StreamReader(pathTemplateLoc);
    
    if ()
    {
      messageLbl->Text = "Found Paths.bat.Template";
      messageLbl->ForeColor = System::Drawing::Color::Green;
      saveBtn->Enabled = true;
      if (pathFile.good())
      {
        System::String ^temp;
        pathFile >> temp;
        
        temp->ToUpper();
        while(temp->Compare("SET") || pathFile.eof())
        {
          pathFile >> temp;
          temp->ToUpper();
        }
      }

      pathTemplateFile.close();
      pathFile.close();
    }
    else
    {
      saveBtn->Enabled = false;
      messageLbl->Text = "Paths.bat.Template not found";
      messageLbl->ForeColor = System::Drawing::Color::Red;
    }
  }
}

private: System::Void cancelBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
  this->Close();
}

private: System::Void browseBtn_Click(System::Object^  sender, System::EventArgs^  e) 
{
  if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
  {
    pathDir = folderBrowserDialog1->SelectedPath;
    this->textBox1->Text = pathDir;
  }
}

private: void ConvertSystemStringToCharString(System::String ^input, char* output)
{
  pin_ptr<const wchar_t> wch;
  wch = PtrToStringChars(input);
  size_t strLength = wcslen(wch) + 1;
  size_t convertedChars = 0;
  wcstombs_s(&convertedChars, output, strLength, wch, _TRUNCATE);
}

private: System::String ^ ConvertCharStringToSystemString(char* input)
{
  return (gcnew String(input));
}
};
}

