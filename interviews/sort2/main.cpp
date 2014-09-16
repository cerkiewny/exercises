// deifnition of sort number
#define SORT_VAL 20

#include<iostream>
#include<fstream>
#include<cctype>
#include <new>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::bad_alloc;

#ifdef TESTS
#define MS_ASSERT_EQ(x,y) if (! (x == y) ) cout << "failure: " << __LINE__ << endl;
#endif

typedef unsigned int uint;

// general usage pair storage
template <class F, class S> class pair{
    public:
        F first;
        S second;
        pair() {};
        pair(F a, S b) : first(a), second(b){};
};

//my own vector

template<class V> class msVec{
    private:

        uint howMany;
        uint capacity;
        V (*  buffer);
        bool hash_Valid;
        uint hash_;
    public:

        void print(){
            for(uint i = 0u; i < howMany; i++){
                cout << buffer[i];
            }
        }
        //rewrite on assignment
        msVec<V> & operator = (const msVec<V> & in){
            // if not the self assignment
            if (this != &in){
                if(buffer != NULL)
                    delete[] buffer;
                howMany = in.howMany;
                capacity = in.capacity;
                hash_Valid = in.hash_Valid;
                hash_ = in.hash_;
                buffer = new V[capacity];
                for(uint i = 0; i < howMany; i++){
                    buffer[i] = in.buffer[i];
                }
            }
            return * this;
        }
        
        //initialization
        msVec(const msVec<V> & in) : howMany(in.howMany), capacity(in.capacity), hash_Valid(in.hash_Valid), hash_(in.hash_), buffer(NULL){
            buffer = new V[in.capacity];
            for(uint i = 0; i < howMany; i++){
                buffer[i] = in.buffer[i];
            }
        }

        uint count(){ return howMany; }

        msVec() : howMany(0), capacity(10), hash_Valid(false), hash_(0){ buffer = new V[10]; }

        //push the end if we are out of size we increase the buffer size twice.
        void push_back(V nv) { 
                if (howMany == capacity){
                    capacity *= 2;
                    V (* temp) = new V[capacity];
                    for(uint i = 0; i < capacity / 2; i++){
                        temp[i] = buffer[i];
                    }
                    delete[] (buffer);
                    buffer = temp;
                }
                buffer[howMany] = nv;
                howMany ++;
                hash_Valid = false;
            }

        ~msVec(){ if(buffer != NULL) delete[](buffer);}

        // pop the last element and return it
        V pop_back(){ hash_Valid = false; howMany--; return buffer[howMany];}

        //calculate hashing function for map
        uint hash(){ 
            uint ret = 0u;
            for(uint i = 0u; i < howMany; i ++ ){
                    ret = ret * 547 + buffer[i];
                }
            hash_ = ret;
            return ret;
            };

     V operator [](uint i) const {return buffer[i];}

     V & operator [](uint i) { hash_Valid = false; return buffer[i];}

     void clear(){ howMany = 0; }

     bool operator== (msVec<V>& in){
         if(in.count() != howMany )
            return false;
         for(uint i = 0u; i < howMany; i++){
             if( buffer[i] != in[i] )
                 return false;
         }
         return true;

         };

     bool operator> (msVec<V> & in){
         uint cmpSize = howMany;
         if(in.howMany < howMany){
             cmpSize = howMany;
         }
         for(uint i = 0u; i < cmpSize; i++){
             if(buffer[i] > in.buffer[i]){
                 return true;
             }
             if(buffer[i] > in.buffer[i]){
                 return false;
             }
         }
         return howMany > in.howMany;
         
     }
};

//greater operation used in the heap (they are used to supress the usage of default operator> on pointers
//which is disasterous if we have the pointers to vectors

bool greater( int & in1, int& in2){
    return in1 > in2;
    }

bool greater( pair<char, unsigned int>& in1,  pair< char, unsigned int>& in2){
    if(in1.second > in2.second){
        return true;
    }
    return false;
}

bool greater( pair<msVec<char>, unsigned int>* in1,  pair<msVec<char>, unsigned int>* in2){
    if(in1->second > in2->second){
        return true;
    }
    return false;
}

// heap with constant number of entries
template <class V> class constSizeHeap{

    private:
        uint _size;
        uint howMany;
        V (* buffer);

        uint leftChild(uint i){
            return  2 * i + 1;
        }
        uint rightChild(uint i){
            return  2 * i;
        }

        uint parent(uint i){
            return i / 2;
        }

    public:
        constSizeHeap(uint size) : _size(0), howMany(0), buffer(NULL){
            _size = size;
            buffer = new V[size];
        }

        bool empty(){ return howMany == 0;}
        bool full(){ return howMany == _size;}

        void push_heap(V newVal){
            if(howMany < _size){
                buffer[howMany] = newVal;
                uint curEl = howMany;
                
                while (curEl != 0){
                    if(greater(buffer[parent(curEl)], buffer[curEl])){
                        V tmp = buffer[parent(curEl)];
                        buffer[parent(curEl)] = buffer[curEl];
                        buffer[curEl] = tmp;
                        curEl = parent(curEl);
                    }
                    else
                        curEl = 0;
                }
                howMany ++;
            }
            else
            {
                pop_heap();
                push_heap(newVal);
            }
        }

        //pop the heap and than return its heap property
        void pop_heap(){
           buffer[0] = buffer[howMany - 1];
           howMany--;
           uint curEl = 0;
           while(curEl < howMany){
               uint left = leftChild(curEl);
               uint right = rightChild(curEl);
               if(left >= howMany){
                   left = right;
               }
               if(right >= howMany){
                   return;
               }
               uint nextEl;
               if(greater(buffer [right], buffer[left])){
                   nextEl = left;
               }
               else
                   nextEl = right;
               if(greater(buffer[curEl], buffer[nextEl])){
                   V tmp = buffer[nextEl];
                   buffer[nextEl] = buffer[curEl];
                   buffer[curEl] = tmp;
                   curEl = nextEl;
               }
               else
                   curEl = howMany;

           }
        }
        
        V front(){
            return buffer[0];
        }

        ~constSizeHeap(){
            delete[] (buffer);
        }
};


//map of character vectors
class charVecMap{
    typedef  msVec< pair< msVec<char>, uint >* > (* Values);
    private:
        Values * buffer;
        uint howMany;
        uint _capacity;
    public:
        charVecMap() : howMany(0), _capacity(10){
            buffer = new Values[_capacity];
            for(uint i = 0u; i < _capacity; i++){
                buffer[i] = NULL;
            }
        }
        ~charVecMap(){
            for( uint j = 0u; j < _capacity; j++){
                if(buffer[j] != NULL){
                    delete  buffer[j];
                }
            }
            delete[](buffer);
        }

#ifdef TESTS
        void print_all(){
            for( uint j = 0u; j < _capacity; j++){
                if(buffer[j] != NULL){
                    for(uint k = 0u; k < buffer[j]->count(); k++){
                        cout << buffer[j]->operator[](k)->second;
                        cout << " ";
                        buffer[j]->operator[](k)->first.print();
                        cout << endl;
                    }
                }
            }
        }
#endif

        void print_top(int n){
            constSizeHeap<pair<msVec<char> , uint> * > csh = constSizeHeap<pair<msVec<char> , uint> * >(n);
            bool first = true;
            for( uint j = 0u; j < _capacity; j++){
                if(buffer[j] != NULL){
                    for(uint k = 0u; k < buffer[j]->count(); k++){
                        if(first){
                            first = false;
                            csh.push_heap(buffer[j]->operator[](k));
                        }
                        else if( !csh.full()){
                            csh.push_heap(buffer[j]->operator[](k));
                        }
                        else{
                            if(greater(buffer[j]->operator[](k), csh.front())){
                                csh.pop_heap();
                                csh.push_heap(buffer[j]->operator[](k));
                            }
                        }
                    }
                }
            }
            pair<msVec<char> , uint> * res[n];
            int count = 0;
            while(!csh.empty()){
                res[count] = csh.front();
                csh.pop_heap();
                count++;
                
            }
            while(count > 0){
                cout << "      " <<  res[count - 1]->second << " ";
                res[count-1]->first.print();
                cout << endl;
                count --;
            }

        }

        //apppend a new value to the map
        void append(msVec<char> newVal){
            if(howMany > _capacity * _capacity){
                _capacity = _capacity * 2;
                Values * temp = NULL;
                try{
                    temp = new Values [_capacity]; 
                }
                catch(bad_alloc & e){
                    cout << "too big alloc";
                }
                for( uint j = 0u; j < _capacity ; j++){
                    temp[j] = NULL;
                }
                for( uint j = 0u; j < _capacity / 2; j++){
                    if(buffer[j] != NULL){
                        for(uint k = 0u; k < buffer[j]->count(); k++){
                            uint hash = buffer[j]->operator[](k)->first.hash();
                            if (temp[hash % _capacity] == NULL){
                                temp[hash % _capacity] =  new  msVec< pair< msVec<char> , uint >* >();
                            }
                            temp[hash % _capacity]->push_back(buffer[j]->operator[](k));
                        }
                        delete  buffer[j];
                    }

                }
                delete[](buffer);
                buffer = temp;
            }
            howMany ++;
            pair< msVec< char >, uint > * newValP =  new pair< msVec< char >, uint >(newVal, 1);
            if(buffer[newVal.hash() % _capacity] == NULL){
                buffer[newVal.hash() % _capacity] = new  msVec< pair< msVec<char> , uint >* >();
            }
            buffer[newVal.hash() % _capacity]->push_back( newValP );

        };

        //check whether the map contains a key
        bool contains(msVec<char>& key) {
            if(  buffer[key.hash() % _capacity] == NULL || buffer[key.hash() % _capacity]->count() == 0){
                return false;
            }
            else{
                for (uint i = 0u; i < buffer[key.hash() % _capacity]->count(); i++){
                    if (key == buffer[key.hash() % _capacity]->operator[](i)->first){
                        return true;
                    }
                }
            }
            return false;
        }

        //increase number of occurances of value
        void increase(msVec<char>& key) {
            for (uint i = 0; i < buffer[key.hash() % _capacity]->count(); i++){
                if (key == buffer[key.hash() % _capacity]->operator[](i)->first){
                     buffer[key.hash() % _capacity]->operator[](i)->second++;
                }
            }
        };

        pair< msVec<char > , uint > * operator [] (msVec<char> key){
            for (uint i = 0; i < buffer[key.hash() % _capacity]->count(); i++){
                if (key == buffer[key.hash() % _capacity]->operator[](i)->first){
                    return  buffer[key.hash() % _capacity]->operator[](i);
                }
            }
        };

};

int main(int argc, char * argv[]){

#ifdef TESTS
    msVec<int> testV;
    MS_ASSERT_EQ(testV.count(), 0);
    testV.push_back(1);
    MS_ASSERT_EQ(testV.count(), 1);
    for(int i = 0; i < 100; i++){
        testV.push_back(1);
    }
    MS_ASSERT_EQ(testV, testV);
    for(int i = 0; i < 101; i++){
        MS_ASSERT_EQ(testV.pop_back(), 1);
    }
    MS_ASSERT_EQ(testV.count(), 0);
    charVecMap a;
    msVec<char> testC;
    testC.push_back('a');
    testC.push_back('b');
    testC.push_back('b');
    testC.push_back('a');
    msVec<char> testZ;
    testZ.push_back('a');
    testZ.push_back('b');
    testZ.push_back('b');
    testZ.push_back('a');
    msVec<char> cpTest = testC;
    MS_ASSERT_EQ(testC, cpTest);


    msVec<char> testD;
    testD.push_back('a');
    testD.push_back('b');
    a.append(testC);
    MS_ASSERT_EQ(a.contains(testC), true);
    MS_ASSERT_EQ(a.contains(testD), false);
    constSizeHeap<int> csh = constSizeHeap<int>(3);
    csh.push_heap(3);
    MS_ASSERT_EQ(csh.front(), 3);
    csh.push_heap(2);
    MS_ASSERT_EQ(csh.front(), 2);
    csh.push_heap(1);
    MS_ASSERT_EQ(csh.front(), 1);
    csh.push_heap(10);
    MS_ASSERT_EQ(csh.front(), 2);

    constSizeHeap< pair< char, uint > > csh2 = constSizeHeap< pair< char, uint> >(5);

    pair < char, uint > t1 = pair< char, uint > ('a', 2);
    pair < char, uint > t2 = pair< char, uint > ('b', 3);
    pair < char, uint > t3 = pair< char, uint > ('x', 1);

    csh2.push_heap(t1);
    csh2.push_heap(t2);

    MS_ASSERT_EQ(csh2.front().first, 'a');

    csh2.push_heap(t3);

    MS_ASSERT_EQ(csh2.front().first, 'x');

    a.increase(testC);



#endif

    if(argc <= 1){
        cout << "please provide input file argument" << endl;
    }

    else{

        ifstream in(argv[1], ifstream::in);
        in >> std::noskipws;
        msVec<char> inp;
        charVecMap * counts = new charVecMap();
        while(in.good()){
            char tmp;
            in >> tmp;
            if(isalnum(tmp)){
                inp.push_back(tmp);
            }
            else if(inp.count() != 0 ){
                if(counts->contains(inp)){
                    counts->increase(inp);
                }
                else{
                    counts->append(inp);
                }
                inp.clear();
            }
        }
#ifdef TESTS
        counts->print_all();
#endif
        counts->print_top(20);
        delete(counts);
    }
}
