# 🎮 Tetris

A simple yet polished Tetris clone built with **C++** and **SFML**.

## ✨ Features
- 🔹 **Three difficulty levels** — block falling speed increases with difficulty  
- 🔹 **Classic gameplay** — rotate, move, and drop blocks to clear lines  
- 🔹 **Score counter** — earn points for every cleared row  
- 🔹 **Clean interface** — smooth visuals powered by SFML  

---

### 🖼️ Screenshot
<picture>
  <source media="(prefers-color-scheme: dark)" srcset="https://github.com/GiperB0la/Tetris/blob/main/Screen.jpg">
  <img alt="Screen" src="https://github.com/GiperB0la/Tetris/blob/main/Screen.jpg">
</picture>

---

## 🛠️ Build

### 🔹 Prerequisites
- **CMake ≥ 3.16**  
- **C++17 compiler** (MSVC, g++, clang++)  
- **SFML 2.6.2** ([download](https://www.sfml-dev.org/download/sfml/2.6.2/))

---

```powershell
# Clone project
git clone https://github.com/GiperB0la/Tetris.git
cd Tetris
mkdir build && cd build

# Configure (set SFML_DIR to your SFML cmake folder)
cmake .. -DSFML_DIR="path/to/SFML/lib/cmake/SFML"

# Build (Release version)
cmake --build . --config Release
