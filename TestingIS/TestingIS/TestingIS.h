#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TestingIS.h"

class TestingIS : public QMainWindow
{
    Q_OBJECT

public:
    TestingIS(QWidget *parent = nullptr);
    ~TestingIS();

private:
    Ui::TestingISClass ui;
};
