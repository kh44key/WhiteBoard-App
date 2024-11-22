#include <QApplication>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPixmap>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    m_whiteboard = new WhiteBoard;

    // Create a container for the buttons and logo
    QWidget* topBar = new QWidget(this);

    // Create a horizontal layout for the top bar
    QHBoxLayout* topBarLayout = new QHBoxLayout;

    // Add a logo to the top-left corner
    QLabel* logoLabel = new QLabel;
    QPixmap logoPixmap(":/images/logo.png"); // Replace with your logo path
    logoLabel->setPixmap(logoPixmap.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    topBarLayout->addWidget(logoLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);

    // Create a container for the buttons
    QGroupBox* buttonBar = new QGroupBox;
    buttonBar->setStyleSheet("QGroupBox { border: 2px solid black; border-radius: 5px; padding: 5px; }");
    buttonBar->setMaximumHeight(60); // Restrict height for better aesthetics

    // Horizontal layout for the buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // Create Buttons
    QPushButton* btnBlue = new QPushButton("Blue");
    btnBlue->setStyleSheet("background-color: blue; color: white; font-weight: bold;");

    QPushButton* btnRed = new QPushButton("Red");
    btnRed->setStyleSheet("background-color: red; color: white; font-weight: bold;");

    QPushButton* btnGreen = new QPushButton("Green");
    btnGreen->setStyleSheet("background-color: green; color: white; font-weight: bold;");

    QPushButton* btnUndo = new QPushButton("Undo");
    btnUndo->setStyleSheet("font-weight: bold;");

    QPushButton* btnRedo = new QPushButton("Redo");
    btnRedo->setStyleSheet("font-weight: bold;");

    QPushButton* btnSmall = new QPushButton("Small Pen");
    QPushButton* btnMedium = new QPushButton("Medium Pen");
    QPushButton* btnLarge = new QPushButton("Large Pen");

    QPushButton* btnClear = new QPushButton("Clear");
    btnClear->setStyleSheet("background-color: white; color: black; font-weight: bold;");

    // Add buttons to the layout
    buttonLayout->addWidget(btnBlue);
    buttonLayout->addWidget(btnRed);
    buttonLayout->addWidget(btnGreen);
    buttonLayout->addSpacing(10); // Add a little spacing for grouping
    buttonLayout->addWidget(btnSmall);
    buttonLayout->addWidget(btnMedium);
    buttonLayout->addWidget(btnLarge);
    buttonLayout->addSpacing(10); // More spacing
    buttonLayout->addWidget(btnUndo);
    buttonLayout->addWidget(btnRedo);
    buttonLayout->addSpacing(10);
    buttonLayout->addWidget(btnClear);

    // Assign layout to the button bar
    buttonBar->setLayout(buttonLayout);

    // Center the buttons in the top bar
    topBarLayout->addWidget(buttonBar, 1, Qt::AlignCenter);

    topBar->setLayout(topBarLayout);

    // Main layout with whiteboard
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topBar, 0, Qt::AlignTop);
    mainLayout->addWidget(m_whiteboard, 1); // Make the whiteboard take all remaining space

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Connect Buttons to Slots
    connect(btnBlue, &QPushButton::pressed, this, &MainWindow::setPenBlue);
    connect(btnRed, &QPushButton::pressed, this, &MainWindow::setPenRed);
    connect(btnGreen, &QPushButton::pressed, this, &MainWindow::setPenGreen);
    connect(btnSmall, &QPushButton::pressed, this, &MainWindow::setPenSizeSmall);
    connect(btnMedium, &QPushButton::pressed, this, &MainWindow::setPenSizeMedium);
    connect(btnLarge, &QPushButton::pressed, this, &MainWindow::setPenSizeLarge);
    connect(btnUndo, &QPushButton::pressed, this, &MainWindow::undoAction);
    connect(btnRedo, &QPushButton::pressed, this, &MainWindow::redoAction);
    connect(btnClear, &QPushButton::pressed, this, &MainWindow::clearScreen);
}

void MainWindow::setPenBlue()
{
    m_whiteboard->setPenColor(Qt::blue);
}

void MainWindow::setPenRed()
{
    m_whiteboard->setPenColor(Qt::red);
}

void MainWindow::setPenGreen()
{
    m_whiteboard->setPenColor(Qt::green);
}

void MainWindow::clearScreen()
{
    m_whiteboard->clearImage();
}

void MainWindow::undoAction()
{
    m_whiteboard->undo();
}

void MainWindow::redoAction()
{
    m_whiteboard->redo();
}

void MainWindow::setPenSizeSmall()
{
    m_whiteboard->setPenSize(2);
}

void MainWindow::setPenSizeMedium()
{
    m_whiteboard->setPenSize(5);
}

void MainWindow::setPenSizeLarge()
{
    m_whiteboard->setPenSize(10);
}

void MainWindow::keyPressEvent(QKeyEvent* k)
{
    if (k->key() == Qt::Key_0) // Exit on '0'
    {
        QApplication::instance()->exit();
    }
    else if (k->modifiers() & Qt::ControlModifier) // Check for Ctrl key
    {
        if (k->key() == Qt::Key_Z) // Ctrl + Z for Undo
        {
            m_whiteboard->undo();
        }
        else if (k->key() == Qt::Key_Y) // Ctrl + Y for Redo
        {
            m_whiteboard->redo();
        }
    }
}

MainWindow::~MainWindow()
{
}

