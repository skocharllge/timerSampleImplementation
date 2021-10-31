#include <iostream>
#include <vector>

using namespace std;

//*******************************************************************REFER README on HOW TO DERIVE OVERFLOW_TIME*******************************************************************

#define OVERFLOW_TIME  10 //in ms

//*******************************************************************REFER README on HOW TO DERIVE OVERFLOW_TIME*******************************************************************

//Timer type

typedef enum TIMERMODE {
    ONE_SHOT,        //stop after counter becomes 0
    PERIODIC         //reset the counter after it becomes 0
} ;


class timer
{
  public:

   timer(int time, void(*callBackPtr)(), TIMERMODE mode)
   {
        this->count = time * 1000/OVERFLOW_TIME ;
        this->time =  time;
      this->callback = callBackPtr;
        this->mode = mode;


    }

   ~timer()
    {

    }
    void timerStart()
    {
        enable = 1;
    }
    void timerStop()
    {

        enable = 0;
    }

   void timerConfig(int time)
   {
     this->count = time * 1000/OVERFLOW_TIME;
  }

    int time ; //in milliSec
    int count; //Calculate the timer ;
    void (*callback)();
    int enable ;

    TIMERMODE mode;

};




//List of timers
vector<timer*>timerList;

//ISR to be invoked after overflow of the counter reaches to the max and resets.

static void isr()
{
   for(int i = 0; i < timerList.size(); i++)
   {
     	timer* t = timerList[i];

        if (t->enable != 1)
            continue;

        if (t->count > 0)
            t->count--;

        if (t->count == 0 && t->callback) //
        {
              t->callback();
              if(t->mode == PERIODIC)
              {
                    t->timerConfig(t->time);  //reset the timer in case of periodic timer
              }
        }
  }

}

void timerCallBack()
{

}


int main()
{

 timer* t = new timer(10,timerCallBack,  ONE_SHOT);



}



