# Fitness-Project-C++
# 🏋️ Gym Management & Fitness System

A console-based Gym Management System developed in C++ that simplifies gym operations through role-based access for administrators, trainers, and customers.

The system provides functionality for managing gym staff, registering customers, booking appointments, assigning workout plans, and tracking customer workout history.

## ✨ Features

- **Admin Management:** Add and remove trainers, register customers, view records, manage appointments, and update user passwords.
- **Trainer Management:** View personal schedules, cancel appointments, and assign workout plans to customers.
- **Customer Portal:** View personal profiles, book trainer appointments, and access assigned workout history.
- **Secure Login Interface:** Role-based authentication with masked password input.
- **Input Validation:** Handles invalid menu inputs to improve application usability.
- **Appointment Management:** Manage bookings between trainers and customers.

## 👥 User Roles

| Role | Main Responsibilities |
|---|---|
| Administrator | Manage trainers, customers, credentials, and appointments |
| Trainer | View schedules, cancel bookings, and assign workout plans |
| Customer | Book appointments and view workout history |

## 🛠️ Technologies Used

- **Language:** C++
- **Programming Concepts:** Object-Oriented Programming (OOP)
- **Libraries:** iostream, limits, conio.h, cstdlib
- **Interface:** Console-Based Application

## 🚀 Getting Started

### Prerequisites
- C++ compiler (MinGW or compatible Windows compiler).
- Code editor or IDE (Visual Studio Code, Code::Blocks, etc.).

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
```

**2. Navigate to the project directory**

cd YOUR-REPOSITORY
```

**3. Compile the project**

```bash
g++ main1.cpp Fitness.cpp -o GymSystem
```
**4.Run the application**
```bash
GymSystem.exe
```
*Note: The project requires the `Fitness.h` header and its corresponding implementation file. It also uses Windows-specific functions such as `conio.h`, `_getch()`, and `system("cls")`.*

## 📂 Project Structure
Gym-Management-System/
│
├── main1.cpp       # Main application and role-based menus
├── Fitness.h       # Gym system class declarations
├── Fitness.cpp     # Class implementations
└── README.md       # Project documentation
```
## 🎯 Project Objective

To develop a structured gym management application that demonstrates object-oriented programming concepts while providing an organized way to manage gym administrators, trainers, customers, appointments, and workout plans.
## 🔮 Future Improvements

- Database integration for permanent data storage.
- Graphical user interface (GUI).
- Online appointment booking.
- Automated membership management.
- Workout progress tracking and reporting.
---
**Developed with C++ | Gym Management & Fitness System**
