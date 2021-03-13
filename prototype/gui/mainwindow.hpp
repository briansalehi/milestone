#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFile>
#include <QMenuBar>
#include <QStatus>
#include <QLabel>
#include <QString>
#include <QLineEdit>
#include <QTextEdit>

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

	QLineEdit* titleLineEdit;
	QLineEdit* tagLineEdit;

	QTextEdit* commentTextEdit;
	QTextEdit* referenceTextEdit;

	QVBoxLayout* centralLayout;
	QGridLayout* editingLayout;
	QHBoxLayout* buttonsLayout;

	QWidget* centralWidget;

	QPushButton* submitButton;
	QPushButton* cancelButton;
};
