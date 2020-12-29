
#include <list>
#include <iostream>
#include <functional>

//реализация потока, копирование запрещено по идеологическим причинам
class stoppable_thread {
    public:
    stoppable_thread(std::function<void()> fn) : fn_(fn) {
       // fn();
    }
    stoppable_thread(const stoppable_thread& other) = delete;
    stoppable_thread(const stoppable_thread&& other) {
        fn_ = std::move(other.fn_);
    }
   // stoppable_thread& operator = (const stoppable_thread &) = delete; 
/*    stoppable_thread&& operator = (const stoppable_thread &&) {
        fn_ = other.fn_;
    }*/
    void run() { fn_(); }
    private:
    std::function<void()> fn_;
        
};

//пулл потоков, реализует конструктор перемещения для 
//того чтобы можно было эффективно передать его экземпляр
//переместив экземпляры stoppable_thread
class thread_pool
{
public:
  thread_pool() {}
  thread_pool(int size, std::function<void()> fn)
  {
    for (int i = 0; i < size; ++i)
    {
        stoppable_thread tr(fn);
      //threads_.emplace_back(stoppable_thread(fn));
       // stoppable_thread tr1 = tr;
        threads_.emplace_back(std::move(tr));
    }
      

  }
      thread_pool(const thread_pool&& other) {
          
            for (auto& tr: other.threads_)
            {
                threads_.emplace_back(std::move(tr));
            }

    }
  void start() {
    for (auto& tr: threads_)
    {
      tr.run();
    }
  }

private:
  std::list<stoppable_thread> threads_;
};

void bar() {
    std::cout << "fn called\n";
}

int main()
{
    thread_pool tp(4, bar);
    tp.start();
    
    thread_pool tpcopy = std::move(tp);
    tpcopy.start();

  return 0;
}
