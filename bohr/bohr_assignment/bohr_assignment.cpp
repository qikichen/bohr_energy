#include<iostream>
#include<iomanip>
#include<math.h>
#include<cctype>

const double electron_volts{1.6*pow(10,-19)};

void welcome()
{
    //Simple welcome message for the person using the program
    std::cout << "Welcome to the Energy Calculator" << std::endl;
    std::cout << "Please input an atomic number, an n_i and an n_j in the next line." << std::endl;
}

bool choose_eV()
{
    //returns a boolean to indicate whether the user wants to print the energy i eV or J
    std::string input_string{};
    std::cout << "Type E if you want to return the energy in eV and J if you want joules:" << std::endl;
    std::cin >> input_string;
    if(input_string == "E"){
        return true;
    }
    else if(input_string == "J"){
        return false;
    }
    //Simple validation of input if it isn't E or J
    else{
        std::cout << "This is invalid, please try again." << std::endl;
        choose_eV();
    }
}

double bohr_energy_ev(int Z, int n_i, int n_j, bool ev)
{
    //Formula coded in C++ of the bohr energy split into smaller parts to avoid algebraic errors
    double ratio_n_i{1/pow(n_i,2)};
    double ratio_n_j{1/pow(n_j,2)};
    double Z_2 = Z*Z;
    double bohr_energy {13.6*Z_2*(ratio_n_i-ratio_n_j)};
    if(ev == true)
    {
        return bohr_energy;
    }
    else if(ev == false)
    {
        double bohr_energy_joules = bohr_energy*electron_volts;
        return bohr_energy_joules;
    }
}

int integer_validation()
{
    //validates integer values
    int unvalidated{};
    bool failure{true};
    while(failure == true ){
        std::cout << "That was invalid, please try again" << std::endl;;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> unvalidated;
        //Conditions required to pass the validation
        if (std::cin.fail()==false && std::cin.peek() != '.' && unvalidated > 0 && std::cin.peek() == '\n'){
            failure = false;   
        }
        
    }
    return unvalidated;
}


int input_atomic_number()
{
    //input function for atomic number, uses the validation function as well to validate input
    int atomic_number;
    std::cout << "Atomic Number:"  << std::endl;
    std::cin >> atomic_number;
    if (std::cin.fail()==true || std::cin.peek() == '.' || atomic_number <= 0 || std::cin.peek() != '\n'){
        atomic_number = integer_validation();
    }
    return atomic_number;
}

int input_number_i()
{
    //input function for energy level i, uses the validation function as well to validate input
    int number_i;
    std::cout << "N_i:"  << std::endl;
    std::cin >> number_i;
    if (std::cin.fail()==true || std::cin.peek() == '.' || number_i <= 0 || std::cin.peek() != '\n'){
        number_i = integer_validation();
    }
    return number_i;
}

int input_number_j()
{
    //input function for energy level j, uses the validation function as well to validate input
    int number_j;
    std::cout << "N_j:"  << std::endl;
    std::cin >> number_j;
    if (std::cin.fail()==true || std::cin.peek() == '.' || number_j <= 0 || std::cin.peek() != '\n'){
        number_j = integer_validation();
    }
    return number_j;
}

int main()
//Main function used to do all calculations and user friendly input
{
    welcome();
    int atomic_number;
    int num_i;
    int num_j;
    atomic_number = input_atomic_number();
    num_i = input_number_i();
    num_j = input_number_j();
    //Validation for invalid combinations of the energy levels
    if(num_j > num_i){
        bool bigger{true};
        std::cout << "Unfortunately your N_i and N_j combination is invalid. N_i can't be smaller than N_j. Please try again" << std::endl;
        while(bigger){
            std::cout << "Please type in a new N_i" << std::endl;
            num_i = input_number_i();
            std::cout << "Please type in a new N_j" << std::endl;
            num_j = input_number_j();
            if(num_j > num_i){
                std::cout << "That input is still invalid, please try again!" << std::endl;
            }
            else{
                bigger = false;
            }
        }
    }
    bool units{choose_eV()};
    std::cout << std::endl;
    //Print out the energy with correct units
    double energy{bohr_energy_ev(atomic_number,  num_i,  num_j,  units)};
    if (units){
        std::cout << "Your Energy is " << energy << "eV" << std::endl;
    }
    else if (units == false){
        std::cout << "Your Energy is " << energy << "J" << std::endl;
    }
    //Ending notes and asking the user if they want to rerun the calculator
    std::cout << "Thank you for using the Calculator, would you like to reuse the calculator?(Please type y/n)" << std::endl;
    std::string rerun;
    std::cin >> rerun;
    bool run_again{true};
    while(run_again){
        
        if(rerun == "y"){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            main();
        }
        else if(rerun == "n"){
            std::cout << "Thank you for using the calculator!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            run_again=false;
        }
        else{
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please type in a valid character such as y/n.";
            std::cin >> rerun;
        }
    }
    return 0;
}
