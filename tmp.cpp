#ifndef TEST_IMAGEPOOL_H
#define TEST_IMAGEPOOL_H

#include "TFC/TFC_header.h"
#include "TFC/graph/Image.h"
#include "TFC/thread/ThreadPool.h"

using TaskList = struct {
                  char *file, *name;
                 }*;

class test_ImagePool {
 using IRT = std::unordered_map<const char*, std::shared_ptr<TFC::Image*> >::iterator;

 public:
  test_ImagePool() {}
  ~test_ImagePool() {}

  void Commit(TaskList lst, uint64_t num) {
    fins.store(0);
    for (uint64_t i = 0; i < num; ++i) {
      imgPool[lst[i].name] = std::make_shared<TFC::Image*>(new TFC::Image);
      pool.Commit(
        [&](TaskList lst, uint64_t num, IRT &pos) {
          (pos->second.get())->Load(lst[num].file);
        },
        lst, i, imgPool.begin() + i
      );
    }
  }
  bool IsDone();


 private:
  std::unordered_map<const char*, std::shared_ptr<TFC::Image*> > imgPool;
  TFC::Thread::ThreadPool pool;
  int tsk = 0;
  std::atomic<uint64_t> fins;
};
