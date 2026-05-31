# Inverted Search – C Programming Project (Hash Table Based)

## 📌 Description
The Inverted Search project is a **C-based text search application** that
implements an **inverted index using a hash table** for fast and efficient
word lookup across multiple text files.

Multiple input files (`f1.txt`, `f2.txt`, `f3.txt`, `f4.txt`) are processed to
build a hash table where **each unique word is mapped to the files in which it
appears along with its frequency**.

This project demonstrates **efficient searching using hash tables combined
with linked lists**, which is a core concept in Data Structures and system-level
programming.

---

## 🧠 Concepts Used
- Hash tables
- Linked lists (chaining for collision handling)
- File handling
- Structures
- String manipulation
- Dynamic memory allocation
- Modular programming

---

## 📁 File Structure

```
inverted-search/
├── f1.txt          # Input text file 1
├── f2.txt          # Input text file 2
├── f3.txt          # Input text file 3
├── f4.txt          # Input text file 4
├── main.c          # Program entry point and menu handling
├── functions.c     # Hash table creation and search logic
├── main.h          # Structure definitions and function declarations
└── README.md
```

---

## ▶️ Build and Run

### Compile
```bash
gcc *.c -o inverted_search
```

### Run
```bash
./inverted_search f1.txt f2.txt f3.txt f4.txt
```

---

## 🔍 How It Works
1. Reads multiple input text files.
2. Creates a **hash table** where:
   - Each index represents a hash value.
   - Each bucket uses a **linked list** to handle collisions.
3. Each node stores:
   - Word
   - File name(s)
   - Word occurrence count per file
4. Allows fast searching of a word across all input files.

---

## 🛠️ Tools & Environment
- **Language:** C (ANSI C / C99 compliant)
- **Compiler:** GCC
- **OS:** Linux
- **Version Control:** Git
