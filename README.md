# Patricia Tree Dictionary System

## Description
This repository contains a dictionary management system implemented using a Patricia tree. The project was developed for the Data Structures II course at UNIOESTE, and is designed to handle a collection of words for quick prefix-based searches and efficient dictionary operations.

## Features
- **Load Text File**: Constructs a Patricia tree from a text file containing one word per line.
- **Query Word**: Searches for words in the dictionary that start with a given prefix, displaying up to 10 words in alphabetical order.
- **Print Dictionary**: Outputs all words in the dictionary in alphabetical order.
- **Load Stopwords File**: Removes all words found in a provided stopwords file from the dictionary.
- **Print Subtree by Levels**: Given a prefix, displays all subtrees under it by levels, including the number of children at each subtree.

### Technical Details
- **Implementation**: The system is developed in C.
- **Data Structure**: Utilizes the Patricia tree for efficient word management and prefix searches.

## Known Issues
- **Documentation**: While the code implementation is correct, documentation within the codebase is minimal and will be enhanced in future revisions.

## How to Use
### Compilation and Execution
To compile and run the program, use the following commands:
```bash
gcc -o dictionarySystem *.c
./dictionarySystem
