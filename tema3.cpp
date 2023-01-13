#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>



//clasa singleton pentru a genera id-uri unice pentru fiecare obiect de tip Aliment
class ID{
private:
    int nextID;
    static ID* ptr;
    ID(){};
public:
    ID(const ID& obj)=delete;
    static ID* getptr()
    {
        if(ptr==NULL){
            ptr=new ID();
            return ptr;
        }
    }
   int getnextID(){
        return nextID++;
    }
};
ID* ID::ptr=nullptr;

//clasa de baza
class Aliment{
protected:
    std::string nume;
    int pret;
    int id;
public:
    Aliment(std::string nume, int pret) : nume(nume),pret(pret)
    {
        id= ID::getptr()->getnextID();
    }
std::string getnume()
{
    return nume;
}
int getpret()
{
        return pret;
}
int getid()
{
        return id;
}
virtual void print()=0;

virtual Aliment* clone()=0;

virtual ~Aliment()=default;

friend std::ostream &operator <<(std::ostream &os, Aliment &obj)
{
obj.print();
return os;
}
};

class Legume : public Aliment
{
    std::string culoare;
    int nrproteine;
    int nrcalorii;
    friend class Legume_builder;
public:
    Legume(std::string nume, int pret, std::string culoare, int nrproteine, int nrcalorii) : Aliment(nume, pret), culoare(culoare), nrproteine(nrproteine), nrcalorii(nrcalorii)
    {
    }
    void print()
    {
        std::cout<<"Leguma "<<nume<<" are pretul "<<pret<<",  culoarea"<<culoare<<", calorii "<<nrcalorii<<", proteine"<<nrproteine<<'\n';
    }
    Legume* clone()
    {
        return new Legume(nume, pret, culoare,nrproteine, nrcalorii);
    }
    friend class Myvector;
};

//builder Legume
class Legume_builder
{
    Legume l;
public:


    Legume_builder& culoare(std::string nr)
    {
        l.culoare=nr;
        return *this;
    }

    Legume_builder& nrproteine(int nr)
    {
        l.nrproteine=nr;
        return *this;
    }
    Legume_builder& nrcalorii(int nr)
    {
        l.nrcalorii=nr;
        return *this;
    }
    Legume build()
    {
        return l;
    }
};

//factory design

class LegumeFactory
{
public:
    static Legume Morcov()
    {
        return Legume("Morcov", 15, "portocaliu", 20, 13);
    }
    static Legume Carotof()
    {
        return Legume("Cartof", 10, "galben", 10, 40);
    }
    static Legume Ceapa()
    {
        return Legume("Ceapa", 7, "rosie", 35, 18);
    }
};
//singleton
class Morcov : public Legume
{
protected:
    Morcov();
    Morcov(const Morcov&) = delete;
    Morcov& operator=(const Morcov&) = delete;
public:
    static Morcov* Getinstance();
};
Morcov::Morcov() : Legume("Morcovel", 14 , 3) {}
Morcov* Morcov::Getinstance() {
    static auto morcov = new Morcov();
    return morcov;
}

template <typename T> class ComparaID {
public:
    bool operator()(const T &ob1, const T &ob2) {
        return ob1->getid() < ob2->getid();
    }
};


template<typename T>
class MyVector {
    T* arr;
    int size;

public:
    MyVector(int size) {
        arr = new T[size];
        this->size = size;
    }

    MyVector(const MyVector<T> &rhs) {
        arr = new T[rhs.size];
        size = rhs.size;
        std::copy(rhs.arr, rhs.size, arr);
    }

    MyVector<T>& operator=(const MyVector<T> &rhs) {
        if (rhs.arr != arr) {
            delete[] arr;
            arr = new T[rhs.size];
            size = rhs.size;
            std::copy(rhs.arr, rhs.size, arr);
        }

        return *this;
    }

    T& operator[](int pos) {
        return arr[pos];
    }


    ~MyVector() {
        delete[] arr;
    }

};


int main() {

    Legume c = LegumeFactory::Morcov();
    Legume* l1= new Legume("morcovel",2,"portocaliu",15,20);
    Legume* l2= new Legume("cartofel",4,"galben",5,25);
    Legume* l3= new Legume("praz",1,"portocaliu",2,16);
    Legume* l4= new Legume("brocoli",5,"portocaliu",4,12);
    MyVector<Legume>v(4);
    v[0]=l1;
    v[1]=l2;
    v[2]=l3;
    v[3]=l4;

   std::cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3]<<'\n';

    return 0;

}