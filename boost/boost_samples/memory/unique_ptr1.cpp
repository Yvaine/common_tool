// c++ --std=c++11 unique_ptr1.cpp -o unique_ptr1

#include <memory>
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
    std::unique_ptr<Detail> detail;
};

int main()
{
    std::cout << "Startup" << std::endl;

    std::unique_ptr<Master> x(new Master);

    std::cout << "Shutdown" << std::endl;

    return 0;
}
