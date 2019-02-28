//============================================================================
// Name        : Fstream.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <fstream>
#include <cstdio>

int main()
{
 std::fstream src,dest;

  src.open("test.txt");
  dest.open("copy.txt");

  std::filebuf* inbuf = src.rdbuf();
  std::filebuf* outbuf = dest.rdbuf();

  char c = inbuf->sbumpc();

  while( c != EOF ) {
    outbuf->sputc(c);
    c = inbuf->sbumpc();
  }

  dest.close();
  src.close();

  return 0;
}
