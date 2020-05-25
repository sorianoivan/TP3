#ifndef _THREAD_H
#define _THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    /* Constructor */
    Thread();

    /* Ejecuta el thread con el metodo abstracto run, que sera
     * implementado por las clases hijas */
    void start();
    /* Bloquea el thread hasta que los otros completen su trabajo */
    void join();

    virtual void run() = 0;
    virtual bool isDone() = 0;

    /* Destructor */
    virtual ~Thread();
};



#endif //_THREAD_H
