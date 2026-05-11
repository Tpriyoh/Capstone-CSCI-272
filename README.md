# Security Event Log Analyzer (SentinelOps)

CSCI 272 — Object Oriented Programming — Capstone Project

**Team:** Bilal Ahmed, Ibrahim Jahangir, Miguel Llapa, Tanzin Priyoh, Tun Tun (Jonathan) Aung

---

## What the program is

A C++ menu-driven application that lets a security analyst load, search, report on, and modify a collection of real-world security events. Every event is attempts to follow 

## What it does

- Loads existing events from `events.csv` at startup
- Lets the user **add**, **view**, **search**, **delete**, **report on**, and **save** events through a 7-option menu
- Persists changes back to `events.csv` on exit
- Demonstrates **inheritance** (Event → IntrusionEvent / MalwareEvent), **polymorphism** (`vector<Event*>` + virtual `display()` / `toCSV()`), **operator overloading + template** (`template <typename T> T& operator<<`), **STL** (`vector`, `set`, `stringstream`), **file I/O**, and **exception handling**

| File | Owner | Role |
|---|---|---|
| `Event.h` / `Event.cpp` | Tun Tun (Jonathan) | base class  fields, virtual functions, static validateSeverity, template operator<< |
| `IntrusionEvent.h` / `.cpp` | Tanzin | derived class adds attackType + attemptCount |
| `MalwareEvent.h` / `.cpp` | Bilal | derived class  adds malwareType + affectedFile |
| `EventManager.h` / `.cpp` | Miguel | owns `vector<Event*>`, add / search / delete / report |
| `FileHandler.h` / `.cpp` | Ibrahim | CSV load / save, bubble sort, binary search, try/catch |
| `main.cpp` | All | menu loop and lifecycle |

## CSV format

Eight comma-separated fields per row. The first field is the type discriminator.

```
INTRUSION,eventID,timestamp,ipAddress,severity,cveID,attackType,attemptCount
MALWARE  ,eventID,timestamp,ipAddress,severity,cveID,malwareType,affectedFile
```

Severity must be one of: `LOW`, `MEDIUM`, `HIGH`, `CRITICAL`.

---

### Exception handling
- At any "Enter your option (1-7):" prompt, type `abc` instead of a number. Expected: `Error: Must enter a number between 1-7.` and the menu re-displays without crashing.
- Rename `events.csv` to `events.csv.bak` and run the program. Expected: `FileHandler Error: File could not be opened: events.csv` followed by `Starting with an empty event list instead.` Program continues normally.

---

## Rubric concept map

| Concept | Where it lives |
|---|---|
| Class definition (header/impl split) | All five class files |
| Encapsulation | `protected` data + getters in Event |
| Inheritance | IntrusionEvent / MalwareEvent inherit from Event |
| Polymorphism | `vector<Event*>` + virtual `display()` / `toCSV()` + virtual `~Event()` |
| Operator overloading | `template <typename T> T& operator<<` in Event.h |
| Template `<typename T>` | Same templated `operator<<` (T = stream type) |
| `static` member | `Event::validateSeverity()` |
| STL container | `vector<Event*>` (EventManager); `set<string>` (report) |
| File I/O | FileHandler — `ifstream`, `ofstream`, `getline` |
| `stringstream` | FileHandler `splitCSVLine` and event `toCSV` |
| Exception handling | menu try/catch + FileHandler try/catch (load + save + parse) |
| Pointers + dynamic memory | `new` in case 1, `delete` in `~EventManager()` and `deleteEventById` |
| `dynamic_cast` | `EventManager::generateReport()` to count by type |

---

## AI usage note

We used Claude (Anthropic) during planning and to clarify concepts (virtual functions, polymorphism, the difference between member and free-function operator overloads, the trade-offs between member and free-function templates). After completion, AI was then use to check for test cases, explain other teammember's code for understanding. Readme.md layout was designed through AI for pretty graphic and structure syntaxes. Every concept Claude explained was cross-checked against course Lessons 4, 8, and 10 before we used it.
