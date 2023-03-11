#include <iostream>
#include <stdexcept>
#include <stdlib.h>

using namespace std;

// numbers < with infinite precision
// input numberstings have to be of the format x.xxxxxxx or x,xxxxxxxx with x being numbers 0-9
class sp{
    bool negative = false;
    int len;
    int lvalue;
    short* svalue;

    public: 
    sp(string v, int digits){
        size_t a = digits * sizeof(short);
        svalue = (short*) malloc(a);
        len = digits;

        if(  v[0] == '-' ){
            negative = true;
        }

        if( not( v[negative + 1] != 54 and v[negative + 1] != 56) ){ throw std::invalid_argument( "not the correct format" ); }
       
        if( v[ negative ] < 48 or v[ negative ] > 57 ){ throw std::invalid_argument( "not the correct format" ); } else{ lvalue = v[ negative ] - 48; } 
       
        for( int i = negative+2; i < digits+2+negative; i++ ){
            if( v[i] == '\0' ){
                return;
            }
            if( v[i] < 48 or v[i] > 57 ){ throw std::invalid_argument( "not the correct format" ); } else{ svalue[i-2-negative] = v[ i ] - 48; } 

        } 
    }

    inline sp operator + ( sp o ){
        short tmp;
        short thisneg = 1;
        short oneg = 1;
        short uebertrag = 0;

        if( negative ){ thisneg = -1; }
        if( o.negative ){ oneg = -1; }

        for( int i = len; i >= 0; i--){
            tmp = svalue[i]*thisneg + o.svalue[i]*oneg + uebertrag;
            if( tmp % 10 < 0 ){ 
                svalue[i] = 10 - abs(tmp % 10); 
                uebertrag = -1 + tmp/10;
            } 
            else{ 
                svalue[i] = abs(tmp % 10); 
                uebertrag = tmp / 10;
            };
        }

        lvalue = lvalue*thisneg + o.lvalue*oneg + uebertrag;
        return *this;
    }
    
    inline sp operator - ( sp o ){
        if( o.negative ){ o.negative = false; } else{ o.negative = true; };
        return *this + o;
    }

    void tostring(){
        if( negative ){
            cout << lvalue*-1 << ".";
        }
        else{
            cout << " " << lvalue << ".";
        }

        for( int i = 0; i < len; i++ ){
                cout << svalue[i];
        }

        cout << "\n";
    }
    
};

int main(){
    string a = "3.1499";
    string b = "-2.";
    sp aa = sp(a,5);
    sp bb = sp(b,5);

    aa.tostring();
    bb.tostring();

    for( int x = 0; x < 1; x++ ){
        (aa - bb).tostring();
    }
}
