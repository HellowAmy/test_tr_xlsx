
#include "wid_check_dig.h"

wid_check_dig::wid_check_dig(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("Tips"));
    this->resize(400,250);

    _lab = new QLabel(this);
    _lab->setAlignment(Qt::AlignCenter);

    QPushButton *butt_cancel = new QPushButton(tr("Cancel"),this);

    QPushButton *butt_confirm = new QPushButton(tr("Confirm"),this);


    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(butt_cancel);
    lay->addWidget(butt_confirm);


    QVBoxLayout *lay_main = new QVBoxLayout(this);
    lay_main->addWidget(_lab);
    lay_main->addLayout(lay);


    connect(butt_cancel,&QPushButton::clicked,[=](){
        QDialog::reject();
    });

    connect(butt_confirm,&QPushButton::clicked,[=](){
        QDialog::accept();
    });

}

wid_check_dig::~wid_check_dig()
{
}

void wid_check_dig::set_txt_tips(const QString &s)
{
    _lab->setText(s);
}
