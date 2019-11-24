#include <iostream>
#include <thread>  // compile with -std=c++11

void func(int threadID, int start, int stop)
{
  for(int i=start; i < stop; i++)
    {
      std::cout<<"thread id: " << threadID <<", Iteration: "<<i<<"\n";
    }
}
int main(int argc, const char * argv[])
{
  std::thread* t1 = new std::thread(func, 0, 0, 10);
  std::thread* t2 = new std::thread(func, 1, 10, 20);
  
  t1->join();
  t2->join();
  std::cout<<"Done!"<<"\n";

  return 0;
}
