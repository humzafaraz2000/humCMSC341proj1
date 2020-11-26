#include <iostream>
#include "Graph.h"

using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

// Constructor - DO NOT MODIFY
Graph::Graph(int n) {
  if (n <= 0)
    throw invalid_argument("Graph::Graph(): number of vertices must be positive");

  _rows = new EntryList*[n];
  for (int i = 0; i < n; i++) {
    _rows[i] = new EntryList();
  }
  _numVert = n;
  _numEdge = 0;
}

Graph::Graph(const Graph& G) {
  _rows = new EntryList*[G._numVert];
  for (int i = 0; i < G._numVert; i++){
    _rows[i] = G._rows[i];
  }
  _numVert = G._numVert;
  _numEdge = G._numEdge;
}

const Graph& Graph::operator=(const Graph& rhs) {
  if (this != &rhs){
    //destructor
    for (int i = 0; i < _numVert; i++){
      delete _rows[i];
    }
    _numVert = 0;
    _numEdge = 0;
    //constructor
    _rows = new EntryList*[rhs._numVert];
    for (int i = 0; i < rhs._numVert; i++){
       _rows[i] = new EntryList();
    }
    _numVert = rhs._numVert;
    _numEdge = rhs._numEdge; 
  }
  else{
    cout << "No self-assignment!" << endl;
  }
  return *this;
}

Graph::~Graph() {
  _numVert = 0;
  _numEdge = 0;
}

// Number of vertices - DO NOT MODIFY
int Graph::numVert() const {
  return _numVert;
}

// Number of edges - DO NOT MODIFY
int Graph::numEdge() const {
  return _numEdge;
}

void Graph::addEdge(int u, int v, weight_t x) {
  EntryList::Entry e(v, x);
  bool check;
  for (int i = 0; i < _numVert; i++){
    check = _rows[u]->insert(e);
    if (check == true){
      _numEdge++;
    }
  }
}

bool Graph::removeEdge(int u, int v) {
  EntryList::Entry e;
  for (int i = 0; i < _numVert; i++){
    bool remove = _rows[u]->remove(v, e);
    if (remove == true){
      _numEdge--;
    }
  }
}


// Dump the graph - DO NOT MODIFY
void Graph::dump() const {

  cout << "Dump of graph (numVert = " << _numVert
       << ", numEdge = " << _numEdge << ")" << endl;

  for (int i = 0; i < _numVert; i++) {
    cout << "Row " << i << ": \n";
    _rows[i]->dump();
  }
}


Graph::EgIterator::EgIterator(Graph *Gptr, bool enditr) {
  _Gptr = Gptr;
  if (enditr == false){
    _itr = _Gptr->_rows[0]->begin();
    _row = 0;
  }
  else{
    _itr = _Gptr->_rows[Gptr->_numVert]->end();
    _row = Gptr->_numVert;
  }
}
  
tuple<int,int,weight_t> Graph::EgIterator::operator*() {
  EntryList::Entry e = *_itr;
  tuple <int, int, weight_t> product;
  product = std::make_tuple(_row, e.getVertex(), e.getWeight());
  return product;
}

bool Graph::EgIterator::operator!=(const EgIterator& rhs) {
  return _itr != rhs._itr;
}

void Graph::EgIterator::operator++(int dummy) {
  _row++;
}

Graph::EgIterator Graph::egBegin() {
  Graph::EgIterator it(this, 0);
  return it;
}
 
Graph::EgIterator Graph::egEnd() {
  Graph::EgIterator it(this, 1);
  return it;
}
 
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool enditr) {
  _Gptr = Gptr;
  _row = v;
  if (enditr == false){
    _itr = _Gptr->_rows[0]->begin();
    _row = 0;
  }
  else{
    _itr = _Gptr->_rows[Gptr->_numVert]->end();
    _row = Gptr->_numVert;
  }
}

bool Graph::NbIterator::operator!=(const NbIterator& rhs) {
  return _itr != rhs._itr;
}

void Graph::NbIterator::operator++(int dummy) {
  _row++;
}

pair<int,weight_t> Graph::NbIterator::operator*() {
  EntryList::Entry e = *_itr;
  pair<int, weight_t> product;
  product.first = e.getVertex();
  product.second = e.getWeight();
  return product;
}

Graph::NbIterator Graph::nbBegin(int v) {
  Graph::NbIterator it(this, v, 0);
}

Graph::NbIterator Graph::nbEnd(int v) {
  Graph::NbIterator it(this, v, 1);
  return it;
}
