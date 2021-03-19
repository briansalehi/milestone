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
	sourceLabel = new QLabel("Source:");

	titleLineEdit= new QTextBrowser;
	titleLineEdit->setPlaceholderText("Page Title");

	tagLineEdit = new QTextBrowser;
	tagLineEdit->setPlaceholderText("Page Tag");

	commentTextEdit = new QTextBrowser;
	commentTextEdit->setPlaceholderText("Page Description");

	referenceTextEdit = new QTextBrowser;
	referenceTextEdit->setPlaceholderText("Reference List");

	sourceTextEdit = new QTextBrowser;
	sourceTextEdit->setPlaceholderText("Source");
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
	editingLayout->addWidget(sourceLabel, 4, 0);
	editingLayout->addWidget(sourceTextEdit, 4, 1);

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
	if (QCoreApplication::arguments().count() < 2)
		exit(1);

	QString fileName = QCoreApplication::arguments().at(1);
	QFile file(fileName);
	file.open(QFile::ReadOnly | QFile::Text);
	if (file.isOpen()) {
		QString content = file.readAll();
		sourceTextEdit->setPlainText(content);
	} else {
		statusBar()->setStyleSheet("QStatusBar{color: red}");
		statusBar()->showMessage("File not found: " + fileName);
		return;
	}

	fileName = fileName.remove(QRegExp("\\.[^\\.]*$"));

	QString titleFileName(fileName);
	titleFileName.append(".title.txt");
	QFile titleFile(titleFileName);
	titleFile.open(QFile::ReadOnly | QFile::Text);
	if (titleFile.isOpen()) {
		QString content = titleFile.readAll();
		titleLineEdit->setText(content);
	}

	QString tagFileName(fileName);
	tagFileName.append(".alias.txt");
	QFile tagFile(tagFileName);
	tagFile.open(QFile::ReadOnly | QFile::Text);
	if (tagFile.isOpen()) {
		QString content = tagFile.readAll();
		tagLineEdit->setText(content);
	}

	QString referenceFileName(fileName);
	referenceFileName.append(".reference.txt");
	QFile referenceFile(referenceFileName);
	referenceFile.open(QFile::ReadOnly | QFile::Text);
	if (referenceFile.isOpen()) {
		QString content = referenceFile.readAll();
		referenceTextEdit->setPlainText(content);
	}

	QString commentFileName(fileName);
	commentFileName.append(".comment.txt");
	QFile commentFile(commentFileName);
	commentFile.open(QFile::ReadOnly | QFile::Text);
	if (commentFile.isOpen()) {
		QString content = commentFile.readAll();
		commentTextEdit->setPlainText(content);
	}
}
