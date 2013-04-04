#include "stdafx.h"
#include "PathBatManager.h"

#include <fstream>
#include <algorithm>

PathBatManager::PathBatManager()
{
}

PathBatManager::~PathBatManager()
{
}

int PathBatManager::LoadPathFiles(const char* a_fileDir, bool a_onlyTemplate)
{
  int ret = NO_ERROR;
  bool l_pathBatFound = false;
  bool l_pathBatTemplateFound = false;

  if (!a_onlyTemplate)
  {
    ret = DoLoadPathFile(a_fileDir, "Paths.bat", true);

    switch (ret)
    {
    case NO_ERROR:
      l_pathBatFound = true;
      break;
    case FILE_NOT_FOUND:
      l_pathBatFound = false;
      break;
    default:
      return ret;
      break;
    }
  }
  

  ret = DoLoadPathFile(a_fileDir, "Paths.bat.template", false);

  switch (ret)
  {
  case NO_ERROR:
    l_pathBatTemplateFound = true;
    break;
  case FILE_NOT_FOUND:
    l_pathBatTemplateFound = false;
    break;
  default:
    return ret;
    break;
  }

  if (l_pathBatFound || l_pathBatTemplateFound)
  {
    return NO_ERROR;
  }
  else
  {
    m_status = std::string("Path.bat and Path.bat.template cannot be found");
    return FILE_NOT_FOUND;
  }
}

const char* PathBatManager::GetStatus()
{
  return m_status.c_str();
}

const size_t PathBatManager::GetNumVariables()
{
  return m_variables.size();
}

const char* PathBatManager::GetVariableNameAtIndex(size_t a_index)
{
  return m_variables[a_index].m_variableName.c_str();
}

const char* PathBatManager::GetVariableValueAtIndex(size_t a_index)
{
  return m_variables[a_index].m_variableValue.c_str();
}

const void PathBatManager::ClearVariables()
{
  m_variables.clear();
}

const void PathBatManager::PushBackVariable(const char* a_variableName, const char* a_variableValue)
{
  Variable l_tempVariable;
  l_tempVariable.m_variableName = std::string(a_variableName);
  l_tempVariable.m_variableValue = std::string(a_variableValue);

  m_variables.push_back(l_tempVariable);
}

const void PathBatManager::SaveFile(const char* a_fileDir)
{
  char l_pathLoc[512];
  strcpy(l_pathLoc, a_fileDir);
  strcat_s(l_pathLoc, "/");
  strcat_s(l_pathLoc, "Paths.bat");

  std::ofstream l_file(l_pathLoc);

  l_file << m_header;
  l_file << "\n";

  std::vector<Variable>::iterator l_itr = m_variables.begin();
  std::vector<Variable>::iterator l_endItr = m_variables.end();
  for (/**/; l_itr != l_endItr; ++l_itr)
  {
    l_file << "SET " << l_itr->m_variableName << "=" << l_itr->m_variableValue << "\n";
  }

  l_file << "\n";
  l_file << m_footer;

  l_file.close();
}

const void PathBatManager::Reset()
{
  ClearVariables();
  m_header.clear();
  m_footer.clear();
}

int PathBatManager::DoLoadPathFile(const char* a_fileDir, const char* a_fileName, 
                                   bool a_overwriteExistingEntries)
{
  char l_pathLoc[512];    
  strcpy(l_pathLoc, a_fileDir);
  strcat_s(l_pathLoc, "/");
  strcat_s(l_pathLoc, a_fileName);

  std::ifstream pathFile(l_pathLoc);

  int ret = NO_ERROR;

  if (pathFile.good())
  {
    std::string l_tempHeader;
    std::string l_tempFooter;

    std::string l_currentLine;
    STATE l_state = HEADER;

    while(!pathFile.eof())
    {
      getline(pathFile, l_currentLine);

      if (l_state == HEADER)
      {
        DoDetectAndChangeState(l_currentLine, l_state);

        l_tempHeader.append(l_currentLine);
        l_tempHeader.append("\n");
      }
      else if (l_state == BODY)
      {
        DoDetectAndChangeState(l_currentLine, l_state);
        
        DoParseVariableLine(l_currentLine, a_overwriteExistingEntries, l_tempFooter);
      }
      else if (l_state == FOOTER)
      {
        DoDetectAndChangeState(l_currentLine, l_state);

        l_tempFooter.append(l_currentLine);
        l_tempFooter.append("\n");
      }
    }
    if (l_state != FOOTER)
    {
      ret = SYNTAX_ERROR;
      m_status = std::string(a_fileName);
      m_status.append(" has a syntax error");
    }
    else
    {
      if ((!m_header.empty() && a_overwriteExistingEntries) || m_header.empty())
      {
        m_header = l_tempHeader;
      }

      if ((!m_footer.empty() && a_overwriteExistingEntries) || m_footer.empty())
      {
        m_footer = l_tempFooter;
      }

      m_status = std::string(a_fileName);
      m_status.append(" found");
    }

    pathFile.close();
  }
  else
  {
    ret = FILE_NOT_FOUND;
    m_status = std::string(a_fileName);
    m_status.append(" not found");
  }

  return ret;
}

void PathBatManager::DoDetectAndChangeState(std::string& a_currentLine,
                                            STATE& a_currentState)
{
  char l_currentLine[512];
  strcpy(l_currentLine, a_currentLine.c_str());
  
  char* l_currentWord;
  l_currentWord = strtok(l_currentLine, " ");
  if (l_currentWord != NULL)
  {
    if (!strcmp(l_currentWord, ":::"))
    {
      l_currentWord = strtok(NULL, " ");

      if (!strcmp(l_currentWord,"SET_ABSOLUTE_PATHS"))
      {
        a_currentState = BODY;
      }
      else if (!strcmp(l_currentWord,"END_SET_ABSOLUTE_PATHS"))
      {
        a_currentState = FOOTER;
      }
    }
  }
}

void PathBatManager::DoParseVariableLine(std::string& a_currentLine, 
                                         bool a_overwrite,
                                         std::string& a_appendComments)
{
  int ret = NO_ERROR;
  
  char l_currentLine[512];
  strcpy(l_currentLine, a_currentLine.c_str());

  char* l_currentWord;
  l_currentWord = strtok(l_currentLine, " ");
  
  if (l_currentWord != NULL)
  {
    if (!strcmp(l_currentWord, "SET"))
    { 
      Variable l_currentVar;
      l_currentWord = strtok(NULL, " =");
      l_currentVar.m_variableName = std::string(l_currentWord);
      
      l_currentWord = strtok(NULL, " ");
      l_currentVar.m_variableValue = std::string(l_currentWord);

      bool l_found = false;
      std::vector<Variable>::iterator l_itr = m_variables.begin();
      std::vector<Variable>::iterator l_endItr = m_variables.end();
      for (/* */; l_itr != l_endItr; ++l_itr)
      {
        if (!(l_currentVar.m_variableName.compare(l_itr->m_variableName)))
        {
          if (a_overwrite)
          {
            l_itr->m_variableValue = l_currentVar.m_variableValue;
          }
          l_found = true;
        }
      }

      if (!l_found)
      {
        m_variables.push_back(l_currentVar);
      }
    }
    else
    {
      a_appendComments.append(a_currentLine);
      a_appendComments.append("\n");
    }
  }
}