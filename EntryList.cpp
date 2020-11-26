#include "EntryList.h"

using std::cout;
using std::endl;
using std::range_error;

// Constructor - DO NOT MODIFY
EntryList::EntryList() {
  _array = new Entry[DEFAULT_SIZE];
  _capacity = DEFAULT_SIZE;
  _size = 0;
}

EntryList::EntryList(const EntryList& rhs) {
  _capacity = rhs._capacity;
  _size = rhs._size;
  _array = new Entry[_capacity];
  for (int i = 0; i < _size; i++){
    _array[i] = rhs._array[i];
  }
}

const EntryList& EntryList::operator=(const EntryList& rhs) {
  if (this != &rhs){
    //destructor
    delete[] _array;
    _size = 0;
    _capacity = 0;
    //copy constructor
    _capacity = rhs._capacity;
    _size = rhs._size;
    _array = new Entry[_capacity];
    for (int i = 0; i < _size; i++){
      _array[i] = rhs._array[i];
    }
  }
  else{
    cout << "No self-assignment!" << endl;
  }
  return *this;
}
  
EntryList::~EntryList() {
  delete[] _array; 
  _size = 0;
  _capacity = 0;
}

bool EntryList::insert(const Entry& e) {
  //check if already exists
  //cout << "check if it exists" << endl;
  /*
  EntryList::Iterator it;
  for (it = begin(); it != end(); it++){
    Entry entry = *it;
    if (entry.getVertex() == e.getVertex()){
      cout << "Already exists!" << endl;
      return false;
    }
  }
  */
  for (int i = 0; i < _size; i++){
    if (_array[i].getVertex() == e.getVertex()){
      //cout << "Already exists!" << endl;
      return false;
    }    
  }
  //expansion
  //cout << "expansion" << endl;
  if (_size + 1  >= _capacity){
    int newCap = _capacity * 2;
    Entry* temp = new Entry[newCap];    
    for (int i = 0; i < _capacity; i++){
      temp[i] = _array[i];
    }
    delete[] _array;
    _capacity *= 2;
    //_array = new Entry[_capacity];
    _array = temp;  
  }
  _array[_size] = e;
  _size++;
  //sort it to be in ascending order
  Entry temp;
  for (int i = 0; i < _size; i++){
    for (int j = i + 1; j < _size; j++){
      if (_array[i].getVertex() > _array[j].getVertex()){
        temp = _array[i];
        _array[i] = _array[j];
        _array[j] = temp;
      }
    }
  }
  return true;
}
  
bool EntryList::update(const Entry& e) {
  /*
  EntryList::Iterator it;
  for (it = begin(); it != end(); it++){
    Entry entry = *it;
    if (entry.getVertex() == e.getVertex()){
      _array[entry.getVertex()].setWeight(e.getWeight());
      return true;
    }
  }
  */
  for (int i = 0;  i < _size; i++){
    if (_array[i].getVertex() == e.getVertex()){
      _array[i].setWeight(e.getWeight());
      return true;
    }
  }
  return false;
}

bool EntryList::getEntry(int vertex, Entry &ret) {
  /*
  EntryList::Iterator it;
  for (it = begin(); it != end(); it++){
    EntryList::Entry e = *it;
    if (e.getVertex() == vertex){
      return true;
    }
  }
  */
  for (int i = 0; i < _size; i++){
    if (_array[i].getVertex() == vertex){
      ret = _array[i];
      return true;
    }
  }
  return false;
}

bool EntryList::remove(int vertex, Entry &ret) {
  /*
  EntryList::Iterator it;
  int count = 0;
  for (it = begin(); it != end(); it++){
    EntryList::Entry e = *it;
    if (e.getVertex() == vertex){
      cout << "in if statement" << endl;
      //set entry to be deleted to ret
      //move each entry over 1 to overlap
      //decrease size
      //decrease capacity if needed
      ret = *it;
      //delete _array[count];
      for (int i = count - 1; i < _size - 1; i++){
        _array[i] = _array[i+1];
      }
      _size--;
      //contraction
      if (_size < (_capacity/4)){
        if (_capacity > DEFAULT_SIZE){
          int newCap = _capacity / 2;
          Entry temp[newCap];    
          for (int i = 0; i < newCap; i++){
            temp[i] = _array[i];
          }
          delete _array;
          _capacity /= 2;
          _array = new Entry[_capacity];
          _array = temp;  
        }
      }
      return true;
    }
    count++;
  }
  cout << "count" << count << endl;
  */
  for (int i = 0; i < _size; i++){
    if(_array[i].getVertex() == vertex){
      ret = _array[i];
      //delete _array[count];
      //????
      for (int j = i - 1; i < _size - 1; i++){
        _array[i] = _array[i+1];
      }
      EntryList::Entry e;
      _array[_size - 1] = e;
      _size --;
      //contraction
      if (_size <= (_capacity/4)){
        if (_capacity > DEFAULT_SIZE){
          int newCap = _capacity / 2;
          Entry* temp = new Entry[newCap];    
          for (int i = 0; i < newCap; i++){
            temp[i] = _array[i];
          }
          delete _array;
          _capacity /= 2;
          //_array = new Entry[_capacity];
          _array = temp;  
        }
      }
      return true;      
    }
  }
  return false;
}

EntryList::Entry& EntryList::at(int indx) const {
  if (indx > _capacity){
    throw range_error("Not a valid index!");
  }
  return _array[indx];
}

// dump data structure - DO NOT MODIFY
void EntryList::dump() {
  for (int i = 0; i < _size; i++) {
    cout << "  " << _array[i] << endl;
  }
}

EntryList::Iterator::Iterator(EntryList *EList, int indx) {
  _ELptr = EList;
  _indx = indx;
}
//removed const in parameter
bool EntryList::Iterator::operator!=(const EntryList::Iterator& rhs) {
  return (_ELptr->at(_indx).getVertex() != rhs._ELptr->at(rhs._indx).getVertex());//; or
         //_ELptr->at(_indx).getWeight() != rhs._ELptr->at(_indx).getWeight());
}

bool EntryList::Iterator::operator==(const EntryList::Iterator& rhs) {
  return (_ELptr->at(_indx).getVertex() == rhs._ELptr->at(_indx).getVertex());// and
        // _ELptr->at(_indx).getWeight() == rhs._ELptr->at(_indx).getWeight());
}

void EntryList::Iterator::operator++(int dummy) {
  _indx++;
}

EntryList::Entry EntryList::Iterator::operator*(){
  EntryList::Entry e;
  e = _ELptr->at(_indx);;
  return e;
}

EntryList::Iterator EntryList::begin() {
  EntryList::Iterator it(this, 0);
  return it;
}
EntryList::Iterator EntryList::end() { 
  EntryList::Iterator it(this, _size);
  return it;
}

// Insertion operator for Entry objects - DO NOT MODIFY
ostream& operator<<(ostream& sout, const EntryList::Entry& e) {
  sout << e._vertex << ": " << e._weight;
  return sout;
}

// A convenient way to write test code for a single class is to write
// a main() function at the bottom of the .cpp file.  Just be sure to
// comment-out main() once you are done testing!

// Following is example test code.  There is no guarantee that it is
// complete -- you are responsbile for thoroughly testing your code.
// In particular, passing these tests does not mean your
// implementation will pass all grading tests.
/*
 int main() {
   EntryList el;
   EntryList::Entry e;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
   
   cout << "before insert" << endl;
   for (int i = 1; i < 13; i++) {
     el.insert( EntryList::Entry((i*5)%13, i) );
   }
   cout << "After insert" << endl;
   
   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
   
   cout << "before remove" << endl;
   for (int i = 1; i < 13; i+=2) {
     el.remove(i, e);
   }
   cout << "after remove" << endl;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

   cout << "Before update" << endl;
   for (int i = 2; i < 13; i+=2) {
     el.update( EntryList::Entry(i, 2*i) );
   }
   cout << "after update" << endl;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;
  
   cout << "Before remove #2" << endl;
   for (int i = 3; i < 13; i*=2) {
     el.remove(i, e);
   }
   cout << "Affter remove #2" << endl;

   cout << "size: " << el.size() << ", capacity: " << el.capacity() << endl;
   el.dump();
   cout << endl;

 cout << "\nPrint using iterator:\n";
 for (auto itr = el.begin(); itr != el.end(); itr++) {
   cout << *itr << endl;
 }

   return 0;
 }
*/