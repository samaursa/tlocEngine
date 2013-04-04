#include "stdafx.h"
#include "Form1.h"

namespace PathBatInstaller {

System::Void Form1::Form1_Load(System::Object^ sender, System::EventArgs^ e)
{
  DoInitializeWindowList();

  saveBtn->Enabled = false;
  DoEnableVariableInputs(false);

  KeyPressInitialization();

  DoSetInitialDirectory();

  m_pathBatManager = new PathBatManager();
}

System::Void Form1::KeyPressInitialization()
{
  /*for each(System::Windows::Forms::TextBox ^theTextBox in m_variable)
  {
    theTextBox->KeyPress += gcnew KeyPressEventHandler(this, &Form1::PreventSpacebar_KeyPress);
  }*/

  for each(System::Windows::Forms::TextBox^ theTextBox in m_variableName)
  {
    theTextBox->KeyPress += gcnew KeyPressEventHandler(
                                    this, &Form1::PreventSpacebar_KeyPress);
  }
}

void Form1::PreventSpacebar_KeyPress( Object^ sender, KeyPressEventArgs^ e )
{
  e->Handled = e->KeyChar == ' ';
}

System::Void Form1::loadBtn_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoReset();
  if ((m_pathDir = this->textBox1->Text) != "")
  {
    int ret;

    char tempPathDir[512];
    DoConvertSystemStringToCharString(m_pathDir, tempPathDir);
    ret = m_pathBatManager->LoadPathFiles(tempPathDir,
                                          PathBatTemplatePriorityBtn->Checked);

    if (!ret)
    {
      messageLbl->ForeColor = System::Drawing::Color::Green;

      size_t l_numVariables = m_pathBatManager->GetNumVariables();
      if (l_numVariables > (size_t)m_variable->Count)
      {
        l_numVariables = (size_t)m_variable->Count;
      }

      for (size_t i = 0; i < l_numVariables; ++i)
      {
        m_variable[i]->Text = DoConvertCharStringToSystemString(
          m_pathBatManager->GetVariableValueAtIndex(i));
        m_variableName[i]->Text = DoConvertCharStringToSystemString(
          m_pathBatManager->GetVariableNameAtIndex(i));
      }

      saveBtn->Enabled = true;
      DoEnableVariableInputs(true);
    }
    else
    {
      messageLbl->ForeColor = System::Drawing::Color::Red;
      saveBtn->Enabled = false;
      DoEnableVariableInputs(false);
    }
    messageLbl->Text = DoConvertCharStringToSystemString(
      m_pathBatManager->GetStatus());

    DoCheckMainPath();
  }
}

System::Void Form1::browseBtn_Click( System::Object^ sender, System::EventArgs^ e )
{
  if (folderBrowserDialog1->ShowDialog() ==
      System::Windows::Forms::DialogResult::OK)
  {
    m_pathDir = folderBrowserDialog1->SelectedPath;
    this->textBox1->Text = m_pathDir;
  }
}

System::Void Form1::saveBtn_Click( System::Object^ sender, System::EventArgs^ e )
{
  m_pathBatManager->ClearVariables();
  char l_tempVariableName[512];
  char l_tempVariableValue[512];

  for (int i = 0; i < m_variableName->Count; ++i)
  {
    if (m_variableName[i]->Text != "" && m_variable[i]->Text != "")
    {
      DoConvertSystemStringToCharString(m_variableName[i]->Text,
                                        l_tempVariableName);
      DoConvertSystemStringToCharString(m_variable[i]->Text,
                                        l_tempVariableValue);
      m_pathBatManager->PushBackVariable(l_tempVariableName,
                                         l_tempVariableValue);
    }
  }

  char l_tempPath[512];
  DoConvertSystemStringToCharString(m_pathDir, l_tempPath);
  m_pathBatManager->SaveFile(l_tempPath);

  this->Close();
}

System::Void Form1::closeBtn_Click( System::Object^ sender, System::EventArgs^ e )
{
  this->Close();
}

System::Void Form1::browseBtn1_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(1);
}

System::Void Form1::browseBtn2_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(2);
}

System::Void Form1::browseBtn3_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(3);
}

System::Void Form1::browseBtn4_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(4);
}

System::Void Form1::browseBtn5_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(5);
}

System::Void Form1::browseBtn6_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(6);
}

System::Void Form1::browseBtn7_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(7);
}

System::Void Form1::browseBtn8_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(8);
}

System::Void Form1::browseBtn9_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(9);
}

System::Void Form1::browseBtn10_Click( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleBrowserBtnClick(10);
}

System::Void Form1::variableName1_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(1);
}

System::Void Form1::variableName2_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(2);
}

System::Void Form1::variableName3_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(3);
}

System::Void Form1::variableName5_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(5);
}

System::Void Form1::variableName4_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(4);
}

System::Void Form1::variableName6_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(6);
}

System::Void Form1::variableName7_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(7);
}

System::Void Form1::variableName8_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(8);
}

System::Void Form1::variableName9_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(9);
}

System::Void Form1::variableName10_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableNameTextChange(10);
}

System::Void Form1::variable1_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable2_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable3_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable4_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable5_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable6_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable7_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable8_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable9_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

System::Void Form1::variable10_TextChanged( System::Object^ sender, System::EventArgs^ e )
{
  DoHandleVariableValueTextChange(sender);
}

void Form1::DoInitializeWindowList()
{
  m_variableName = gcnew System::Collections::Generic::List<System::Windows::Forms::TextBox^>;
  m_variableName->Add(variableName1);
  m_variableName->Add(variableName2);
  m_variableName->Add(variableName3);
  m_variableName->Add(variableName4);
  m_variableName->Add(variableName5);
  m_variableName->Add(variableName6);
  m_variableName->Add(variableName7);
  m_variableName->Add(variableName8);
  m_variableName->Add(variableName9);
  m_variableName->Add(variableName10);

  m_variable = gcnew System::Collections::Generic::List<System::Windows::Forms::TextBox^>;
  m_variable->Add(variable1);
  m_variable->Add(variable2);
  m_variable->Add(variable3);
  m_variable->Add(variable4);
  m_variable->Add(variable5);
  m_variable->Add(variable6);
  m_variable->Add(variable7);
  m_variable->Add(variable8);
  m_variable->Add(variable9);
  m_variable->Add(variable10);

  m_browseButtons = gcnew System::Collections::Generic::List<System::Windows::Forms::Button^>;
  m_browseButtons->Add(browseBtn1);
  m_browseButtons->Add(browseBtn2);
  m_browseButtons->Add(browseBtn3);
  m_browseButtons->Add(browseBtn4);
  m_browseButtons->Add(browseBtn5);
  m_browseButtons->Add(browseBtn6);
  m_browseButtons->Add(browseBtn7);
  m_browseButtons->Add(browseBtn8);
  m_browseButtons->Add(browseBtn9);
  m_browseButtons->Add(browseBtn10);
}

void Form1::DoReset()
{
  DoEnableVariableInputs(false);
  m_pathBatManager->Reset();

  for each(System::Windows::Forms::TextBox^ l_textBox in m_variableName)
  {
    l_textBox->Text = String::Empty;
    l_textBox->BackColor = System::Drawing::Color::White;
  }

  for each(System::Windows::Forms::TextBox^ l_textBox in m_variable)
  {
    l_textBox->Text = String::Empty;
    l_textBox->BackColor = System::Drawing::Color::White;
  }

  fix_it_button->Enabled = false;
}

void Form1::DoCheckMainPath()
{
  // Find TLOC_PATH and make sure it is our current directory, if not, then
  // color the text box yellow and enable the fix it button
  for(int i = 0; i < m_variableName->Count; ++i)
  {
    if (m_variableName[i]->Text == "TLOC_PATH")
    {
      System::String^ currDir = System::AppDomain::CurrentDomain->BaseDirectory;
      if ( m_variable[i]->Text != currDir )
      {
        m_variableName[i]->BackColor = System::Drawing::Color::Orange;
        m_variable[i]->BackColor = System::Drawing::Color::Orange;

        fix_it_button->Enabled = true;
      }
      else
      {
        m_variableName[i]->BackColor = System::Drawing::Color::White;
        m_variable[i]->BackColor = System::Drawing::Color::White;

        fix_it_button->Enabled = false;
      }

      break;
    }

  }
}

void Form1::DoEnableVariableInputs( bool a_enableAll )
{
  for each(System::Windows::Forms::TextBox^ l_textBox in m_variableName)
  {
    l_textBox->Enabled = a_enableAll;
  }

  for (int i = 0; i < m_variable->Count; ++i)
  {
    if (m_variableName[i]->Text == "")
    {
      m_variable[i]->Enabled = false;
      m_browseButtons[i]->Enabled = false;
    }
    else
    {
      m_variable[i]->Enabled = a_enableAll;
      m_browseButtons[i]->Enabled = a_enableAll;
    }
  }

  /*for each(System::Windows::Forms::Button^ theButton in m_browseButtons)
  {
  theButton->Enabled = enableAll;
  }*/
}

void Form1::DoSetInitialDirectory()
{
  char l_currentDirectory[512];
  _getcwd(l_currentDirectory,512);

  System::String ^l_temp;
  l_temp = DoConvertCharStringToSystemString(l_currentDirectory);

  this->textBox1->Text = l_temp;
  this->folderBrowserDialog1->SelectedPath = l_temp;
}

void Form1::DoHandleBrowserBtnClick( size_t a_buttonNumber )
{
  a_buttonNumber -= 1;
  folderBrowserVariable->SelectedPath = m_variable[a_buttonNumber]->Text;

  if (folderBrowserVariable->ShowDialog() ==
      System::Windows::Forms::DialogResult::OK)
  {
    m_variable[a_buttonNumber]->Text = folderBrowserVariable->SelectedPath;
  }
}

void Form1::DoHandleVariableValueTextChange( System::Object^ a_modifiedObject )
{
  System::Windows::Forms::TextBox^ l_textbox =
    static_cast<System::Windows::Forms::TextBox^>(a_modifiedObject);

  DoCheckMainPath();

  if (System::IO::Directory::Exists(l_textbox->Text))
  {
    l_textbox->ForeColor = System::Drawing::Color::Green;
  }
  else
  {
    l_textbox->ForeColor = System::Drawing::Color::Red;
  }
}

void Form1::DoHandleVariableNameTextChange( int a_objectNum )
{
  a_objectNum -= 1;
  if (m_variableName[a_objectNum]->Text != "")
  {
    m_variable[a_objectNum]->Enabled = true;
    m_browseButtons[a_objectNum]->Enabled = true;
  }
  else
  {
    m_variable[a_objectNum]->Enabled = false;
    m_browseButtons[a_objectNum]->Enabled = false;
  }
}

void Form1::DoConvertSystemStringToCharString( System::String^ a_input,
                                              char* a_output )
{
  pin_ptr<const wchar_t> l_wch;
  l_wch = PtrToStringChars(a_input);
  size_t l_strLength = wcslen(l_wch) + 1;
  size_t l_convertedChars = 0;
  wcstombs_s(&l_convertedChars, a_output, l_strLength, l_wch, _TRUNCATE);
}

System::String ^ Form1::DoConvertCharStringToSystemString( const char* a_input )
{
  return (gcnew String(a_input));
}

};