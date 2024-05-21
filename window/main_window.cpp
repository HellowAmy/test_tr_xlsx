
#include "main_window.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QUdpSocket>
#include <QComboBox>
#include <QApplication>
#include <QLabel>

#include "Tvlog.h"

main_window::main_window(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("Main Window"));

    QPushButton *butt = new QPushButton(tr("Switch","main_window"),this);
    QLabel *lab = new QLabel(tr("Show Tips","main_window"),this);

    QComboBox *combo = new QComboBox(this);
    combo->addItem("English");
    combo->addItem("中文");

    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->addWidget(lab);
    lay->addWidget(butt);
    lay->addWidget(combo);
}

main_window::~main_window()
{
}