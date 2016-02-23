// c++ --std=c++11 -I /usr/local/include/boost scoped_ptr1.cpp -o scoped_ptr1

#include <boost/scoped_ptr.hpp>
#include <iostream>

class Detail
{
public:
    Detail(unsigned id) :
        m_id(id)
    {
        std::cout << "+++ Detail:" << m_id << "\n"; 
    }
    ~Detail()
    {
        std::cout << "--- Detail:" << m_id << "\n"; 
    }
private:
    unsigned    m_id;
};

class Master
{
public:
    Master() :
        detail(new Detail(42))
    {
        std::cout << "+++ Master\n"; 
    }
    ~Master()
    {
        std::cout << "--- Master\n"; 
    }

private:
    boost::scoped_ptr<Detail> detail;
};

int main()
{
    std::cout << "Startup" << std::endl;

    boost::scoped_ptr<Master> x(new Master);

    std::cout << "Shutdown" << std::endl;

    return 0;
}
