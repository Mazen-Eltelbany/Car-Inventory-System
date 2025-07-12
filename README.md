# Car Inventory Management System

This is a simple C++ console application that manages a car dealership's inventory. It allows users to add, view, delete, and compare original (new) and used cars. Data is stored and retrieved from text files to maintain persistence across runs.

## 🧩 Features

- 📄 Show all original (new) cars
- 📄 Show all used cars
- ➕ Add a new original or used car
- ❌ Delete a car (both original and used)
- ### 🔍 Compare two used cars based on:

  - Year (newer is better)
  - Distance driven (lower is better)
  - Motor power (higher is better)

## Requirements

- C++ Compiler (e.g., g++, Visual Studio)
- Console environment
- Text files (orgcars.txt and Usedcars.txt) should exist or will be created

## How It Works

- Cars are stored as records in a delimited format using ' #//# '.
- The app reads from and writes to the corresponding text files (orgcars.txt, Usedcars.txt).
- A menu-driven interface allows users to interact with the system easily.
- Deleted cars are filtered out by marking them and rewriting the file without them.

## ▶️ How to Run

### Option 1: Using Git

1-**Clone the repo:**

```bash
git clone https://github.com/Mazen-Eltelbany/Car-Inventory-System.git
```

2-**Navigate to the project:**

```bash
cd Car-Inventory-System
```

3- **Compile:**
"If you don't have a g++ compiler download from this video"
<a href="https://youtu.be/GxFiUEO_3zM">The Installation guide</a>

```bash
g++ Car-Project.cpp -o CP
```

4- **Run:**

```bash
./CP
```

### Option 2: Download As ZIP:

**1- Download the ZIP:**

- Go to the repo: Car-Inventory-System on GitHub
- Click the green "Code" button → Download ZIP
- Extract it anywhere on your computer

**2- Open The Folder:**

```bash
cd Car-Inventory-System-main
```

**3- Compile And Run:**

```bash
g++ Car-Project.cpp -o CP
./CP
```

## Author

- 👤 Mazen Eltelbany
