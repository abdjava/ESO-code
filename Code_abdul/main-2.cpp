#include "mbed.h"
#include "QEI.h"



class Potentiometer{
private:
    AnalogIn inputSignal;
    float VDD;
public:
    Potentiometer(PinName pin, float v) : inputSignal(pin), VDD(v) {}
 
    float amplitudeVolts(void) { return (inputSignal.read()*VDD); }
    float amplitudePC(void) { return inputSignal.read(); }; 
};
    
class encoder {
    private:
    Ticker timer ;
    int pluses[];//  number of tciks in the past
    int num;    // number of samples saved done so far
    QEI en;
    float r,speed_1;
    float p_max; // maxium plues for 1 rev
    
    void sample(){
        i=i%2;
        pluses[i] = en.getPulses();
        i++;
        }
    
    
    public:
    encoder (PinName A,PinName B,PinName index,int pluses_per_rev , float radius):en(A,B,index,pluses_per_rev){
        
        r =radius;
        p_max = 256*2;
        speed_1=0;
        num=0;
        }
        
    void change_r(float radius){ r =radius;}
    void change_p_max(float max){p_max = max;}
    float get_speed(){
        int num1 = i, int num2 = i-1;
        if (num1 =0){num1 =sizeof(pluses)/sizeof(int);}
        else {num1--;}
         if (num2 =0){num2 =sizeof(pluses)/sizeof(int);}
        else {num2--;}
        
        
        return ((pluses[num1]-pluses[num2])/p_max);// this needs work change formula
        
        }
    
    
    
    
    }





// we need to testing switching fequency  for various motor drive bord ferquencyies
class motor {
    private:    
 float speed,frequency ;      // spped of the motor                   
 bool direction ;    // direction of the motor  ture(1) is forwards flase(0) is backwards
 
  PwmOut output;// output object
 DigitalOut dir_output;     // output direction.

    
   public: 
    
    motor (PinName pin_pwm,PinName pin_dir):output(pin_pwm),dir_output(pin_dir){
        speed = 0;                  // speed zero
        direction =true;            // constructor 1
        frequency =1000; // start off with 1 killohz
        output = 0;
        output.period(1/frequency);     
        dir_output = direction;         // outputing the direction
        }
        
        
    void change_f(float f ){
        
        frequency=f;
         output.period(1/frequency);
        
        }
    float change_speed( float speed ){  // speed is number bewteen 1 and 0 1 is max speed 0 is low speed.
        if (speed >1 ||speed<0){ return NULL; }     // check if your value is in the right range
        
        output = speed;
        return speed;
        
        }
        
    bool change_dir (bool dir){         // returns the direction
        
        direction = dir;
        dir_output = direction;
        return direction;    
        } 
        
        
        
    // getters
    float check_f(){return frequency; }     
    bool check_dir(){return direction;}
    float check_speed(){ return speed;}
    //
    void breaks(){        // this funcation makes the motor break
    change_dir(0);
    change_speed(1);
        
        
        }
    void max(){     // forward at max speed
    change_dir(1);
    change_speed(1);
        
        
        }
    void stop (){   // truns it off.
        
    change_speed(0);
        
        }
    
    
    };



int main() {
    Serial pc(USBTX, USBRX);
    Potentiometer p1(A0,5);
    Potentiometer p2(A1,2);
    
    DigitalOut redled(D5);
    redled =1;
    motor m (D9,D8);    // blue is driection green pwm
    
    m.change_f(1000);    //
   
    
    m.change_dir(1);        // dir 
     
    while(1){   
       m.change_speed(p1.amplitudePC()); // 0  1 max
        m.change_dir((int)p2.amplitudeVolts());
        }
    
    
    

}
 