#include<iostream>
#include<fstream>
#include<string.h>
std::fstream myFile;

int main(){
myFile.open("user.txt",std::ios::in);
if(myFile.is_open()){
//infile is a way to access the txt file
 std::ifstream infile("password.txt");
 //num var is declared to store the numeric values in it.
 int num;
//this is to iterate or loop inside the file until there's no numeric data left
 
    
while(infile >> num){
    //this is to convert int data into char ascii
     std::cout<<(char)num;
}

//this function is use as a way to close the file after the user use it
 infile.close();
}
myFile.close();
    
    
    return 0;
}