//(C) 2019 Łukasz Konrad Moskała <lm@lukaszmoskala.pl>
// this code is in the public domain 
#include <iostream>
#include <fstream>
#include <inttypes.h>
using namespace std;
int main() {
  ifstream f;
  f.open("LICENSE");
  if(!f.is_open())
    return 1;
  size_t len=0;
  f.seekg(0, ios_base::end);
  len=f.tellg();
  f.seekg(0);
  char data[len];
  f.read(data, len);
  f.close();
  cout<<" char GNU_GPL_V3_LICENSE["<<len+1<<"] = {";
  for(size_t i=0; i<len; i++) {
    cout<<"0x";
    cout<<hex<<(int)data[i];
    cout<<",";
  }
  cout<<"0x0};";
  return 0;
}