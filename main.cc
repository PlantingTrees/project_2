// A -> I = E
// E -> P O P | P
// O -> + | - | * | / | **
// P -> I | L | UI | UL | (E)
// U -> + | - | !
// I -> C | CI
// C -> a | b | ... | y | z
// L -> D | DL
// D -> 0 | 1 | ... | 8 | 9

//Todo! create a text file called input.txt and store these grammar on it.
//Do we have to be concerned about white space
//We may have to remove white spaces from buffers

#include <iostream>
#include <string>
#include <fstream>


using namespace std;

string buff;


bool A(void);
bool E(void);
bool O(void);
bool P(void);
bool U(void);
bool I(void);
bool C(void);
bool L(void);
bool D(void);

int main(int argc, char *argsv[]){
   
    //read the input file
    ifstream fin("input.txt");
    
    if(fin.is_open()){
        
        while(fin.good()){
            getline(fin, buff); //gotten one line from input file
            string t = buff;
            //perform parsing
            if(A()){
                cout << "The string "<< t << " is in the language.\n" <<endl;
            }
            else {
                
                cout << "The string "<< t << " is not the language.\n" <<endl;
                
            }
        }
        
    }
    else{
        cout << "The input file cannot be read." <<endl;
    }
}

bool A(void){
    // A -> I = E
    if(I()){
        if(buff[0] == '='){
            buff = buff.substr(1);
            if(E()){
                return true;
            }
            return false;
        }
    }
    return false;
}

bool I(){
    // I -> C | CI
    if(C()){
        if(buff[0] != '='){
            if(I()){
                return true;
            }
            return false;
        }
        return true;
    }
    return false;
       
}

bool C(){
    if('a' <= buff[0] && buff[0] <= 'z'){
        buff = buff.substr(1);
        return true;
    }
    return false;
}

bool E(){
    // E -> P O P | P
    
    if(P()){
        //buff = buff.substr(1);
        if(O()){
            //buff = buff.substr(1); //having a bug here with moving to the next item
            if(P()){
                return true;
            }
        }
        return true;
    }
    return false;
}

bool P(){
    // P -> I | L | UI | UL | (E)
    if(I()){
        return true;
    }
    else if(L()){
        return true;
    }
    else if(U()){
        if(L()){
            return true;
        }
        return false;
    }
    else if(U()){
        if(I()){
            return true;
        }
        return false;
    }
    else if(buff[0] == '('){
        buff = buff.substr(1);
        if(E()){
            if(buff[0] == ')'){
                return true;
            }
        }
    }
    return false;
}

bool O(){
    // O -> + | - | * | / | **
    if(buff[0] == '+'){
        return true;
    }
    else if(buff[0] == '-'){
        return true;
    }
    else if (buff[0] == '*'){
        return true;
    }
    else if(buff[0] == '/'){
        return true;
    }
    else if (buff.compare("**") == 0 ){ //returns 0 if the same
        return true;
    }
    return false;
}

bool L(){
    // L -> D | DL
    if(D()){
        if(buff.empty() == false){
            if(L()){
                return true;
            }
        }
        return true;
    }
    return false;
}

bool U(){
    // U -> + | - | !
    if(buff[0] == '+'){
        return true;
    }
    else if (buff[0] == '-'){
        return true;
    }
    else if (buff[0] == '!'){
        return true;
    }
    return false;
}

bool D(){
    // D -> 0 | 1 | ... | 8 | 9
    if('0' <= buff[0] && buff[0] <= '9'){
        buff = buff.substr(1);
        return true;
    }
    return false;
}
