Abstract
The Cafeteria Management System is a console based  C program designed to automate cafeteria operations, providing different interfaces for customers and administrators. Customer module allows viewing menu, placing orders, calculating final bill and generating receipts. The Administration module is secured by a password which allows staff to update menu items, add/remove food items, update stock, change prices, manage inventory and 
1. Introduction
Managing a cafeteria involves multiple tasks including taking orders, updating menus, keeping track of stock, and calculating bills. These tasks become time-consuming and prone to human error when done manually.
This project provides a simple computerized system where customers can place orders instantly, and administrators can modify menu items or update stock securely. The program strengthens foundational concepts like arrays, functions, structures, loops, decision making, and file handling

2. Objectives
To develop a functional cafeteria system that supports both Customers and Administrators.
To provide secure access to administrative features through password verification.
To allow admins to update menus, add/remove items, change prices, and manage stock.
To allow customers to view menu, place orders, calculate total bills, and generate receipts.
To practice programming concepts such as conditional statements, loops, structures, arrays, and file input/output.
To build a simple, clear, and user-friendly menu-based interface.



3. System Design
System Overview
Flow of the program:

Start → Display Main Menu → Choose Customer/Admin →
If Admin: Verify Password → Perform Updates
If Customer: Display Menu → Take Order → Calculate Bill and show receipt → Exit
Algorithm
1.Start the program
2.Display Main Menu (Admin or Customer)
3.If user selects Admin:
Ask for password
If correct → show admin controls
Update menu/stock/prices as required
4.If user selects Customer:
Display menu
Take order and quantity
Check stock availability
Compute total bill and display receipt

5.Save updated stock/menu in files
6.End program
Input & Output
Input:
Customer order selections
Admin updates (new item, price, stock levels)
Password for admin login
Output: 
Menu display
Updated stock list
Calculated bill and receipt
Confirmation messages for admin operations
