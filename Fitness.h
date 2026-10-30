#ifndef FITNESS_H
#define FITNESS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// --- HELPERS ---
int timeToMinutes(string t);
bool isValidDate(int d, int m, int y);
bool isDateBefore(string date1, string date2); 

// ==========================================
//            WORKOUT CLASSES
// ==========================================
class Workout {
protected:
    string name;
    int duration;
    double caloriesBurned;
    string date;
public:
    Workout(string n, int d, string dt);
    Workout();
    virtual ~Workout() {}
    virtual void calculateCalories() = 0;
    virtual void displayInfo() const;
    double getCalories() const;
};

// ... (Cardio, Strength, Yoga, MMA classes remain same)
class Cardio : public Workout {
public:
    Cardio(string dt, int dur);
    void calculateCalories() override;
    void displayInfo() const override;
};

class Strength : public Workout {
    string intensity;
public:
    Strength(string dt, int dur, string intel);
    void calculateCalories() override;
    void displayInfo() const override;
};

class Yoga : public Workout {
    int difficulty;
public:
    Yoga(string dt, int dur, int diff);
    void calculateCalories() override;
    void displayInfo() const override;
};

class MMA : public Workout {
    string style;
public:
    MMA(string dt, int dur, string s);
    void calculateCalories() override;
    void displayInfo() const override;
};

// ==========================================
//           APPOINTMENT & ACTORS
// ==========================================
struct Appointment {
    string customerName;
    string customerID;
    string date;
    string time;     
    int durationMins; 
};

class Customer; 

class Trainer {
private:
    string id, name, password, speciality;
    vector<Appointment> schedule;
public:
    Trainer(string i, string n, string pass, string spec);
    string getID() const;
    string getName() const;
    string getPassword() const;
    string getSpeciality() const;

    // UPDATE: Admin ko password badalne ki ijazat dene ke liye
    void setPassword(string newPass) { password = newPass; }
    
    void addAppointment(string cName, string cID, string d, string t, int dur);
    void cancelAppointment(string cID);
    bool isSlotFree(string d, string startTime, int duration) const; 
    void assignWorkout(Customer* cust); 
    void viewSchedule() const;
    vector<Appointment> getSchedule() const;
};

class Customer {
private:
    string id, name, password;
    int age;
    double height; 
    double weight;
    string assignedTrainer;
    string apptDate; 
    vector<Workout*> workoutLog; 

public:
    Customer(string i, string n, string pass, int a, double h, double w);
    ~Customer(); 

    string getID() const;
    string getName() const;
    string getPassword() const;
    void setPassword(string newPass) { password = newPass; }

    string getAssignedTrainer() const;
    string getApptDate() const;      
    void setTrainer(string tName);
    void setApptDate(string d);      
    void showProfile() const;

    void logCardio(string date, int dur);
    void logStrength(string date, int dur, string intensity);
    void logYoga(string date, int dur, int diff);
    void logMMA(string date, int dur, string style);
    
    void viewWorkoutHistory() const;
};

// ==========================================
//               GYM SYSTEM
// ==========================================
class GymSystem {
private:
    vector<Trainer> trainers;
    vector<Customer*> customers;
    
    bool isTrainerIDTaken(string id);
    bool isCustomerIDTaken(string id);
    string generateTrainerID();
    string generateCustomerID();

public:
    GymSystem();
    ~GymSystem(); 

    bool adminLogin(string u, string p);
    void addTrainer();   
    void deleteTrainer(); 
    void addCustomer();  
    void viewAllTrainers();
    void viewAllCustomers();
    void viewAllAppointments();
    void viewCredentials(); 

    // NEW: Admin kisi ka bhi password manually change kar sakay
    void updateUserPassword(); 

    Trainer* trainerLogin(string id, string pass);
    Customer* customerLogin(string id, string pass);
    
    void bookAppointment(Customer* currentCust); 
    Customer* findCustomerByID(string id);
};

#endif