# SocialNet Simulator

**Course:** COL106 - Data Structures and Algorithms  
**Institute:** Indian Institute of Technology Delhi  
**Name:** Mora Adarsha  
**Entry Number:** 2024CS10367  
**Assignment:** Long Assignment 2  
**Date:** November 5, 2025

---

## Table of Contents
1. [Introduction](#introduction)
2. [How to Compile and Run](#how-to-compile-and-run)
3. [Design Decisions](#design-decisions)
4. [Data Structures Used](#data-structures-used)
5. [Error Handling](#error-handling)
6. [Command Reference with Complexity](#command-reference-with-complexity)
7. [Key Implementation Details](#key-implementation-details)
8. [File Structure](#file-structure)

---

## Introduction

**SocialNet Simulator** is a command-line program that works like a simple social media platform. The program allows you to create user accounts, make friends, post messages, and find connections between users.

### What Can You Do?

- **Add Users:** Create new user accounts
- **Make Friends:** Connect two users as friends
- **View Friends:** See all friends of a user
- **Get Suggestions:** Find potential friends based on mutual connections
- **Find Connections:** Calculate how many steps it takes to reach one user from another
- **Create Posts:** Users can write posts with timestamps
- **View Posts:** See recent posts from any user

The program reads commands from the keyboard (or a file) and shows results immediately.

---

## How to Compile and Run

### Prerequisites
- **C++ Compiler:** g++ with C++17 support
- **Operating System:** Windows (PowerShell)

### Compilation

Use the following command in PowerShell:
```bash
g++ -std=c++17 -Wall -Wextra -o socialnet.exe main.cpp
```

Alternatively, you can use the provided batch file:
```bash
.\compile.bat
```

### Running the Program

#### Interactive Mode:
```bash
.\socialnet.exe
```

#### With Input File:
```bash
Get-Content testcases.txt | .\socialnet.exe > output.txt
```

### Running Tests
To test with provided test cases and compare with expected output:
```bash
Get-Content testcases.txt | .\socialnet.exe > my_output.txt
cmd /c fc my_output.txt actual_output.txt
```

---

## Design Decisions

This program uses custom C++ implementations of Graph and AVL Tree data structures:

- **Graph:** Users are vertices, friendships are edges. HashMap provides O(1) username lookup.
- **AVL Trees:** Self-balancing binary search trees store friends (alphabetically), posts (by time), and suggestions (by mutual friend count).
- **Comparators:** Allow the same AVL tree implementation to sort different data types.
- **Case Insensitivity:** All text converted to lowercase for consistency.

---

## Data Structures Used

### Graph (Social Network)
**File:** `Graph.hpp`

Main class managing all users and their connections. Uses HashMap for O(1) username lookup.

### AVL Tree
**File:** `AVLTree.hpp`

A self-balancing binary search tree that maintains sorted data.

**Functions:**
- `insert()`: Add a new item
- `getElements()`: Get items in sorted order
- `contains()`: Check if an item exists

### User Class
**File:** `User.hpp`

Represents one user in the social network.

**Attributes:**
- `username`: User's name (lowercase)
- `friends`: AVL tree of friends (alphabetically sorted)
- `posts`: AVL tree of posts (sorted by time, newest first)

### Node Structures
**File:** `DataStructures.hpp`

**FriendNode:** Stores pointer to friend's User object

**PostNode:** Stores post content and timestamp

**SuggestionNode:** Stores potential friend and mutual friend count

### Comparators
**File:** `Comparators.hpp`

**FriendComparator:** Sorts friends alphabetically

**PostComparator:** Sorts posts by time (newest first)

**SuggestionComparator:** Sorts by mutual friend count (descending), then alphabetically

---

## Error Handling

The program handles various types of errors and invalid inputs:

### Invalid Commands
- If you type a command that doesn't exist, the program shows an error message
- Example: Typing "DELETE_USER" will show "Unknown command" error
- Type `HELP` to see all valid commands

### User Not Found
- If you try to operate on a user that doesn't exist, you get an error
- Example: "Error: User alice not found"

### Already Exists
- Cannot add a user that already exists
- Cannot make two users friends if they're already friends
- Example: "Error: Users are already friends"

### Invalid Input Format
- Missing quotes around post content: "Error: Post content must be enclosed in quotes"
- Missing parameters: "Error: Usage: ADD_FRIEND <username1> <username2>"
- Invalid numbers: "Error: Number must be an integer"

### Logical Errors
- Cannot add yourself as a friend: "Error: Cannot add self as friend"
- Cannot perform operations with empty usernames

The program continues running even after errors, so you can correct and retry commands.

---

## Command Reference with Complexity

### ADD_USER
**Syntax:** `ADD_USER <username>`

**Description:** Adds a new user to the network with no friends or posts.

**Example:**
```
ADD_USER alice
```

**Complexity:**
- **Time:** O(1) - Constant time
- **Space:** O(1) - Just stores one user

**Error Cases:** Username already exists

---

### ADD_FRIEND
**Syntax:** `ADD_FRIEND <username1> <username2>`

**Description:** Makes two users friends (works both ways).

**Example:**
```
ADD_FRIEND alice bob
```

**Complexity:**
- **Time:** O(log F) - Logarithmic time
- **Space:** O(1) - No extra space needed

**Variables:**
- F = number of friends a user has

**Error Cases:** User not found, already friends, cannot add self as friend

---

### LIST_FRIENDS
**Syntax:** `LIST_FRIENDS <username>`

**Description:** Shows all friends of a user in alphabetical order.

**Example:**
```
LIST_FRIENDS alice
```

**Complexity:**
- **Time:** O(F) - Linear time
- **Space:** O(F) - Stores list of friends

**Variables:**
- F = number of friends

**Error Cases:** User not found, user has no friends

---

### SUGGEST_FRIENDS
**Syntax:** `SUGGEST_FRIENDS <username> <N>`

**Description:** Suggests potential friends based on mutual connections. Shows people who are friends-of-friends but not direct friends.

**Example:**
```
SUGGEST_FRIENDS alice 3
```

**Complexity:**
- **Time:** O(F₁ × F₂ + S log S)
- **Space:** O(S) - Stores suggestions

**Variables:**
- F₁ = number of friends the user has
- F₂ = average number of friends each friend has
- S = number of suggestions found

**Special Cases:** N = -1 (all suggestions), N = 0 (nothing)

**Error Cases:** User not found, no suggestions available

---

### DEGREES_OF_SEPARATION
**Syntax:** `DEGREES_OF_SEPARATION <username1> <username2>`

**Description:** Finds the shortest path between two users. Returns how many friendship links connect them.

**Example:**
```
DEGREES_OF_SEPARATION alice eve
```

**Complexity:**
- **Time:** O(V + E) - Linear in network size
- **Space:** O(V) - Stores visited users

**Variables:**
- V = total number of users in the network
- E = total number of friendships

**Algorithm:** Uses BFS (Breadth-First Search)

**Special Cases:** Same user (returns 0), no path (returns -1)

**Error Cases:** User not found

---

### ADD_POST
**Syntax:** `ADD_POST <username> "<post content>"`

**Description:** Creates a post for a user. Content must be in quotes.

**Example:**
```
ADD_POST alice "Hello World!"
```

**Complexity:**
- **Time:** O(log P) - Logarithmic time
- **Space:** O(1) - Just stores one post

**Variables:**
- P = number of posts the user has

**Error Cases:** User not found, missing quotes

---

### OUTPUT_POSTS
**Syntax:** `OUTPUT_POSTS <username> <N>`

**Description:** Shows the N most recent posts from a user (newest first).

**Example:**
```
OUTPUT_POSTS alice 2
```

**Complexity:**
- **Time:** O(min(N, P)) - Linear in posts shown
- **Space:** O(min(N, P)) - Stores posts to display

**Variables:**
- P = total posts by user
- N = number of posts requested
- min(N, P) = whichever is smaller

**Special Cases:** N = -1 (all posts), N = 0 (nothing)

**Error Cases:** User not found, user has no posts

---

### HELP
**Syntax:** `HELP`

**Description:** Shows all available commands.

**Complexity:** O(1) - Just prints text

---

### EXIT
**Syntax:** `EXIT`

**Description:** Closes the program.

**Complexity:** O(1) - Instant

---

## Key Implementation Details

### AVL Tree
- Works for any data type (friends, posts, suggestions)
- Automatically stays balanced using rotations
- Can use different sorting rules with comparators

### Friend Suggestions
- Uses HashMap to count mutual friends quickly
- AVL tree sorts suggestions automatically
- Works fast even with many friends

### Finding Shortest Path
- Uses BFS (Breadth-First Search) algorithm
- Checks friends level-by-level
- Guarantees shortest path

### Memory Management
- Properly frees memory when program ends
- No memory leaks
- All users and data are cleaned up automatically

---

## File Structure

```
.
├── main.cpp              # Main program and command handling
├── Graph.hpp             # Social network graph
├── User.hpp              # User class
├── AVLTree.hpp           # AVL tree implementation
├── Comparators.hpp       # Sorting functions
├── DataStructures.hpp    # Data containers (nodes)
├── compile.bat           # Compilation script
└── README.md             # Documentation
```

---
