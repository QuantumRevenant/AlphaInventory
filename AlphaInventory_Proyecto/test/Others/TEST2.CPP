#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  int width = 100;
  string text = "Hello World";

  int padding = (width - text.length()) / 2;
  cout << setw(width) << setiosflags(ios::left) << setfill(' ') << setw(padding) << "" << text << endl;

  return 0;
}