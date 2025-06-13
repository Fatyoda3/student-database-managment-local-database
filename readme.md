
---

```markdown
# 🎓 Student Database Management (Terminal App)

A colorful, interactive terminal-based Student Record Management System written in C.

> Made with ❤️ by  — for learning and fun.

---

## 🌟 Features

- Add new student records (name, age, grade)
- Load records into heap memory (simulates dynamic memory usage)
- Colorful and friendly terminal UI (ANSI codes supported)
- Cross-platform support (Windows + Linux(haven't tested yet) )
- Automatically organizes records by date folders
- Sounds and loading spinners for extra flair (may or may not work)




## ⚙️ How to Build (Windows + Chocolatey)

1. **Install make + GCC (MinGW):**

   Open **PowerShell as Administrator**, and run:

   ```powershell
   choco install make mingw
````

Once installed, restart your terminal (or VS Code).

2. **Build the App:**

   ```bash
   make
   ```

   Output: `build/app.exe` 🎉

3. **Run the App:**

   ```bash
   ./build/app
   ```

---

## 🧹 Cleaning Up

To remove object files and the executable:

```bash
make clean
```

---

## ✨ Example Usage

```bash
--- Student Records Menu ---
1. Create new student record
2. Read records from file
3. Retrieve specific record
4. Load and show records from heap
0. Exit

Enter your choice: 1
Enter name: John
Enter age: 21
Enter grade: A
✔️ Done!
✅ Record added!
```

---

## 📚 Prerequisites for Beginners

* Basic C programming knowledge
* `make` and GCC installed (or use VSCode with build tasks)

---

## 🧠 Future Ideas

* Export data to CSV
* Add search by name


Made with C.

