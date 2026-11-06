Address Book System by Maelys Azevedo
A menu-driven C++ console application that stores company contacts and lets you view them all or search by name or department. I built it for my Intermediate Software Design in C++ class (CS 2B) at Foothill College in November 2025.

Features
  View all contacts in a formatted table (name, title or contract length, department or company, room, phone, email)
  Search by name with a first and last name
  Search by department (employees only)
  Two contact types, employees and contractors, each displayed in its own format
  Sample data for 17 contacts (employees and contractors) loaded at startup

C++ concepts used
  Inheritance and polymorphism: ShowContact() is a virtual function, so each contact type prints itself correctly through a base-class pointer
  Abstract base class: Contact cannot be instantiated directly
  Linked list with manual memory management: contacts are allocated with new, and the ContactList destructor walks the list and deletes every node
  Virtual destructor: ensures derived objects are cleaned up correctly when deleted through a Contact*
  Operator overloading: == for comparing names and << for printing them
  dynamic_cast: used in the department search to pick out employees from the mixed list of contacts
  Default values: static const members provide defaults for each class

Usage
  TP Communications Address Book Menu
  1. View all contacts
  2. Search by name
  3. Search by department
  4. Quit
  Select an option (1-4):
  Search by name: enter the first name, then the last name (for example, David then Summer). Matching is exact and case-sensitive.
  Search by department: enter a department exactly as stored (for example, Engineering, Finance, Marketing). Contractors have no department, so they are not included.

Ideas for Future Improvements
  Add, edit, and delete contacts from the menu
  Save and load contacts from a file instead of hardcoded sample data
  Case-insensitive and partial-match searching
  Input validation for non-numeric menu choices
