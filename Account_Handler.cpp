#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>

std::fstream myFile;

class EncrptionAbstract{
    public:
        virtual void encryptPass() = 0;
};

class Password:EncrptionAbstract{
    private:
        std::string user_Num;
        char pass[50];
        char acc[50];
        char email[50];

    
    public:
        void MainMenu();
        void createUser();
        void showInfo();
        void updateInfo();
        void deleteInfo();
        
        /// @brief 
        void encryptPass(){
            
            myFile.open("user.txt",std::ios::in);
            if(myFile.is_open()){
                 std::fstream  inFile;
                 inFile.open("password.txt",std::ios::out | std::ios::app);
                 if(inFile.fail()){
                    std::cout << "\t\tNo File Existed:";
                 }else{
                    for(int i = 0; i <strlen(pass); i++){
                        inFile << (int)pass[i] << " ";
                        
                    }
                    std::cout << std::endl;
                }
                
            }
            
            myFile.close();
        }

    Password(){
        user_Num[2] = ' ';
        pass[50] = ' ';
        acc[50] = ' ';
        email[50] = ' ';
    }


 };


void Password::MainMenu(){
    int userChoice;
    std::cout << "\t\t*******************************************************************\n";
    std::cout << "\t\t1.Create a User: \n";
    std::cout << "\t\t2.Show the User's Info: \n";
    std::cout << "\t\t3.Update a User's Info: \n";
    std::cout << "\t\t4.Delete an Info: \n";
    std::cout << "\t\t5.Exit: \n";
    std::cout << "\t\t*******************************************************************\n";
    std::cout << "\t\tEnter your Option: ";
    std::cin >> userChoice;

    switch(userChoice){
        case 1:
            createUser();MainMenu();
            break;
        case 2:
            showInfo();MainMenu();
            break;
        case 3:
            updateInfo();MainMenu();
            break;
        case 4:
            deleteInfo();MainMenu();
            break;
        default:
            return;

    }

}

void Password::createUser(){
    myFile.open("user.txt",std::ios::out | std::ios::app);
        if(myFile.is_open()){
            std::cout << "\t\tEnter User Number: ";
            std::cin.ignore();
            std::getline(std::cin,user_Num);
            
            std::cout << "\t\tAccount from: ";
            std::cin.getline(acc,50);
            

            std::cout << "\t\tEmail Account: ";
            std::cin.getline(email, 50);

            myFile << user_Num << "\n";
            myFile << acc << "\n"; 
            myFile << email << "\n";
            myFile << std::endl;
           

            std::cout << "\t\tEnter your Password: ";
            std::cin.getline(pass, 50);
            encryptPass();
            
            
            
            
            
            
        }
        myFile.close(); 
    
}

void Password::showInfo(){
    
    myFile.open("user.txt", std::ios::in);
    if(myFile.is_open()){
        std::string info;
        std::cout << "\t\tINFORMATION\n";
        while(std::getline(myFile,info)){
            std::cout <<"\t\t"<< info << std::endl;
        }
        myFile.close();
    }
    
}
//Done:The solution I found on the internet is by line number
//reading the lines inside the file into the vector that I created
//and writing it back to the file except the one who will get updated
//then change the text inside the vector and write it back to the file
void Password::updateInfo(){
   
   std::ifstream readfile;
   std::string filename;
   std::string text;
   int line_number;
    //asking the user to enter the name of the file, text that will replace the original text
    //ask the specific line of the text that will get updated
   std::cout << "\t\tEnter the text File: ";
   std::cin.ignore();
   std::getline(std::cin,filename);

   std::cout << "\t\tEdit Info: ";
   std::getline(std::cin,text);

   std::cout << "\t\tFind Line: ";
   std::cin >> line_number;

    //Open the file 
   readfile.open(filename);
   //error handling
   if(readfile.fail()){
    std::cout << "\t\tNo file Exist";
   }
   //creating vector and the variable for reading through text file
    std::vector<std::string> lines;
    std::string line;
    //loop through line byline then copy it inside the vector
    while(std::getline(readfile,line)){
        lines.push_back(line);
        
    }
   readfile.close();
    //error handling - if the given size of the line number is greater than the size of the vector
    //prompt the line number that the user input and indicate that the text file only have nth numbeer
    //of lines
   if(line_number > lines.size()){
        std::cout << "Line "  << line_number << " not in file" <<std::endl;
        std::cout << "File has " << line << " lines" << std::endl;
   }
    //calling ofstream to make the file into write mode
   std::ofstream writefile;

   writefile.open(filename);
    //error handling
   if(writefile.fail()){
        
        std::cout << "Writing File does not exist!";
   }

    //vector index starts at zero while the user assumed that the counting
    //or finding the specific line starts at 1 so 
    //we have to decrement the line number that the user input by 1. 
   line_number--;
    //used for loop to loop through the whole vector
   for(int i = 0; i < lines.size(); i++){
        //checks if the position is equal to the line that will be edited
        //if not equal keep looping and if the for loop finds the line write
        //the newly created/updated line inside the text file
        if(i != line_number){
            writefile << lines[i] << std::endl;
        }else{
            writefile << text << std::endl;
        }
   }
   writefile.close();

}
//same as the update function but it will ask the user to
//enter none to delete the line they want to delete.
void Password::deleteInfo(){
    std::ifstream readfile;
    std::ofstream writefile;
    std::string filename;
    std::string text;
    int line_num;

    std::cout << "\t\t Enter File Name: ";
    std::cin.ignore();
    std::getline(std::cin,filename);

    std::cout << "\t\tEnter None to Delete Line: ";
    std::getline(std::cin,text);

    std::cout << "\t\tEnter the line that will be deleted: ";
    std::cin >> line_num;

    readfile.open(filename);
    if(readfile.fail()){
        std::cout << "\t\tNo file existed!";

    }
    std::vector<std::string> lines;
    std::string line;
    while(std::getline(readfile,line)){
        lines.push_back(line);
    }
    readfile.close();

   if(line_num > lines.size()){
        std::cout << "Line " << line_num;
        std::cout << " not in file" << std::endl;

        std::cout << lines.size()  << " lines";
        std::cout << " only existed";
   } 

   writefile.open(filename);
   if(writefile.fail()){
        std::cout << "Write file Error: ";
   }   

   line_num--;

   for(int i = 0; i < lines.size(); i++){
     
     if(i != line_num){
        writefile << lines[i] <<std::endl;
     }else{
        writefile << text << std::endl;
     }
   }
    writefile.close();


}



int main(){
    Password user;
    Password* ptr = &user;

    ptr->MainMenu();
    

    return 0;
}