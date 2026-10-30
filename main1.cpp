#include <iostream>
#include "Fitness.h"
#include <limits>
#include <conio.h> 
#include <cstdlib> 

using namespace std;

// Function to mask password with asterisks
string inputPassword() {
    string pass = "";
    char ch;
    while(true) {
        ch = _getch();
        if(ch == 13) { cout << endl; break; } 
        else if(ch == 8) { 
            if(pass.length() > 0) { cout << "\b \b"; pass.pop_back(); }
        }
        else { pass += ch; cout << "*"; }
    }
    return pass;
}

// ==========================================
//             ADMIN PANEL
// ==========================================
void adminPanel(GymSystem& gym) {
    string u, p;
    while(true) {
        system("cls");
        cout << "\n=========================================\n";
        cout << "           ADMINISTRATOR LOGIN           \n";
        cout << "=========================================\n";
        cout << " (Type '0' in User to Go Back)\n\n";
        cout << " User: "; cin >> u; if(u=="0") return;
        cout << " Pass: "; p = inputPassword();

        if (gym.adminLogin(u, p)) break;
        cout << "\n>>> Invalid Credentials! Try again.\n"; system("pause");
    }

    int c;
    do {
        system("cls");
        cout << "\n=========================================\n";
        cout << "            ADMIN DASHBOARD              \n";
        cout << "=========================================\n";
        cout << " 1. Add Trainer       (Auto-ID)\n";
        cout << " 2. Remove Trainer    (Delete)\n";
        cout << " 3. Add Customer      (New Registration)\n";
        cout << " 4. View All Staff & Members\n";
        cout << " 5. Master Schedule   (All Bookings)\n";
        cout << " 6. View Credentials  (SECRET)\n"; 
        cout << " 7. Update User Password (NEW)\n"; 
        cout << " 8. Logout\n";
        cout << "=========================================\n";
        cout << " Select Option: ";
        
        // Input Validation Loop
        while(!(cin >> c)) { 
            cin.clear(); 
            cin.ignore(1000,'\n'); 
            cout << ">>> Invalid Input! Please enter a number (1-8): ";
        }
        
        if(c==1) { gym.addTrainer(); system("pause"); }
        else if(c==2) { gym.deleteTrainer(); system("pause"); }
        else if(c==3) { gym.addCustomer(); system("pause"); }
        else if(c==4) { 
            system("cls"); 
            gym.viewAllTrainers(); 
            gym.viewAllCustomers(); 
            system("pause");
        }
        else if(c==5) { 
            system("cls"); 
            gym.viewAllAppointments(); 
            system("pause");
        }
        else if(c==6) { 
            system("cls");
            gym.viewCredentials(); 
            system("pause");
        }
        else if(c==7) { 
            system("cls");
            gym.updateUserPassword(); 
            system("pause");
        }
    } while (c != 8);
}

// ==========================================
//            TRAINER PANEL
// ==========================================
void trainerPanel(GymSystem& gym) {
    string id, p;
    Trainer* t = nullptr;
    while(true) {
        system("cls");
        cout << "\n=========================================\n";
        cout << "             TRAINER LOGIN               \n";
        cout << "=========================================\n";
        cout << " (Type '0' in ID to Go Back)\n\n";
        cout << " ID:   "; cin >> id; if(id=="0") return;
        cout << " Pass: "; p = inputPassword();
        t = gym.trainerLogin(id, p);
        if (t) break;
        cout << "\n>>> Invalid ID or Password!\n"; system("pause");
    }

    int c;
    do {
        system("cls");
        cout << "\n=========================================\n";
        cout << "      TRAINER PANEL: " << t->getName() << "\n";
        cout << "=========================================\n";
        cout << "   [ MANAGEMENT ]\n";
        cout << " 1. My Schedule       (View Bookings)\n";
        cout << " 2. Cancel Appt       (Remove Booking)\n";
        cout << "\n   [ AUTHORITY ]\n";
        cout << " 3. Assign Workout    (Create Plan)\n";
        cout << "\n 4. Logout\n";
        cout << "=========================================\n";
        cout << " Select Option: ";
        
        // Fixed Input Validation for Trainer Panel
        while(!(cin >> c)) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << ">>> Invalid! Enter a number (1-4): ";
        }
        
        if(c==1) { system("cls"); t->viewSchedule(); cout<<"\nPress key..."; _getch(); }
        else if(c==2) { 
            string cid; cout << "\nCust ID (0 to Cancel): "; cin >> cid; 
            if(cid!="0") t->cancelAppointment(cid); 
            system("pause"); 
        }
        else if(c==3) { 
            string cid; cout << "\nEnter Cust ID (0 to Cancel): "; cin >> cid; 
            if(cid!="0") {
                Customer* cust = gym.findCustomerByID(cid);
                if(cust) { t->assignWorkout(cust); } 
                else cout << ">>> Not Found.\n";
            }
            system("pause");
        }
    } while (c != 4);
}

// ==========================================
//            CUSTOMER PANEL
// ==========================================
void customerPanel(GymSystem& gym) {
    string id, p;
    Customer* c = nullptr;
    while(true) {
        system("cls");
        cout << "\n=========================================\n";
        cout << "             CUSTOMER LOGIN              \n";
        cout << "=========================================\n";
        cout << " (Type '0' in ID to Go Back)\n\n";
        cout << " ID:   "; cin >> id; if(id=="0") return;
        cout << " Pass: "; p = inputPassword();
        c = gym.customerLogin(id, p);
        if (c) break;
        cout << "\n>>> Invalid ID or Password!\n"; system("pause");
    }

    system("cls");
    c->showProfile();
    cout << "\nPress any key to enter menu..."; _getch();

    int choice;
    do {
        system("cls");
        cout << "\n=========================================\n";
        cout << "      CUSTOMER MENU: " << c->getName() << "\n";
        cout << "=========================================\n";
        cout << " 1. Book Appointment  (With Trainer)\n";
        cout << " 2. View My History   (Assigned Plans)\n";
        cout << " 3. Logout\n";
        cout << "=========================================\n";
        cout << " Select Option: ";
        
        // Fixed Input Validation for Customer Panel
        while(!(cin >> choice)) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            cout << ">>> Invalid! Enter a number (1-3): ";
        }

        if (choice == 1) { gym.bookAppointment(c); system("pause"); }
        else if (choice == 2) { system("cls"); c->viewWorkoutHistory(); cout<<"\nPress key..."; _getch(); }
    } while (choice != 3);
}

// ==========================================
//                MAIN FUNCTION
// ==========================================
int main() {
    system("color 0A"); 

    GymSystem mySystem; 
    
    int opt;
    while (true) {
        system("cls");
        cout << "\n============================================\n";
        cout << "      GYM MANAGEMENT & FITNESS SYSTEM       \n";
        cout << "============================================\n";
        cout << " 1. ADMINISTRATOR\n";
        cout << " 2. TRAINER\n";
        cout << " 3. CUSTOMER\n";
        cout << " 4. EXIT\n";
        cout << "============================================\n";
        cout << " Select Your Role: ";
        
        if(!(cin >> opt)) { 
            cin.clear(); 
            cin.ignore(1000, '\n'); 
            continue; 
        }
        
        if (opt == 1) adminPanel(mySystem);
        else if (opt == 2) trainerPanel(mySystem);
        else if (opt == 3) customerPanel(mySystem);
        else if (opt == 4) break;
    }
    return 0;
}