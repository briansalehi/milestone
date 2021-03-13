#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Notebook Editor");
	setWindowIcon(QIcon("notebook.png"));

	setupFields();
	loadContent();
	setupButtons();
	setupLayouts();

	setCentralWidget(centralWidget);

	QObject::connect(cancelButton, &QPushButton::clicked, this, &QApplication::exit);
}

void MainWindow::setupFields()
{
	titleLabel = new QLabel("Title:");
	tagLabel = new QLabel("Tag:");
	referenceLabel = new QLabel("Reference:");
	commentLabel = new QLabel("Comment:");

	titleLineEdit= new QLineEdit;
	titleLineEdit->setPlaceholderText("Page Title");

	tagLineEdit = new QLineEdit;
	tagLineEdit->setPlaceholderText("Page Tag");

	commentTextEdit = new QTextEdit;
	commentTextEdit->setPlaceholderText("Page Description");

	referenceTextEdit = new QTextEdit;
	referenceTextEdit->setPlaceholderText("Reference List");
}

void MainWindow::setupButtons()
{
	submitButton = new QPushButton("Submit");
	cancelButton = new QPushButton("Cancel");
}

void MainWindow::setupLayouts()
{
	editingLayout = new QGridLayout;
	editingLayout->addWidget(titleLabel, 0, 0);
	editingLayout->addWidget(titleLineEdit, 0, 1);
	editingLayout->addWidget(tagLabel, 1, 0);
	editingLayout->addWidget(tagLineEdit, 1, 1);
	editingLayout->addWidget(referenceLabel, 2, 0);
	editingLayout->addWidget(referenceTextEdit, 2, 1);
	editingLayout->addWidget(commentLabel, 3, 0);
	editingLayout->addWidget(commentTextEdit, 3, 1);

	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(cancelButton);
	buttonsLayout->addWidget(submitButton);

	centralLayout = new QVBoxLayout;
	centralLayout->addLayout(editingLayout);
	centralLayout->addStretch();
	centralLayout->addLayout(buttonsLayout);

	centralWidget = new QWidget;
	centralWidget->setLayout(centralLayout);
}

void MainWindow::loadContent()
{
	QFile file("cpp/stl/sequential/vector/initialization.title.txt");
	file.open(QFile::ReadOnly | QFile::Text);
	if (file.isOpen()) {
		QString content = file.readAll();
		titleLineEdit->setText(content);
	} else {
		statusBar()->setStyleSheet("QStatusBar{color: red}");
		statusBar()->showMessage("File not found!");
	}
}
