# 🌲 Forest Fire Model

A simple C implementation of the **Forest Fire cellular automaton model** using **SDL2** for visualization.

---

## 🧰 Requirements

- [SDL2 2.0.22 (VC)](https://github.com/libsdl-org/SDL/releases/download/release-2.0.22/SDL2-devel-2.0.22-VC.zip)
- Windows
- Visual Studio (with _x64 Native Tools Command Prompt for VS_)

---

## 🧭 How to Run

### 1. Use the proper CLI

Launch `x64 Native Tools Command Prompt for VS`

### 2. Move to the project directory

```
cd C:\<YOUR_PATH>\forest-fire-model\src
```
### 3. Compile
```
cl main.c forest.c /I"..\SDL2-2.0.22\include" ^
  /link /LIBPATH:"..\SDL2-2.0.22\lib\x64" ^
  SDL2.lib SDL2main.lib Shell32.lib User32.lib /SUBSYSTEM:CONSOLE
```

⚠️ Make sure SDL2.dll is in the same folder as main.exe, or in your system PATH.

### 4. Run the simulation
```
main.exe
```

---

### 📂 Project Structure
```
forest-fire-model/
├── SDL2-2.0.22/          # SDL2 (not tracked in Git)
├── src/
│   ├── main.c
│   ├── config.h
│   ├── forest.c
│   ├── forest.h
│   └── main.exe          # Output binary
├── .gitignore
└── README.md
```

---

### 📸 Preview
(Add a screenshot or GIF here to show how the simulation looks!)