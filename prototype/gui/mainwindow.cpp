#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	setWindowTitle("Notebook Editor");
	setWindowIcon(QIcon(QPixmap("notebook.png")));

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
	difficultyLabel = new QLabel("Difficulty:");

	title= new QLabel("Page Title");

	tag = new QLabel("Page Tag");

	QStringList difficultyItems({"Basic", "Intermediate", "Expert"});
	difficulty = new QComboBox;
	difficulty->addItems(difficultyItems);

	comment = new QTextBrowser;
	comment->setPlaceholderText("Page Description");

	reference = new QTextBrowser;
	reference->setPlaceholderText("Reference List");

	source = new QTextBrowser;
	source->setPlaceholderText("Source Sample");
}

void MainWindow::setupButtons()
{
	submitButton = new QPushButton("Save");
	cancelButton = new QPushButton("Cancel");
}

void MainWindow::setupLayouts()
{
	editingLayout = new QGridLayout;
	editingLayout->addWidget(titleLabel, 0, 0);
	editingLayout->addWidget(title, 0, 1);
	editingLayout->addWidget(tagLabel, 1, 0);
	editingLayout->addWidget(tag, 1, 1);
	editingLayout->addWidget(difficultyLabel, 2, 0);
	editingLayout->addWidget(difficulty, 2, 1);
	editingLayout->addWidget(referenceLabel, 3, 0);
	editingLayout->addWidget(reference, 3, 1);
	editingLayout->addWidget(commentLabel, 4, 0);
	editingLayout->addWidget(comment, 4, 1);
	editingLayout->addWidget(sourceLabel, 5, 0);
	editingLayout->addWidget(source, 5, 1);

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
		source->setPlainText(content);
		file.close();
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
		title->setText(content);
		titleFile.close();
	}

	QString tagFileName(fileName);
	tagFileName.append(".alias.txt");
	QFile tagFile(tagFileName);
	tagFile.open(QFile::ReadOnly | QFile::Text);
	if (tagFile.isOpen()) {
		QString content = tagFile.readAll();
		tag->setText(content);
		tagFile.close();
	}

	QString difficultyFileName(fileName);
	difficultyFileName.append(".difficulty.txt");
	QFile difficultyFile(difficultyFileName);
	difficultyFile.open(QFile::ReadOnly | QFile::Text);
	if (difficultyFile.isOpen()) {
		QString content = difficultyFile.readAll();
		difficulty->setCurrentIndex(1);
		difficultyFile.close();
	}

	QString referenceFileName(fileName);
	referenceFileName.append(".reference.txt");
	QFile referenceFile(referenceFileName);
	referenceFile.open(QFile::ReadOnly | QFile::Text);
	if (referenceFile.isOpen()) {
		QString content = referenceFile.readAll();
		reference->setPlainText(content);
		referenceFile.close();
	}

	QString commentFileName(fileName);
	commentFileName.append(".comment.txt");
	QFile commentFile(commentFileName);
	commentFile.open(QFile::ReadOnly | QFile::Text);
	if (commentFile.isOpen()) {
		QString content = commentFile.readAll();
		comment->setPlainText(content);
		commentFile.close();
	}
}
