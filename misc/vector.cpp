#include <iostream>

typedef int T;

class iterator
{
    public:
        iterator() = delete;
        iterator(T* p);
        T& operator*();
        iterator operator++(int);
        void operator--();
        bool operator==(const iterator& it);
        bool operator!=(const iterator& it);

    private:
        friend class vector;
        T* _p;
        int _occupied;
};

iterator::iterator(T* p)
    : _p(p)
{
}

T& iterator::operator*()
{
    return *_p;
}

iterator iterator::operator++(int)
{
    ++_p;
    return *this;
}

void iterator::operator--()
{
    --_p;
}

bool iterator::operator==(const iterator& it)
{
    return _p == it._p;
} 

bool iterator::operator!=(const iterator& it)
{
    return !(*this == it);
}

class vector
{
    public:
        vector();
        ~vector();
        vector(const vector& other);
        void insert(const T& element);
        void erase(int index);
        T& operator[](int index) const;
        int size() const;
        iterator begin();
        iterator end();
        void print_details();

    private:
        T* _p;
        int _count;
        int _occupied;
};

void print_vector(const vector v)
{
    for (int i = 0; i < v.size(); ++i)
    {
        std::cout << v[i] << '\n';
    }
}

vector::vector()
    : _p(nullptr),
    _count(0),
    _occupied(0)
{
}

vector::~vector()
{
    if (_p) {
        delete[] _p;
    }
}

void vector::insert(const T& element)
{
     if ((_count - _occupied) == 0) {
         std::cout << "count : " << _count << "occupied : "
             << _occupied << "new alloction : " << _count * 2
             << '\n';
         if(_count) {
             _count *= 2;
         }
         else {
             _count = 1;
         }
         
         if(_p) 
             delete[] _p;

         _p = new T[_count];
     }

     _p[_occupied++] = element;
}

void vector::erase(int index)
{
    if(index > -1 && index <= _occupied)
    {
        _p[index] = 0;

        for(; index < _occupied - 1; ++index) {
            _p[index] = _p[index + 1];
        }
        --_occupied;
    }
}

T& vector::operator[](int index) const
{
    return _p[index];
}

int vector::size() const
{
    return _occupied;
}


iterator vector::begin()
{
    iterator it(_p);
    return it;
}

iterator vector::end()
{
    return iterator(_p + _occupied);
}

void vector::print_details()
{
    std::cout << _p << '\n';
}


vector::vector(const vector& other)
{
    if(other._count > 0) {
        _p = new T[other._count];
        for (int i = 0; i < other._occupied; ++i) {
            _p[i] = other._p[i];
        }
        _count = other._count;
        _occupied = other._occupied;
    }
}

int main() 
{
    vector v;

    //print_vector(v);

    v.insert(1);
    //print_vector(v);
    v.insert(2);
    //print_vector(v);
    v.insert(3);
    //print_vector(v);
    
    v.erase(1);
    print_vector(v);

    auto it = v.begin();
    std::cout << "From iterator : " << *it << '\n';

    v.print_details();

    vector v2 = v;
    v2.print_details();

    v2[0] = 2;

    std::cout << "v vector : " << '\n';
    print_vector(v);
    std::cout << "v2 vector : " << '\n';
    print_vector(v2);

    std::cout << "Trying out new iterator : \n";
    for(auto it2 = v.begin(); it2 != v.end();
            it2++)
    {
        std::cout <<*it2 << '\n';
    }
}

