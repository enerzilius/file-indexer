# file-indexer

## How does it work?

This is a simple command-line application that simulates a text file search mechanism. It reads the files, builds an inverted index and saves it as a file. After that, it is possible to search for keywords, returning a list of documents that have the desired search term.

## Building and running

- Run (on Linux):
```bash
$ make && ./main
```
- That will put you inside the app's CLI. You can then run your desired commands:
```bash
>> indice construir <dir_path>  # Processes the files inside the specified directory and builds its inverted index and saves it as index.dat  
>> indice buscar <search_term> # If there is a `index.dat` file in the directory it is loaded and prints the relevant files
```

- Just use `ctrl+c` to exit the program.

<img width="1469" height="288" alt="image" src="https://github.com/user-attachments/assets/6d537096-682c-46f0-9624-0417cf53a02d" />
