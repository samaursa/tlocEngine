#ifndef PATH_BAT_MANAGER_H
#define PATH_BAT_MANAGER_H

#include <string>
#include <vector>

struct Variable;

class PathBatManager
{
public:
  PathBatManager();
  ~PathBatManager();

  enum RETURN_VALUE
  {
    NO_ERROR = 0,
    FILE_NOT_FOUND,
    SYNTAX_ERROR,

    RETURN_VALUE_END
  };

  int LoadPathFiles(const char* a_fileDir, bool a_onlyTemplate);

  const char* GetStatus();

  const size_t GetNumVariables();
  const char* GetVariableNameAtIndex(size_t a_index);
  const char* GetVariableValueAtIndex(size_t a_index);

  const void ClearVariables();
  const void PushBackVariable(const char* a_variableName, const char* a_variableValue);

  const void SaveFile(const char* a_fileDir);

  const void Reset();

private:

  int DoLoadPathFile(const char* a_fileDir, const char* a_fileName, 
                     bool a_overwriteExistingEntries);

  std::string m_header;
  std::string m_footer;

  enum STATE
  {
    HEADER = 0, 
    BODY, 
    FOOTER,
    FINISHED,
              
    STATE_END
  };

  void DoDetectAndChangeState(std::string& a_currentLine, STATE& a_currentState);

  std::string m_status;

  void DoParseVariableLine(std::string& a_currentLine, bool a_overwrite, 
                           std::string& a_appendComments);

  std::vector<Variable> m_variables;
};

struct Variable
{
  std::string m_variableName;
  std::string m_variableValue;
};

#endif