//
//  main.cpp
//  Ice Cream
//
//  Created by Oroz, Justin M. on 9/11/14.
//  Copyright (c) 2014 Oroz, Justin M. All rights reserved.
//

#include <iostream>
using namespace std;

/* Top-Down
 
 Print Menu
 Get number of cones
    Error check number of cones
 For number of cones (create cone)
    Get number of scoops for that cone
        Error check number of scoops
    Print instructions for flavor entry (first loop only)
    for number of scoops get flavors
    Print Cone
 Calculate Total
 
*/

const int MAX_CONES = 10;
const int MAX_SCOOPS = 30;

void printMenu();
// Prints store name and menu

void cancelPurchase();
// Cancel Purchase?

bool valid(int input, int min, int max);
// Returns TRUE if valid
// check if input lies between min & max inclusively

float createCone(int, int&);
// Puts together and ultimately prints the current cone
// Input is the current cone number, and it returns price of the cone
// second input returns number of scoops (for receipt purposes)

char flavorInput(int);
// gets flavor form the user and returns it. input is the flavor number

float costCalc(int);
// calculates cost of a cone given number of scoops

void printCone(char[], int);
// Gives the customer theyre cone (Suckers)
// Inputs: array of flavors, total number of scoops

void printReceipt(int[], int, float);
// asks if they want receipt, prints it if so
// inputs: receipt array, number of cones bought, total cost


int main(int argc, const char * argv[])
{

    int cones, currentCone;
    float total = 0.0;
    int receipt[MAX_CONES];
    
    // Menu & Prices
    printMenu();
    
    // Get numer of cones
    cout << "How many cones would you like to purchase (0-" << MAX_CONES << "):  ";
    cin >> cones;       // # of cones to purchase
    
    
    // Cancel Purchase?
    if (valid(cones, 0, 0)) { //If 0 scoops
        cancelPurchase();
    }
    

    // Error Checking: Number of Cones
    while (!valid(cones, 1, MAX_CONES)) {
        cout << "Please enter a valid number (1-" << MAX_CONES << "): ";
        cin >> cones;
    }

    
    // For each cone
    for (currentCone = 1; currentCone <= cones; currentCone++) {
        
       total += createCone(currentCone, receipt[currentCone-1]);
    }
    
    // "Magic Formula"
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    
    // Prints total
    cout << "Your total is $" << total << endl;
    
    // Receipt?
    cout << "\nPrint Receipt? (y/n)\t";
    printReceipt(receipt, cones, total);
    
    return 0;
}

void printMenu(){
    cout << "  Juice's Ice Cream Parlor" << endl;
    cout << "1 Scoop\t\t\t\t\t$2.00\n" << "2 Scoops\t\t\t\t$3.00\n" << "Add more scoops\t\t\t$ .75\n" << endl;
}

void cancelPurchase(){
    char quit;
    char yes = 'y';
    
    cout << "Cancel Purchase? (y/n)\t";
    cin >> quit;
    quit = tolower(quit);
    if (!strncmp(&quit, &yes, sizeof(yes))) {
        exit(0); //quits if answer is yes, continues with anything else
        
    }
}

bool valid(int input, int min, int max){
    
    // Checks for letter input
    if(cin.fail()) //cin.fail() checks to see if the value in the cin
        //stream is the correct type, if not it returns true,
        //false otherwise.
    {
        cin.clear(); //This corrects the stream.
        cin.ignore(); //This skips the left over stream data.
        
        return false;
    }
    
    if ((input >= min) && (input <= max))
        return true;
    else
        return false;
}

char flavorInput(int flavorNum){
    char flavor;
    
    cout << "Input Flavor " << flavorNum << ": ";
    cin >> flavor;
    
    return flavor;
}

float costCalc(int scoops){
    float total;
    
    if (scoops == 1) {
        total = 2.0;
    } else if (scoops == 2) {
        total = 3.0;
    } else {
        total = (scoops - 2)*0.75 + 3.0;
    }
    
    return total;
}

void printCone(char flavor[], int totalScoops){
    cout << "\n\nOrder Up!\n\n";
    cout << "\t\t ___ \n";
    for (int i = 0; i < totalScoops; i++) {
       // cout << "\t\t( " << flavor[i] << " )\n"; //scoops
        
        // seperates scoops if they are of different type
        cout << "\t\t(";
        if ((flavor[i] == flavor[i+1])          // if scoop if same as one after, no divider
            || ( i == (totalScoops - 1))) {     // or if scoop is the bottom one, no divider
            cout << " " << flavor[i] << " )\n";
        } else {
            cout << "_" << flavor[i] << "_)\n"; // rest have dividers
        }
    }
   // cout << "\t\t\\```/\n" << "\t\t \\ / \n" << "\t\t  V  \n\n"; //base of cone
    cout << "\t\t\\```/\n" << "\t\t \\ / \n" << "\t\t  V  \n\n"; //base of cone

    
    
}

void printReceipt(int receipt[], int cones, float total){
    char answer;
    char yes = 'y';
    
    cin >> answer;
    answer = tolower(answer);
    if (!strncmp(&answer, &yes, sizeof(yes))) {
        cout << "\n\n" << "   Juice's Ice Cream Parlor\n\n";
        for (int i = 0; i < cones; i++) {
            cout << "Cone " << (i+1) << "\n\t" << receipt[i] << " Scoops\t\t\t$" << costCalc(receipt[i]) << endl;
        }
        cout << endl;
        cout << "Total\t\t\t\t\t$" << total << endl;
    } else {
        cout << "Please come again!\n";
    }

}

float createCone(int cone, int& scoops){
    int currentScoop;
    char flavors[MAX_SCOOPS];
    float price;
    
    // Get number of scoops for current cone
    cout << "How many Scoops for Cone " << cone << " (0-" << MAX_SCOOPS << ")?  ";
    cin >> scoops;
    
    // Cancel Purchase?
    if (valid(scoops, 0, 0)) {
        cancelPurchase();
    }
    
    // Error Checking: Number of Scoops
    while (!valid(scoops, 1, MAX_SCOOPS)) {
        cout << "Please enter a valid number (1-" << MAX_SCOOPS << "): ";
        cin >> scoops;
    }
    
    // Print instructions for flavor entry (first loop only)
    if (cone == 1)
        cout << "Enter one character for each flavor.\n";
    
    // input flavor loop
    for (currentScoop = 1; currentScoop <= scoops; currentScoop++)
        flavors[currentScoop-1] = flavorInput(currentScoop);
    
    // print cone
    printCone(flavors, scoops);
    
    
    // Calculate Cost
    price = costCalc(scoops);
    
    return price;
}