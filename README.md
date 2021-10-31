# timer  Sample Implementation
Implement timer class with given 2 inputs CPU FREQ 2.3GHz and 24Bit Counter

Question:
Given  2.3GZ clock and 24-bit counter, Implement timer API.


Answer:

Get Tick Period from Given (System) Clock: 


        2.3GHZ is 2.3GHZ cycles per sec which is 2.3 *  1o pow (9)  tics per sec

        Each tick period is 0.4nanosec.


Get overflow time of counter.  What time does it take to overflow the 24bit counter 

        We are given a 24bit counter, so it will take 

        2 pow (24) * .4 nanosec = 6.7milliSec to overflow the counter .




We should/can round off the overflow time from 6.7millisec to 7millisec or even 10millisec,


How to round off to 6millsec from 6.7millsec?

        Instead of resetting the 24 bit counter to 0 when it reaches max which is 2 pow (24) = 16,777,216
        reset the counter instead of 0 to 1,777,216 . 

        So the ticks to reach 16,777,216 is 15,000,000 from 1,777,216

                    15 * 10 pow(6) * .4 nanosec = 6 milliSec. 


For every overflow of the 24bit counter, it takes 6 milliseconds. 

Assumption:

With Prescaler and tweaking the initial load value of the counter, we can get the overflow time of 
counter to 10milliseconds

 
Trigger an ISR when the overflow of the counter happens ,which is every 10millisec. We define that count in the code as OVERFLOW_TIME

        #define  OVERFLOW_TIME 10


How to use this information?

        To create a timer of 12sec, Calculate the count value of for each timer .

        For every ISR  call, decrement the count of the timer. When the count reaches 0 , call the callback function.

        For Ex: 
            Timer1 with 12 sec 

                count  = 12 * 1000(millisec)/10 milliSec  = 1200

            Timer2 with 6 sec

                count = 6*1000/10millisec = 600
