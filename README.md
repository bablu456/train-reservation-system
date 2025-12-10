🚆 Railway Reservation System (C Project)
A simple Railway Reservation System implemented in C, featuring user registration, login, and ticket booking functionalities. This project demonstrates file handling, structures, and menu-driven programming in C.

📌 Features
User Management

Register new users (stored in users.txt)

Login with username & password

Ticket Management

Book tickets (stored in TrainData.txt)

Cancel tickets by Ticket ID

Search tickets by Ticket ID

View reservation status

View all passenger details

Interactive Menu

Color-coded console output for better readability

Easy navigation through options

🛠️ Technologies Used
Language: C

Concepts: Structures, File Handling, Menu-driven programming

Files Used:

users.txt → Stores registered users

TrainData.txt → Stores booking details

temp.txt → Temporary file used during cancellation

📂 Project Structure
Code
├── Train_Res_System.c   # Main source code
├── users.txt            # Stores registered users
├── TrainData.txt        # Stores booking details
└── temp.txt             # Temporary file for cancellation
▶️ How to Run
Compile the program

bash
gcc Train_Res_System.c -o train_system
Run the executable

bash
./train_system
Follow the menu options

Register → Login → Book/Cancel/Search/View tickets

📖 Example Flow
Start program → Register a user

Login with credentials

Book a ticket by entering details (ID, train number, name, age, gender, status)

Search or cancel tickets using Ticket ID

View passenger list or reservation status

🎯 Learning Outcomes
File handling (fopen, fread, fwrite, remove, rename)

Struct usage for user and booking

Menu-driven program design

Input handling (scanf, fgets, strcspn)

🚀 Future Improvements
Add train schedules and seat availability

Encrypt passwords for better security

Improve UI with better formatting

Add admin panel for managing trains

👨‍💻 Author
Developed by Bablu Kumar Aspiring Full Stack Developer | Passionate about C, Java, and Backend System
