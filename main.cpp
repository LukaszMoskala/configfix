/*
Copyright (C) 2019 Łukasz Konrad Moskała

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "version.hpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <errno.h>
using namespace std;

//this string contains characters, that indicate comments in file
string commentCharacters = "#;";

//returns true if c is whitespace
bool isWhistespace(char c) {
  return (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

string removeTailingWhitespaces(string s) {
  int lastChar=0;
  for(int i=s.length()-1;i>=0 && lastChar == 0;i--) {
    if(!isWhistespace(s[i])) lastChar=i;
  }
  return s.substr(0, lastChar+1);
}
//returns first non-whitespace character, not it's position!
char firstNonWhitespaceCharacter(string s) {
  for(int i=0;i<s.size();i++) {
    if(!isWhistespace(s[i])) return s[i];
  }
  return 0;
}
int main(int args,char** argv) {
  if(args == 2 && (string(argv[1]) == "-h" || string(argv[1]) == "--help")) {
    cerr<<"Configfix Copyright (C) 2019 Łukasz Konrad Moskała ukasz_moskala8@tlen.pl"<<endl;
    cerr<<"This program comes with ABSOLUTELY NO WARRANTY."<<endl;
    cerr<<"This is free software, and you are welcome to redistribute it"<<endl;
    cerr<<"under certain conditions; Read attached license file for details."<<endl;
    cerr<<endl;
    cerr<<"You should have received a copy of the GNU General Public License"<<endl;
    cerr<<"along with this program.  If not, see <https://www.gnu.org/licenses/>."<<endl;
    cerr<<endl;
    cerr<<"Configfix: program to remove empty lines, comments and trailing whitespaces from files"<<endl;
    cerr<<"usage: configfix /path/to/file"<<endl;
    cerr<<"       configfix relative/path"<<endl;
    cerr<<"Reading from STDIN is supported, just don't pass any parameters"<<endl;
    cerr<<"Current file will be saved as <filename>.bak"<<endl;
    cerr<<"If it exist, it'll be overwritten"<<endl;
    return 0;
  }
  if(args == 2 && (string(argv[1]) == "-v" || string(argv[1]) == "--version")) {
    cerr<<"Configfix "<<VERSION<<endl;
    return 0;
  }
  ifstream ifs;
  ofstream ofs;
  bool useStdin=true;

  if(args > 1) {
    //more than 1 argument, so we'r not using STDIN
    useStdin=false;
    string fname=argv[1];
    string newname=fname+".bak";

    //move file to file.bak

    if(rename(fname.c_str(),newname.c_str())) {
      cerr<<"Failed to move "<<fname<<" to "<<newname<<": "<<strerror(errno)<<endl;
      return 1;
    }

    //open moved file, because we need to read from somewhere
    ifs.open(newname.c_str());
    if(!ifs.is_open()) {
      cerr<<"Failed to open "<<newname.c_str()<<" to read, check permissions."<<endl;
      return 1;
    }
    //and another file for writing
    ofs.open(fname.c_str());
    if(!ofs.is_open()) {
      cerr<<"Failed to open "<<fname.c_str()<<" to write, check permissions."<<endl;
      ifs.close();
      return 1;
    }
  }
  string line; //currently processed line

  //If we'r using file, check if there is anything left to read
  //same with stdin
  while( ( !useStdin && ifs.good() ) || ( useStdin && cin.good() ) ) {

    //read line from stdin or file
    if(useStdin)
      getline(cin,line);
    else
      getline(ifs, line);

    //skip empty lines
    if(line.length() == 0)
      continue;
    //find starting position of comment
    for(int i=0;i<commentCharacters.size();i++) {

      char currentCharacter=commentCharacters[i];

      //convert char to string, dirty hack but works
      string tmp=" ";
      tmp[0]=currentCharacter;

      int charpos=line.find(tmp);

      //line begins with comment, skip it
      if(charpos == 0)
        continue;

      //find first non-whitespace character
      char c=firstNonWhitespaceCharacter(line);

      //if it's comment OR 0 (that means, string contains only whitespaces)
      //then skip that line
      if(c == currentCharacter || c == 0)
        continue;
      //comment exist, and isn't the only thing on that line
      //so remove it
      if(charpos > -1) {
        line=line.substr(0, charpos);
      }
    }
    //remove tailing whitespaces
    line=removeTailingWhitespaces(line);

    //and finally, print line
    if(useStdin)
      cout<<line<<endl;
    else
      ofs<<line<<endl;
  }
  //close file if opened
  if(!useStdin)
    ofs.close();
  return 0;
}
