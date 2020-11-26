#include <iostream>
#include <stdexcept>    
#include <tuple> 
#include "Graph.h"
#include "EntryList.h"

using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;
using std::range_error;

int main(){
  EntryList el;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test size and capacity" << endl;
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test insert" << endl;
  for (int i = 1; i < 13; i++) {
    el.insert( EntryList::Entry((i*5)%13, i) );
  }
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test update" << endl;
  for (int i = 2; i < 13; i+=2) {
    el.update( EntryList::Entry(i, 2*i) );
  }
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test getEntry" << endl;
  EntryList::Entry e;
  el.getEntry(1, e);
  cout << "Vertex: " << e.getVertex() << " Weight: " << e.getWeight() << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test remove" << endl;
  for (int i = 1; i < 13; i+=2) {
    el.remove(i, e);
  }
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;  
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test duplicate" << endl;
  bool insertCheck = el.insert( EntryList::Entry(2, 5));
  cout << "Should be false" << endl << "InsertCheck: " << insertCheck << endl;
  //--------------------------------------------------------------------------------------------------------------------- 
  cout << "Test copy constructor" << endl;
  EntryList copy(el);
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test assignment operator" << endl;
  EntryList assign = el;
  cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test deep copy (entries are removed from assign then e is printed, should stay the same)" << endl;
  for (int i = 3; i < 13; i*=2) {
    assign.remove(i, e);
  }
  el.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test contraction (should have size of 10 now)" << endl;
  cout << "size: " << assign.size() << ", capacity: " << assign.capacity() << endl;
  assign.dump();
  cout << endl;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test self assignment" << endl;
  EntryList selfTest = el;
  selfTest = selfTest;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test copy and assignment function correctly when the source object is empty (nothing should print)." << endl;
  EntryList copyEmptyTest;
  EntryList assignEmptyTest;
  EntryList empty(copyEmptyTest);
  EntryList empty2 = assignEmptyTest;
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test bool functions and range_error" << endl;
  EntryList::Entry test (20, 10);
  bool insert = el.insert(EntryList::Entry(20, 30));
  bool update = el.update(test);
  bool remove = el.remove(test.getVertex(), test);
  cout << "All should be 1(true)" << endl << "Insert: " << insert << " Update: " << update
    << " Remove: " << remove << endl;
  //EntryList::Entry throwTest;
  //throwTest = el.at(100);
  //---------------------------------------------------------------------------------------------------------------------
  
  Graph G(5) ;
  cout << "GRAPH TESTING" << endl;
  //--------------------------------------------------------------------------------------------------------------------- 
  cout << "Test insert" << endl;
  G.addEdge(3,4,11);
  G.addEdge(1,4,12);
  G.addEdge(0,3,13);
  G.addEdge(0,4,14);
  G.addEdge(0,1,15);
  G.addEdge(1,2,16);
  G.addEdge(2,4,17);
  G.dump();
  //--------------------------------------------------------------------------------------------------------------------- 
  cout << "Test remove" << endl;
  G.removeEdge(3,4);
  G.removeEdge(0,4);
  G.removeEdge(1,2);
  G.dump();
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test copy constructor" << endl;
  Graph H(G);
  H.dump();
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test assignment operator" << endl;
  Graph I = G;
  I.dump();
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test deep copy (should stay the same)" << endl;
  I.removeEdge(2,4);
  G.dump();
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Test copy and assignment function correctly when the source object is empty  (nothing should print)" << endl;
  /*
  //Throws invalid argument
  Graph graph(0);
  Graph assignTest = graph;
  Graph copyTest(graph);
  assignTest.dump();
  copyTest.dump();
  */
  //---------------------------------------------------------------------------------------------------------------------
  cout << "Check self-assignment" << endl;
  Graph newTest(5);
  newTest = newTest;
    
  return 0;
}
