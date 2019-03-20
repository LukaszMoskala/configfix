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
//value passed from command line, assigned in main
string commentCharacters;

//returns true if c is whitespace
bool isWhitespace(char c) {
  return (c == '\t' || c == '\n' || c == '\r' || c == ' ');
}

string removeTailingWhitespaces(string s) {
  int lastChar=0;
  for(int i=s.length()-1;i>=0 && lastChar == 0;i--) {
    if(!isWhitespace(s[i])) lastChar=i;
  }
  return s.substr(0, lastChar+1);
}
//returns first non-whitespace character, not it's position!
char firstNonWhitespaceCharacter(string s) {
  for(int i=0;i<s.size();i++) {
    if(!isWhitespace(s[i])) return s[i];
  }
  return 0;
}
int args;
char **argv;
//parses argument
//format:
// --longname value
// -shortname value

//shortname should be only 1 character in length!
string getarg(string shortname, string longname, string defval) {
  for(int i=1;i<args;i++) {
    string ca(argv[i]);
    if( ( ca == "--"+longname  || ca == "-"+shortname ) && i+1 < args ) {
      return string(argv[i+1]);
    }
  }
  return defval;
}
bool argexist(string shortname, string longname) {
  for(int i=0;i<args;i++) {
    string ca(argv[i]);
    if( ca == "--"+longname  || ca == "-"+shortname ) {
      return true;
    }
  }
  return false;
}
struct stats_t {
  uint16_t removedComments=0;
  uint16_t removedEmptyLines=0;
  uint16_t removedCharacters=0;
  uint16_t tailingWhitespacesRemoved=0;
} stats;
int main(int _args,char** _argv) {
  args=_args;
  argv=_argv;
  if(argexist("h","help")) {
    cerr<<"Configfix Copyright (C) 2019 Łukasz Konrad Moskała ukasz_moskala8@tlen.pl"<<endl;
    cerr<<"This program comes with ABSOLUTELY NO WARRANTY."<<endl;
    cerr<<"This is free software, and you are welcome to redistribute it"<<endl;
    cerr<<"under certain conditions; Read attached license file for details."<<endl;
    cerr<<endl;
    cerr<<"You should have received a copy of the GNU General Public License"<<endl;
    cerr<<"along with this program.  If not, see <https://www.gnu.org/licenses/>."<<endl;
    cerr<<endl;
    cerr<<"Configfix: program to remove empty lines, comments and trailing whitespaces from files"<<endl;
    cerr<<"usage: configfix -f /path/to/file"<<endl;
    cerr<<"       configfix -f relative/path"<<endl;
    cerr<<endl;
    cerr<<"Additional options: "<<endl;
    cerr<<"       -n --nostats      | Don't display statistics"<<endl;
    cerr<<"       -V --version      | display version and compilation time"<<endl;
    cerr<<"       -O --oversion     | display only version"<<endl;
    cerr<<"       -h --help         | this message"<<endl;
    cerr<<"       -c --commentchars | Specify characters that indicates comment"<<endl;
    cerr<<"Current file will be saved as <filename>.bak"<<endl;
    cerr<<"If it exist, it'll be overwritten"<<endl;
    return 0;
  }
  //display to STDOUT not STDERR because this is usefull in scripts
  if(argexist("V","version")) {
    cout<<"Configfix "<<VERSION<<" compiled "<<__DATE__<<" "<<__TIME__<<endl;
    return 0;
  }
  //display only version without any other informations
  if(argexist("O","oversion")) {
    cout<<VERSION<<endl;
    return 0;
  }
  //characters that indicates comments
  commentCharacters=getarg("c","commentchars","#;");
  //for file IO handling
  ifstream ifs;
  ofstream ofs;
  //when set to true, program reads STDIN and outputs to STDOUT
  bool useStdin=true;
  //get filename from command line
  string fname="-";
  if(args == 2) {
    fname=argv[1];
    if(fname.find("-") == 0 && fname != "-") { //that was not a file name
      fname=getarg("f","filename","-");
    }
  }
  //if filename is not '-', use files
  if(fname != "-") {
    //tell program that we'r not using STDIN
    useStdin=false;
    //generate new file name for backup
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

    //find starting position of comment
    for(int i=0;i<commentCharacters.size() && line.size();i++) {

      char currentCharacter=commentCharacters[i];

      //Find position of character that indicates comment
      int charpos=line.find(currentCharacter);

      //line begins with comment, skip it
      if(charpos == 0) {
        stats.removedCharacters+=line.size();
        stats.removedComments++;
        //setting line to empty will force program to skip it when writting
        //side effect: causes it to be counted in statistics as empty line
        line="";
        break;
      }

      //find first non-whitespace character
      char c=firstNonWhitespaceCharacter(line);

      //if it's comment OR 0 (that means, string contains only whitespaces)
      //then skip that line
      if(c == currentCharacter || c == 0) {
        stats.removedCharacters+=line.size();
        stats.removedComments++;
        line="";
        break;
      }

      //comment exist, and isn't the only thing on that line
      //so remove only the comment, not entire line
      if(charpos > -1) {
        int i0=line.size();
        line=line.substr(0, charpos);
        int i1=line.size();
        int i2=i0-i1;
        stats.removedCharacters+=i2;
        stats.removedComments++;
        break;
      }
    }
    //skip empty lines
    //We can't put this before removing comments
    //because line after removing comments may be empty
    //so we have to check if this is the case
    if(line.length() == 0) {
      stats.removedEmptyLines++;
      continue;
    }
    //remove tailing whitespaces
    int i0=line.size();
    line=removeTailingWhitespaces(line);
    stats.tailingWhitespacesRemoved+=(i0-line.size());
    //and finally, print line
    if(useStdin)
      cout<<line<<endl;
    else
      ofs<<line<<endl;
  }
  //close file if opened
  if(!useStdin)
    ofs.close();
  if(!argexist("n","nostats")) {
    cerr<<"Removed tailing whitespaces: "<<stats.tailingWhitespacesRemoved<<endl;
    cerr<<"Removed comments: "<<stats.removedComments<<endl;
    cerr<<"        (characters: "<<stats.removedCharacters<<")"<<endl;
    cerr<<"Removed empty lines: "<<stats.removedEmptyLines<<endl;
  }
  return 0;
}
