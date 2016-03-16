template <typename T>
struct Container
{};


struct Kernel {
typedef int Nested;
};


template <class K,
          class C = Container<typename K::Nested*> >
struct Poly
{};


// if f() gets commented it compiles
template<class T>
Poly<T>* 
f()
{ 
    return 0;
}


//template<class T2, class T1> // this compiles
template<class T1, class T2>
void
fails(T1, 
      Poly<T2> *)
{}


// if f() is moved here it also compiles

int main()
{  
    Poly<Kernel> * poly = 0;

    fails(0, poly);

    return 0;
}
