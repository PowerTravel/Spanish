#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <Windows.h>
#include <algorithm>
#include <cassert>
#include <codecvt>
#include <random>
#include <limits>
#include <ios>
using namespace std;

/* Boilerplate feature-test macros: */
#if _WIN32 || _WIN64
#  define _WIN32_WINNT  0x0A00 // _WIN32_WINNT_WIN10
#  define NTDDI_VERSION 0x0A000002 // NTDDI_WIN10_RS1
#  include <sdkddkver.h>
#else
#  define _XOPEN_SOURCE     700
#  define _POSIX_C_SOURCE   200809L
#endif

#include <iostream>
#include <locale>
#include <locale.h>
#include <stdlib.h>
#include <string>

/* The Microsoft C and C++ runtime libraries that ship with Visual Studio, as
 * of 2017, have a bug that neither stdio, iostreams or wide iostreams can
 * handle Unicode input or output.  Windows needs some non-standard magic to
 * work around that.  This includes programs compiled with MinGW and Clang
 * for the win32 and win64 targets.
 *
 * NOTE TO USERS OF TDM-GCC: This code is known to break on tdm-gcc 4.9.2. As
 * a workaround, "-D MS_STDLIB_BUGS=0" will at least get it to compile, but
 * Unicode output will still not work.
 */

# include <io.h>
# include <fcntl.h>

using std::endl;
using std::istream;
using std::wcin;
using std::wcout;

void init_locale(void)
{
  constexpr char cp_utf16le[] = ".1200";
  setlocale( LC_ALL, cp_utf16le );
  _setmode( _fileno(stdout), _O_WTEXT );
  _setmode( _fileno(stdin), _O_WTEXT );
}

struct Noun {
  string article;
  string word;
};

enum class Language {
  SPANISH,
  ENGLISH,
  SWEDISH,
  UNKNOWN
};

struct Library
{
  map<Language, vector<Noun>> nouns;
};

string languageToString(Language lan)
{
  switch(lan)
  {
    case Language::SPANISH: return "Español";
    case Language::ENGLISH: return "English";
    case Language::SWEDISH: return "Svenska";
  }
  return "Unkonwn";
}

string toLowerCase(string str)
{
  std::transform(str.begin(), str.end(), str.begin(),
    [](unsigned char c){ return tolower(c); });
  return str;
}

Language stringToLanguage(string language)
{
  language = toLowerCase(language);
  if(language.compare("español") == 0 || language.compare("espanol") == 0 || language.compare("spanish") == 0 || language.compare("spanska") == 0)
  {
    return Language::SPANISH;
  }
  else if(language.compare("english")  == 0 ||
          language.compare("inglés")   == 0 ||
          language.compare("ingles")   == 0 ||
          language.compare("engelska") == 0)
  {
    return Language::ENGLISH;
  }
  else if(language.compare("svenska") == 0 ||
          language.compare("sueco")   == 0 ||
          language.compare("swedish") == 0)
  {
    return Language::SWEDISH;
  }

  assert(0);
  return Language::UNKNOWN;
}

string trim(string str)
{
  size_t begin = str.find_first_not_of(" \t");
  size_t end = str.find_last_not_of(" \t");
  if(end == str.length()-1)
  {
    end = string::npos;
  }
  return str.substr(begin, end);
}

vector<string> tokenize(string str, char token)
{
  vector<string> result;
  size_t begin = 0;
  size_t pos = 0;
  do{ 
    pos = str.find(token, begin);
    result.push_back(trim(str.substr(begin,pos)));
    begin = pos + 1;
  }while(pos != string::npos);
  
  return result;
}

Noun parseSpanishDefiniteNoun(string nounStr)
{
  Noun noun = {};
  vector<string> tokenizedNoun = tokenize(nounStr, ' ');
  noun.article = tokenizedNoun[0];
  noun.word = tokenizedNoun[1];
  return noun;
}

Noun parseSwedishDefiniteNoun(string nounStr)
{
  Noun noun = {};
  if(nounStr.find("en") == nounStr.length()-2 || 
     nounStr.find("an") == nounStr.length()-2 ||
     nounStr.find("yn") == nounStr.length()-2 ||
     nounStr.find("ln") == nounStr.length()-2)
  {
    noun.word = nounStr;
    noun.article = "en";
    return noun;
  }

  if(nounStr.find("et") == nounStr.length()-2)
  {
    noun.word = nounStr;
    noun.article = "ett";
    return noun;
  }

  noun.word = nounStr;
  noun.article = "";
  return noun;
}

Noun parse(string str, Language lan)
{
  switch(lan)
  {
    case Language::SPANISH: return parseSpanishDefiniteNoun(str);
    case Language::SWEDISH: return parseSwedishDefiniteNoun(str);
    default: return {};
  }
}

Library readFile(string path)
{
  Library lib = {};
  ifstream file(path);
  if(file.is_open())
  {
    string line;
    getline(file, line);
    vector<string> langs = tokenize(line, ',');
    vector<Language> languages;
    for(string lan : langs)
    {
      languages.push_back(stringToLanguage(lan));
    }

    while(getline(file, line))
    {
      vector<string> tokenizedLine = tokenize(line, ',');

      assert(tokenizedLine.size() == languages.size());
      for(int i = 0; i < tokenizedLine.size(); ++i)
      {
        lib.nouns[languages[i]].push_back(parse(tokenizedLine[i], languages[i]));
      }
    }
  }

  return lib;
}

wstring stringToW(string str)
{
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(str);
}

string wToString(wstring str)
{
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.to_bytes(str);
}

void printToConsole(string outputString)
{
    wcout << stringToW(outputString) << endl; 
}

string readInputFromConsole()
{
  static constexpr size_t bufsize = 1024;
  std::wstring input;
  input.reserve(bufsize);
  wcin >> input;
  string str = wToString(input);
  const char* str2 = str.c_str();
  printToConsole(str.length() + " " + str);
  if(str.find_first_of('\n') != string::npos)
  {
    int a = 10;
  }
  auto limit2 = (numeric_limits<bool>::max)();
  auto limit = (numeric_limits<streamsize>::max)();
  cin.ignore(limit);
  return str;
}

vector<int> generateRandomWordList(Library lib)
{
  static bool randomInitiated = false;
  static mt19937 g;
  if(!randomInitiated)
  {
    random_device rd;
    g = mt19937(rd());
    randomInitiated = true;
  }

  vector<int> list;
  for (int i = 0; i < lib.nouns[Language::SPANISH].size(); ++i)
  {
    list.push_back(i);
  }
  shuffle(list.begin(), list.end(), g);
  return list;
}

bool quit(string input)
{
  //      printToConsole("Sure you want to quit? (y/n)");
  //      input = readInputFromConsole();
  //      if(input.compare("y") == 0 || input.compare("yes") == 0){
  //        i--;
          return true;
  //      }
}

bool equals(string a, string b)
{
  return a.compare(b) == 0;
}

void printHelp()
{
  printToConsole("Commands:");
  printToConsole("  -l --language [se/es] [se/es]");
}

bool startsWith(string str, string substr)
{
  return str.find_first_of(substr) == 0;
}

int main(int argc, char* atgv[]) 
{
  init_locale();


  Library lib = readFile("library.txt");

  const vector<int> randomList = generateRandomWordList(lib);
  
  Language qLan = Language::SWEDISH;
  Language aLan = Language::SPANISH;

  for (int i = 0; i < randomList.size(); ++i)
  {
    Noun qWord = lib.nouns[qLan][randomList[i]];
    Noun aWord = lib.nouns[aLan][randomList[i]];
    printToConsole(qWord.article + " " + qWord.word + " = ");
    string input = trim(readInputFromConsole());
    if(input.length())
    {
      if(equals(input,"q"))
      {
        if(quit(input))
          return 0;
      }
      else if(equals(input,"--help") || equals(input,"?") || equals(input,"-h"))
      {
        printHelp();
      }
      else if(startsWith(input, "-"))
      {
        input = toLowerCase(input);
        if(startsWith(input, "-l") || startsWith(input, "--language"))
        {
          vector<string> tokens = tokenize(input, ' ');
          if(tokens.size() != 3)
          {
            printToConsole("invalid command");
            printHelp();
          }else{
            if(equals(tokens[1],"es"))
            {
              qLan = Language::SPANISH;
            }else if (equals(tokens[1],"se"))
            {
              qLan = Language::SWEDISH;
            }else{
              printToConsole("'" + tokens[1] + " is an invalid country code");
              printHelp();
            }

            if(equals(tokens[2],"es"))
            {
              qLan = Language::SPANISH;
            }else if (equals(tokens[2],"se"))
            {
              qLan = Language::SWEDISH;
            }else{
              printToConsole("'" + tokens[2] + " is an invalid country code");
              printHelp();
            }
          }
        }else{
          printToConsole("invalid command");
          printHelp();
        }
      }
      else if(equals(input, aWord.word))
      {
        printToConsole("Correct!");
      }else{
        printToConsole("Should be " + aWord.word);
      }
    }
  }
  return 0;
}