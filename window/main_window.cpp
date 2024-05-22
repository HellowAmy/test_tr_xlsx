
#include "main_window.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QUdpSocket>
#include <QComboBox>
#include <QApplication>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

#include "wid_check_dig.h"

#include "Txml_tr.h"

#include "Tvlog.h"

main_window::main_window(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle(tr("Translate Tools"));

    QVBoxLayout *lay_main = new QVBoxLayout(this);

    QPushButton *butt_xlse = new QPushButton(tr("To Xlsx"),this);
    QPushButton *butt_ts = new QPushButton(tr("To Ts"),this);

    QLineEdit *edit_src_ts = new QLineEdit(this);
    QLineEdit *edit_xlsx = new QLineEdit(this);
    QLineEdit *edit_dst_ts = new QLineEdit(this);

    edit_src_ts->setText("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/src_ts");
    edit_xlsx->setText("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/tm_xlsx");
    edit_dst_ts->setText("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/dst_ts");

    {
        QLabel *lab = new QLabel(tr("Source Ts Path:"),this);
        QPushButton *browse = new QPushButton(tr("Browse"),this);

        connect(browse,&QPushButton::clicked,[=](){
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            edit_src_ts->setText(dir);
        });

        QHBoxLayout *lay = new QHBoxLayout;
        lay->addWidget(lab);
        lay->addWidget(edit_src_ts);
        lay->addWidget(browse);
        lay_main->addLayout(lay);
    }
    {
        QLabel *lab = new QLabel(tr("Xlsx Savs Path:"),this);
        QPushButton *browse = new QPushButton(tr("Browse"),this);

        connect(browse,&QPushButton::clicked,[=](){
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            edit_xlsx->setText(dir);
        });

        QHBoxLayout *lay = new QHBoxLayout;
        lay->addWidget(lab);
        lay->addWidget(edit_xlsx);
        lay->addWidget(browse);
        lay_main->addLayout(lay);
    }

    {
        QLabel *lab = new QLabel(tr("Target Ts Path:"),this);
        QPushButton *browse = new QPushButton(tr("Browse"),this);

        connect(browse,&QPushButton::clicked,[=](){
            QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"));
            edit_dst_ts->setText(dir);
        });

        QHBoxLayout *lay = new QHBoxLayout;
        lay->addWidget(lab);
        lay->addWidget(edit_dst_ts);
        lay->addWidget(browse);
        lay_main->addLayout(lay);
    }

    {
        QHBoxLayout *lay = new QHBoxLayout;
        lay->addWidget(butt_xlse);
        lay->addWidget(butt_ts);
        lay_main->addLayout(lay);
    }

    connect(butt_xlse,&QPushButton::clicked,[=](){
        QString src = edit_src_ts->text();
        QString dst = edit_xlsx->text();

        if(src != "" && dst != "")
        {
            ts_to_xlsx(src,dst);
        }
        else 
        {
            wid_check_dig dig;
            dig.set_txt_tips(tr("Source Ts Path And Xlsx Savs Path Is Empty"));
            dig.exec();
        }
    });

    connect(butt_ts,&QPushButton::clicked,[=](){
        QString src = edit_xlsx->text();
        QString dst = edit_dst_ts->text();

        if(src != "" && dst != "")
        {
            xlsx_to_ts(src,dst);
        }
        else 
        {
            wid_check_dig dig;
            dig.set_txt_tips(tr("Xlsx Savs Path And Target Ts Path Is Empty"));
            int ret = dig.exec();
            vlogd($(ret));
        }
    });



    // QPushButton *butt = new QPushButton(tr("Switch","main_window"),this);
    // QLabel *lab = new QLabel(tr("Show Tips","main_window"),this);

    // QComboBox *combo = new QComboBox(this);
    // combo->addItem("English");
    // combo->addItem("中文");

    // QHBoxLayout *lay = new QHBoxLayout(this);
    // lay->addWidget(lab);
    // lay->addWidget(butt);
    // lay->addWidget(combo);
}

main_window::~main_window()
{
}

void main_window::ts_to_xlsx(QString src, QString dst)
{
    QString suffix = ".xlsx";
    QDir dir(src);
    auto ls = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    for(auto &a:ls)
    {
        QFileInfo info(a);
        QString src_file = src + "/" + info.fileName();
        QString dst_file = dst + "/" + info.baseName() + suffix;
        vlogd($Q(src_file) $Q(dst_file));
        Txml_tr xml;
        bool oks = xml.open_ts(src_file);
        bool okd = xml.save_xlsx(dst_file);
        vlogd($(oks) $(okd) $Q(src_file) $Q(dst_file));
    }

}

void main_window::xlsx_to_ts(QString src, QString dst)
{
    QString suffix = ".ts";
    QDir dir(src);
    auto ls = dir.entryList(QDir::NoDotAndDotDot | QDir::Files);
    for(auto &a:ls)
    {
        QFileInfo info(a);
        QString src_file = src + "/" + info.fileName();
        QString dst_file = dst + "/" + info.baseName() + suffix;
        Txml_tr xml;
        bool oks = xml.open_xlsx(src_file);
        bool okd = xml.save_ts(dst_file);
        vlogd($(oks) $(okd) $Q(src_file) $Q(dst_file));
    }
}
