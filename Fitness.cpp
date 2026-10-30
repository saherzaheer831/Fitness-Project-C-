#include "Fitness.h"
#include <cstdlib> 
#include <ctime>   

// --- HELPERS ---
int timeToMinutes(string t) {
    size_t colonPos = t.find(':');
    if(colonPos == string::npos) return 0;
    int hrs = stoi(t.substr(0, colonPos));
    int mins = stoi(t.substr(colonPos+1));
    return (hrs * 60) + mins;
}

// Naya Helper: Check karta hai ke date1, date2 se pehle hai ya nahi
bool isDateBefore(string date1, string date2) {
    int d1, m1, y1, d2, m2, y2;
    sscanf(date1.c_str(), "%d/%d/%d", &d1, &m1, &y1);
    sscanf(date2.c_str(), "%d/%d/%d", &d2, &m2, &y2);
    if (y1 < y2) return true;
    if (y1 > y2) return false;
    if (m1 < m2) return true;
    if (m1 > m2) return false;
    return d1 < d2;
}

bool isValidDate(int d, int m, int y) {
    if (y < 2025 || y > 2099) return false; 
    if (m < 1 || m > 12) return false;      
    if (d < 1 || d > 31) return false;      
    if (m == 2) {
        bool isLeap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (isLeap && d > 29) return false;
        if (!isLeap && d > 28) return false;
    } else if (m == 4 || m == 6 || m == 9 || m == 11) {
        if (d > 30) return false; 
    }
    return true; 
}

// --- WORKOUTS ---
Workout::Workout(string n, int d, string dt) {
    name = n;               
    duration = d;           
    date = dt;             
    caloriesBurned = 0.0;    
}

// 2. Default Constructor: Taake child classes ko asani ho
Workout::Workout() {
    name = "Unknown";
    duration = 0;
    date = "00/00/0000";
    caloriesBurned = 0.0;
}

// 3. Calories hasil karne ka function
double Workout::getCalories() const { 
    return caloriesBurned; 
}

// 4. Details dikhane ka function (Formatting ke saath)
void Workout::displayInfo() const {
    cout << left << setw(15) << date 
         << setw(20) << name 
         << setw(10) << duration 
         << setw(10) << fixed << setprecision(1) << caloriesBurned << " kcal" << endl;
}


// Constructor: Ab koi colon nahi hai
Cardio::Cardio(string dt, int dur) {
    name = "Cardio";         // Direct name assign kiya
    duration = dur;          // Direct duration assign ki
    date = dt;               // Direct date assign ki
    calculateCalories();     // Body ke andar hi calculation call ki
}

// Calorie Calculation Logic
void Cardio::calculateCalories() { 
    // Cardio ka fixed rate: 1 minute = 8.0 calories
    caloriesBurned = duration * 8.0; 
}

// Display Logic
void Cardio::displayInfo() const { 
    // Parent class (Workout) ka table format use kiya
    Workout::displayInfo(); 
}

// Constructor:
Strength::Strength(string dt, int dur, string intel) {
    name = "Strength";      // Direct assignment
    duration = dur;         // Direct assignment
    date = dt;              // Direct assignment
    intensity = intel;      // User ki di hui intensity (High/Medium/Low)
    calculateCalories();    // Body ke andar calculation call ki
}

// Calories Calculation Logic (3 Levels)
void Strength::calculateCalories() {
    double mult;
    
    // Logic: Intensity ke mutabiq multiplier set karna
    if (intensity == "High" || intensity == "high") {
        mult = 10.0;        // Heavy lifting ke liye bara multiplier
    } 
    else if (intensity == "Medium" || intensity == "medium") {
        mult = 7.0;         // Normal gym workout ke liye
    } 
    else {
        mult = 4.0;         // Low intensity ya warm-up ke liye
    }
    
    caloriesBurned = duration * mult;
}

// Display Logic
void Strength::displayInfo() const { 
    Workout::displayInfo(); // Parent class ka formatted table use kiya
}

// Constructor: Sara data curly brackets ke andar assign kiya
Yoga::Yoga(string dt, int dur, int diff) {
    name = "Yoga";          // Direct assignment
    duration = dur;         // Direct assignment
    date = dt;              // Direct assignment
    difficulty = diff;      // Difficulty level (1 to 10)
    calculateCalories();    // Body ke andar calculation call ki
}

// Calories Calculation Logic (Scaling 1 to 10)
void Yoga::calculateCalories() {
    double multiplier = difficulty * 1.2;
    // ceil() function decimal ko round up kar deta hai
    caloriesBurned = ceil(duration * multiplier);
}

// Display Logic
void Yoga::displayInfo() const { 
    Workout::displayInfo(); // Parent class ka formatted table use kiya
}

// UPDATED MMA LOGIC: Different styles have different calories
// Constructor: Ab yahan koi colon (:) nahi hai
MMA::MMA(string dt, int dur, string s) {
    name = "MMA (" + s + ")"; //string Concentenation se name banaya
    duration = dur;          // Minutes assign kiye
    date = dt;               // Date assign ki
    style = s;               // Fighting style (Boxing/Judo etc) save kiya
    calculateCalories();     // Body ke andar hi calculation call ki
}

// Calorie Calculation Logic (Style based)
void MMA::calculateCalories() { 
    // Logic: Har style ki intensity alag hoti hai
    if (style == "Boxing" || style == "boxing" || style == "Kickboxing") {
        // Boxing/Kickboxing mein cardio movement sab se zyada hoti hai
        caloriesBurned = duration * 12.0; 
    } 
    else if (style == "Karate" || style == "Judo" || style == "karate") {
        // Traditional martial arts ka rate darmiyana hai
        caloriesBurned = duration * 10.0; 
    } 
    else {
        // Baqi tamaam styles ke liye aik default rate
        caloriesBurned = duration * 8.5;  
    }
}

// Display Logic
void MMA::displayInfo() const { 
    Workout::displayInfo(); // Parent class ka formatted table use kiya
}













// --- TRAINER CONSTRUCTOR ---
Trainer::Trainer(string i, string n, string pass, string spec) {
    id = i;
    name = n;
    password = pass;
    speciality = spec;
}
// --- GETTER FUNCTIONS ---
string Trainer::getID() const { 
    return id; 
}
string Trainer::getName() const { 
    return name; 
}
string Trainer::getPassword() const { 
    return password; 
}
string Trainer::getSpeciality() const { 
    return speciality; 
}
// --- SCHEDULE GETTER ---
vector<Appointment> Trainer::getSchedule() const { 
    return schedule; 
}
void Trainer::addAppointment(string cName, string cID, string d, string t, int dur) {
    schedule.push_back({cName, cID, d, t, dur});
}


// Check if slot is free
bool Trainer::isSlotFree(string d, string startTime, int duration) const {
    int newStart = timeToMinutes(startTime);
    int newEnd = newStart + duration;
    for(const auto& app : schedule) {
        if(app.date == d) {
            int existStart = timeToMinutes(app.time);
            int existEnd = existStart + app.durationMins;
            if (newStart < existEnd && existStart < newEnd) return false; 
        }
    }
    return true;
}


//Cancel appointment by Customer ID
void Trainer::cancelAppointment(string cID) {
    bool found = false;
    for (auto it = schedule.begin(); it != schedule.end(); ) {
        //it is Inspector or pointer we can say it itrator short form
        if (it->customerID == cID) {
            it = schedule.erase(it);
            found = true;
            cout << ">>> SUCCESS: Appointment cancelled for ID: " << cID << ".\n";
        } else ++it;
    }
    if(!found) cout << ">>> ERROR: Customer ID not found in your schedule.\n";
}



// --- TRAINER ASSIGN WORKOUT (UPDATED DATE LOGIC) ---
void Trainer::assignWorkout(Customer* cust) {
    if (cust->getAssignedTrainer() == "None") {
        cout << ">>> ERROR: Customer must have an appointment first!\n";
        return;
    }

    int choice;
    cout << "\n----------------------------------------\n";
    cout << "   ASSIGN WORKOUT TO: " << cust->getName() << endl;
    cout << "   Appointment Date: " << cust->getApptDate() << endl;
    cout << "----------------------------------------\n";
    cout << "1. Cardio\n2. Strength\n3. Yoga\n4. MMA\nSelect Type (0 to Cancel): ";
    cin >> choice;
    if(choice == 0) return;

    int d, m, y, dur;
    while(true) {
        cout << "Enter Date (DD MM YYYY) [0 0 0 to Cancel]: "; 
        cin >> d >> m >> y;
        if(d == 0) return; 
        string wDate = to_string(d) + "/" + to_string(m) + "/" + to_string(y);
        
        if(!isValidDate(d,m,y)) cout << ">>> Invalid Date!\n";
        else if (isDateBefore(wDate, cust->getApptDate())) {
            cout << ">>> ERROR: Cannot assign workout BEFORE appointment date (" << cust->getApptDate() << ")!\n";
        } else break;
    }
    //Concatenation of date string
    string dateStr = to_string(d) + "/" + to_string(m) + "/" + to_string(y);
    
    while(true) {
        cout << "Duration (mins) [0 to Cancel]: ";
        cin >> dur;
        if(dur == 0) return; 
        if(dur >= 30 && dur <= 180) break;
        cout << ">>> Error: 30-180 mins only.\n";
    }

    if(choice == 1) cust->logCardio(dateStr, dur);
    else if(choice == 2) { 
        string i; cout << "Intensity (Medium/High) [0 to Cancel]: "; cin >> i; 
        if(i == "0") return; 
        cust->logStrength(dateStr, dur, i); 
    }
    else if(choice == 3) { 
        int diff; cout << "Difficulty (1-10) [0 to Cancel]: "; cin >> diff; 
        if(diff == 0) return; 
        cust->logYoga(dateStr, dur, diff); 
    }
    else if(choice == 4) { 
        string s; cout << "Style (Boxing/Judo) [0 to Cancel]: "; cin >> s; 
        if(s == "0") return; 
        cust->logMMA(dateStr, dur, s); 
    }
}

void Trainer::viewSchedule() const {
    cout << "\n=======================================================\n";
    cout << "          SCHEDULE FOR " << name << " (" << id << ")\n";
    cout << "==========================================================\n";
    cout << left << setw(12) << "DATE" << setw(10) << "TIME" << setw(10) << "DUR" << setw(15) << "CLIENT" << endl;
    cout << "----------------------------------------------------------\n";
    if(schedule.empty()) { cout << "No appointments booked.\n"; return; }
    for(const auto& a : schedule) 
        cout << left << setw(12) << a.date << setw(10) << a.time << setw(10) << (to_string(a.durationMins)+"m") << setw(15) << a.customerName << endl;
}
// --- CONSTRUCTOR ---
Customer::Customer(string i, string n, string pass, int a, double h, double w) {
    id = i;              
    name = n;            
    password = pass;      
    age = a;              
    height = h;           
    weight = w;           
    assignedTrainer = "None"; 
    apptDate = "None";       
}
// --- DESTRUCTOR ---
Customer::~Customer() { 
    for(auto w : workoutLog) {
        delete w; // Har aik workout object ko memory se mitao
    }
    workoutLog.clear(); // List ko poora khali kar do
}
// --- GETTER FUNCTIONS (Data dekhne ke liye) ---
string Customer::getID() const { 
    return id; }
string Customer::getName() const {
     return name; }
string Customer::getPassword() const { 
    return password; }
string Customer::getAssignedTrainer() const { 
    return assignedTrainer; }
string Customer::getApptDate() const {
     return apptDate; }

// --- SETTER FUNCTIONS (Data badalne ke liye) ---
void Customer::setTrainer(string tName) { 
    assignedTrainer = tName; // Naya trainer assign karne ke liye
}
void Customer::setApptDate(string d) { 
    apptDate = d; // Appointment ki tareekh pakki karne ke liye
}

void Customer::showProfile() const {
    cout << "\n====================================\n";
    cout << "          CUSTOMER PROFILE          \n";
    cout << "====================================\n";
    cout << " ID:       " << id << "\n Name:     " << name << "\n Age:      " << age << "\n Weight:   " << weight << " kg\n Height:   " << height << " feet\n";
    cout << " Trainer:  " << assignedTrainer << "\n";
    cout << "------------------------------------\n";
}

void Customer::logCardio(string date, int dur) { 
    workoutLog.push_back(new Cardio(date, dur)); cout << ">>> Cardio Assigned!\n"; 
  }
void Customer::logStrength(string date, int dur, string intensity) {
     workoutLog.push_back(new Strength(date, dur, intensity)); cout << ">>> Strength Assigned!\n";
    }
void Customer::logYoga(string date, int dur, int diff) {
     workoutLog.push_back(new Yoga(date, dur, diff)); cout << ">>> Yoga Assigned!\n"; 
    }
void Customer::logMMA(string date, int dur, string style) {
     workoutLog.push_back(new MMA(date, dur, style)); cout << ">>> MMA Assigned!\n"; 
    }

void Customer::viewWorkoutHistory() const {
    if(workoutLog.empty()) { cout << "\n[!] No workouts assigned yet.\n"; return; }
    cout << "\n=======================================================\n";
    cout << "             WORKOUT HISTORY (ASSIGNED)                \n";
    cout << "=======================================================\n";
    cout << left << setw(15) << "DATE" << setw(20) << "TYPE" << setw(10) << "MINS" << setw(10) << "CALS" << endl;
    cout << "-------------------------------------------------------\n";
    double total = 0;
    for(const auto& w : workoutLog) { w->displayInfo(); total += w->getCalories(); }
    cout << "-------------------------------------------------------\n";
    cout << "TOTAL CALORIES BURNED: " << total << " kcal\n";
}

// --- GYM SYSTEM ---
GymSystem::GymSystem() {
    //srand(time(0)); 
    trainers.push_back(Trainer("T1", "Umair", "1234", "Bodybuilding"));
    trainers.push_back(Trainer("T2", "Sahar", "2345", "Yoga"));
    trainers.push_back(Trainer("T3", "Isbah", "4565", "Cardio"));
    trainers.push_back(Trainer("T4", "Furqan", "9876", "Karate/MMA"));

    customers.push_back(new Customer("C101", "Ahmed", "4565", 25, 5.8, 75));
    for(int i=2; i<=30; i++) {
        string id = "C1" + (i<10 ? "0"+to_string(i) : to_string(i));
        string pass = to_string(1000 + (rand() % 9000));
        customers.push_back(new Customer(id, "User"+to_string(i), pass, 18+i, 5.5+(i*0.1), 65));
    }
}
GymSystem::~GymSystem() { 
    for(auto c : customers) delete c; }
bool GymSystem::adminLogin(string u, string p) { 
    return (u == "HaxxonBoy" && p == "Haxxon123"); 
    //Check and generate unique IDs
}
bool GymSystem::isTrainerIDTaken(string id) { 
    for(const auto& t : trainers)
     if(t.getID() == id) 
     return true; 
     return false;
 }
bool GymSystem::isCustomerIDTaken(string id) {
     for(const auto& c : customers) if(c->getID() == id) return true; return false; }

string GymSystem::generateTrainerID() {
    int next = 1;
    while(true) { string id = "T" + to_string(next); if(!isTrainerIDTaken(id)) return id; next++; }
}
string GymSystem::generateCustomerID() {
    int next = 101;
    while(true) { string id = "C" + to_string(next); if(!isCustomerIDTaken(id)) return id; next++; }
}
void GymSystem::updateUserPassword() {
    string adminP;
    cout << "\nSecurity Check: Enter Admin Password: "; cin >> adminP;
    if(adminP != "Haxxon123") { cout << ">>> ACCESS DENIED!\n"; return; }

    string id, newP;
    cout << "Enter User ID (Trainer/Customer) to Update: ";
     cin >> id;

    for(auto &t : trainers) {
        if(t.getID() == id) {
            cout << "Trainer Found: " << t.getName() << "\nEnter New Password: ";
            cin >> newP;
            t.setPassword(newP);
            cout << ">>> SUCCESS: Password updated!\n";
            return;
        }
    }
    Customer* c = findCustomerByID(id);
    if(c != nullptr) {
        cout << "Customer Found: " << c->getName() << "\nEnter New Password: ";
        cin >> newP;
        c->setPassword(newP);
        cout << ">>> SUCCESS: Password updated!\n";
    } else {
        cout << ">>> ERROR: ID not found!\n";
    }
}
//viewCredentials

void GymSystem::viewCredentials() {
    string p;
    cout << "\nWARNING: Restricted Area! Enter Admin Password (0 to Cancel): "; cin >> p;
    if(p == "0") return; 
    
    if(p == "Haxxon123") {
        cout << "\n================================================\n";
        cout << "            SECRET CREDENTIALS LIST             \n";
        cout << "================================================\n";
        cout << "--- TRAINERS ---\n";
        cout << left << setw(10) << "ID" << setw(15) << "NAME" << setw(15) << "PASSWORD" << endl;
        for(const auto& t : trainers) cout << left << setw(10) << t.getID() << setw(15) << t.getName() << setw(15) << t.getPassword() << endl;

        cout << "\n--- CUSTOMERS ---\n";
        cout << left << setw(10) << "ID" << setw(15) << "NAME" << setw(15) << "PASSWORD" << endl;
        for(const auto& c : customers) cout << left << setw(10) << c->getID() << setw(15) << c->getName() << setw(15) << c->getPassword() << endl;
        cout << "================================================\n";
    } else { cout << ">>> ACCESS DENIED!\n"; }
}



void GymSystem::addTrainer() {
    string i = generateTrainerID();
    cout << "\n>>> Auto-Generated ID: " << i << endl;
    string n, p, s;
    
    while(true) {
        cout << "Name (Alphabets) [0 to Cancel]: "; cin.ignore(); getline(cin, n);
        if(n == "0") return;
        bool ok = true; for(char c:n) if(!isalpha(c) && c!=' ') ok=false;
        if(ok && !n.empty()) break;
    }
    while(true) {
        cout << "Password (min 4 chars) [0 to Cancel]: "; cin >> p;
        if(p == "0") return;
        if(p.length() >= 4) break;
    }
    cout << "Speciality [0 to Cancel]: "; cin >> s;
    if(s == "0") return;

    trainers.push_back(Trainer(i,n,p,s)); cout << ">>> SUCCESS: Trainer Added!\n";
}


void GymSystem::deleteTrainer() {
    string id; cout << "Enter ID to Delete (0 to Cancel): "; cin >> id; if(id=="0") return;
    for(auto it=trainers.begin(); it!=trainers.end(); ) {
        if(it->getID()==id) { it=trainers.erase(it); cout<<">>> DELETED Successfully!\n"; return; } else ++it;
    } cout << ">>> Error: Not found.\n";
}

void GymSystem::addCustomer() {
    string i = generateCustomerID();
    string n, p; int a; double h, w;
    cout << "\nAuto-Assigned ID: " << i << endl;
    
    while(true) {
        cout << "Enter Name [0 to Cancel]: "; cin.ignore(); getline(cin, n);
        if(n == "0") return;
        bool ok = true; for(char c:n) if(!isalpha(c) && c!=' ') ok=false;
        if(ok && !n.empty()) break;
    }
    while(true) {
        cout << "Set Password (min 4 chars) [0 to Cancel]: "; cin >> p;
        if(p == "0") return;
        if(p.length() >= 4) break;
        cout << ">>> Min 4 chars required!\n";
    }
    while(true) {
        cout << "Age (Min 16) [0 to Cancel]: "; cin >> a;
        if(a == 0) return; 
        if(a>=16 && a<=75) break;
        cout << ">>> Minimum age is 16!\n";
    }
    while(true) {
        cout << "Height (Feet: 4.0-7.5) [0 to Cancel]: "; cin >> h;
        if(h == 0) return;
        if(h>=4.0 && h<=7.5) break;
        cout << ">>> Height must be 4.0 to 7.5 feet!\n";
    }
    while(true) {
        cout << "Weight (40-200 kg) [0 to Cancel]: "; cin >> w;
        if(w == 0) return;
        if(w>=40 && w<=200) break;
    }
    customers.push_back(new Customer(i,n,p,a,h,w));
    cout << ">>> SUCCESS: Registered!\n";
}

Customer* GymSystem::findCustomerByID(string id) { for(auto c : customers) if(c->getID() == id) return c; return nullptr; }

void GymSystem::viewAllTrainers() { 
    cout << "\n--- ALL TRAINERS ---\n"; 
    for(const auto& t : trainers) cout << t.getID() << " | " << t.getName() << " | " << t.getSpeciality() << endl; 
}
void GymSystem::viewAllCustomers() { 
    cout << "\n--- ALL CUSTOMERS ---\n"; 
    for(const auto& c : customers) cout << c->getID() << " | " << c->getName() << endl; 
}
void GymSystem::viewAllAppointments() { for(const auto& t : trainers) t.viewSchedule(); }

Trainer* GymSystem::trainerLogin(string id, string pass) {
    for(auto& t : trainers) if(t.getID() == id && t.getPassword() == pass) return &t;
    return nullptr;
}
Customer* GymSystem::customerLogin(string id, string pass) {
    for(auto c : customers) if(c->getID() == id && c->getPassword() == pass) return c;
    return nullptr;
}

void GymSystem::bookAppointment(Customer* currentCust) {
    // Double Booking Prevention
    if (currentCust->getAssignedTrainer() != "None") {
        cout << ">>> ERROR: You already have an active appointment with " << currentCust->getAssignedTrainer() << "!\n";
        return;
    }

    string tid, t; int d, m, y, hour, minute, dur;
    viewAllTrainers();
    cout << "\nEnter Trainer ID (0 to Cancel): "; cin >> tid; if(tid=="0") return;
    for(auto& tr : trainers) {
        if(tr.getID() == tid) {
            while(true) {
                cout << "Date (DD MM YYYY) [0 0 0 to Cancel]: "; cin >> d >> m >> y;
                if(d == 0) return; 
                if(isValidDate(d,m,y)) break;
            }
            string dateStr = to_string(d)+"/"+to_string(m)+"/"+to_string(y);
            while(true) {
                cout << "Time (HH MM) [0 0 to Cancel]: "; cin >> hour >> minute;
                if(hour == 0 && minute == 0) return;
                if(hour>=0 && hour<=23 && minute>=0 && minute<=59) break;
            }
            string minStr = (minute<10)? "0"+to_string(minute):to_string(minute);
            t = to_string(hour)+":"+minStr;
            while(true) {
                cout << "Duration (30-180 mins) [0 to Cancel]: "; cin >> dur;
                if(dur == 0) return; 
                if(dur >= 30 && dur <= 180) break;
            }
            if(tr.isSlotFree(dateStr, t, dur)) {
                tr.addAppointment(currentCust->getName(), currentCust->getID(), dateStr, t, dur);
                currentCust->setTrainer(tr.getName()); 
                currentCust->setApptDate(dateStr); // Save the appointment date
                cout << "\n>>> SUCCESS: Appointment Booked!\n";
            } else cout << "\n[!!!] FAILED: Slot Busy!\n";
            return;
        }
    }
}