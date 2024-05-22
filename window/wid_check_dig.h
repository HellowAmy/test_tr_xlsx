
#ifndef WID_CHECK_DIG_H
#define WID_CHECK_DIG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class wid_check_dig : public QDialog
{
    Q_OBJECT
public:
    wid_check_dig(QWidget *parent = nullptr);
    ~wid_check_dig();

    void set_txt_tips(const QString &s);

signals:    

protected:
    QLabel *_lab = nullptr;
};
#endif // WID_CHECK_DIG_H
