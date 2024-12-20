# Air Draw

Air Draw is a Qt-based whiteboard application that allows users to draw, sketch, and annotate in an interactive and user-friendly interface.

## Features
- Simple and intuitive whiteboard interface.
- Support for multiple tools like pen, eraser, and shapes.
- Save and load your drawings.
- Lightweight and responsive design.

## Project Structure
The repository consists of the following files and directories:
- **main.cpp**: Entry point of the application.
- **mainwindow.cpp** and **mainwindow.h**: Define the main window UI and logic.
- **whiteboard.cpp** and **whiteboard.h**: Core functionality for the drawing canvas.
- **media.qrc**: Qt resource file for managing application assets (like icons or images).
- **resources/**: Contains additional assets such as icons and logos.
- **whiteboard.pro**: Qt project file for building the application.
- **build/**: Directory for build files (generated during compilation).

## Prerequisites
To run or build the application, ensure you have the following installed:
- [Qt Framework](https://www.qt.io/download): Version 5.12 or higher is recommended.
- A C++ compiler (e.g., GCC or MSVC).
- CMake (optional, if using a CMake-based build system).

## Setup Instructions
### Cloning the Repository
```bash
git clone https://github.com/kh44key/WhiteBoard-App
cd WhiteBoard-App
```

### Building the Application
1. Open the project in Qt Creator:
   - Launch **Qt Creator**.
   - Click on "Open Project" and select the `whiteboard.pro` file.
2. Configure the project using your desired build kit (e.g., Desktop Qt 5.15.2 GCC 64bit).
3. Click the "Build" button to compile the application.
4. Run the application by clicking the "Run" button in Qt Creator.

Alternatively, you can use the command line:
```bash
qmake whiteboard.pro
make
./Whiteboard-App
```

### Running the Application
After building, you can run the application directly from the `build` directory or within Qt Creator.

## Screenshots
![image](https://github.com/user-attachments/assets/a74045fb-4467-4f60-982d-05245c2008bf)
