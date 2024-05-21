
#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QTranslator>


class main_window : public QWidget
{
    Q_OBJECT
public:
    main_window(QWidget *parent = nullptr);
    ~main_window();

signals:
    void sn_click();

protected:

private:
    QTranslator *_trp = nullptr;

    void ts_to_xlsx(QString src,QString dst);
    void xlsx_to_ts(QString src,QString dst);


};
#endif // MAIN_WINDOW_H
