#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QMenuBar>
#include <QStatusBar>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>
#include <QTextBrowser>
#include <QComboBox>
#include <QStringList>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);

private:
	void setupFields();
	void setupButtons();
	void setupLayouts();
	void loadContent();

	QLabel* titleLabel;
	QLabel* commentLabel;
	QLabel* referenceLabel;
	QLabel* tagLabel;
	QLabel* sourceLabel;
	QLabel* difficultyLabel;

	QLabel* title;
	QLabel* tag;
	QComboBox* difficulty;
	QTextBrowser* comment;
	QTextBrowser* reference;
	QTextBrowser* source;

	QVBoxLayout* centralLayout;
	QGridLayout* editingLayout;
	QHBoxLayout* buttonsLayout;

	QWidget* centralWidget;

	QPushButton* submitButton;
	QPushButton* cancelButton;
};
