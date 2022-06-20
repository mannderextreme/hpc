#ifndef MINI_JIT_GENERATORS_MYEXAMPLE_H
#define MINI_JIT_GENERATORS_MYEXAMPLE_H

#include "../backend/Kernel.h"
#include "../instructions/Base.h"

namespace mini_jit {
  namespace generators {
    class MyExample;
  }
}

class mini_jit::generators::MyExample {
  private:
    //! kernel backend
    backend::Kernel m_kernel;
    
  public:
    /**
     * Generates a MyExample kernel which does bitwise AND with w0 and 0.
     *
     * @return function pointer to kernel.
     **/
    uint32_t ( *generate() )();
};

#endif