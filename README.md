<h1 align="center">
  <img src="banner.jpg" width="1000">
</h1>

<h4 align="center">A minimal OCR to complete your SUDOKU grids.</h4>

<p align="center">
  <img src="https://img.shields.io/github/repo-size/QuentinHayK/OCR-Sudoku">
  <img src="https://img.shields.io/github/downloads/QuentinHayK/OCR-Sudoku/total">
  <img src="https://img.shields.io/github/last-commit/QuentinHayK/OCR-Sudoku">
</p>

<p align="center">
  <a href="#key-features">Key Features</a> •
  <a href="#requirement">Requirement</a> •
  <a href="#installation">Installation</a> •
   <a href="#usage">Usage</a>
</p>

# OCR-Sudoku
Developped in C with ❤ by <a href="https://www.epita.fr" target="_blank"> Epita </a> students.

## Key Features

* Train a `Neural Network`
* Test your `Neural Network`
  - Some `data` are provided with the project

## Requirement
```bash
$ sudo apt-get install libsdl1.2-dev
$ sudo apt install libsdl2-image-dev 
```

## Installation
```bash
# Clone this repository
$ git clone https://github.com/QuentinHayK/OCR-Sudoku
```
> **Note**
> The project was made for `linux` only, we can't help you if you have any trouble with other OS.

## Usage
```bash
# Compile code
$ make

# Run program without parameters
$ make run

# Run program to train a new Neural Network (folder must be in data/ folder) and layerI are integers (number of nodes p/ layer)
$ make run-train nn="layer1, layer2, ..., layerN" folder="folder_name" save="save_NN.txt"

# Run program to test the last saved Neural Network
$ make run-test nn="layer1, layer2, ..., layerN" save="save_NN.txt"

# Clean folders
$ make clean
```
