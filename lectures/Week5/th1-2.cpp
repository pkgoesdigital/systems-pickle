#include <iostream>
#include <thread>  // compile with -std=c++11 -pthread options
                   // g++ -std=c++11 -pthread th1.cpp -o th1

void func(int threadID, int start, int stop, int* results)
{
  for(int i=start; i < stop; i++)
    {
      std::cout<<"thread id: " << threadID <<", Iteration: "<<i<<"\n";
    }
  results[threadID] = threadID+3;
  *myInt = 10;
}
int main(int argc, const char * argv[])
{
    int* results = (int*)malloc(2 * sizeof(int));

  std::thread* t1 = new std::thread(func, 0, 0, 10, results);
  std::thread* t2 = new std::thread(func, 1, 10, 20, results);

  t1->join();
  t2->join();
  std::cout<<"Done!"<<"\n";


  std::cout << (results[0] + results[1]) << "\n";
  return 0;
}
