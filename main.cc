#include <map>
#include <iostream>
using namespace std;


int main() {
  map<string, int> m;    // constructs an empty map
  m["a"] = 2;
  m["b"] = 2;

  cout << m["a"] << endl;   // print 2
  cout << m["c"] << endl;   // if key is not found, it is inserted, value is default constructed
  m.erase("a");  
  
}