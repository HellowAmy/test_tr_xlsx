#include <QApplication>
#include <QWidget>
#include <QFile>

#include <iostream>
#include <unistd.h>

#include "tinyxml2.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include "window/main_window.h"

#include "Txml_tr.h"
#include "Txlsx.h"
#include "Tvlog.h"
#include "Ttinyxml.h"
#include "Ttx_tmt_tr.h"

using namespace QXlsx;
using namespace std;
using namespace tinyxml2;

void test_1()
{
    QString path_key = "/home/cong/.ssh/TXYKey.txt";
    bool ok = _sp_tmt_tr_->init_handle(path_key);
    if(ok)
    {
        auto vec = _sp_tmt_tr_->get_tmt_tr({
            "Default and autodefault buttons decide what happens when the user presses enter in a dialog that is big dog.",
            "that is dog",
            "me is cat are you is what",
            "have come a bus",
            "will click you face follow China"
        });   
        print_con(vec,1);
    }
};


void show_xml_ts(ct_xml_ts *ct)
{
    vlogd($("===== show_xml_ts : begin ====="));
    vlogd($(ct->ts_version) $(ct->ts_language));

    for(auto itc = ct->context.begin();itc != ct->context.end();itc++)
    {
        vlogd($(itc->name));

        for(auto itm = itc->message.begin();itm != itc->message.end();itm++)
        {
            vlogd($(itm->source) $(itm->comment));
            vlogd($(itm->location_filename) $(itm->location_line));
            vlogd($(itm->translation) $(itm->translation_type));
            vlogd($(""));
        }
        vlogd($(""));
    }
    vlogd($("===== show_xml_ts : end ====="));
}

void test_ts_read_write()
{
    {
        QString file = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.ts";
        QString file_ts = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_ts.ts";
        QString file_xlsx = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_xlsx.xlsx";
        Txml_tr xml;
        {
            bool ok = xml.open_ts(file);
            vlogd($(ok));
        }
        {
            bool ok = xml.save_ts(file_ts);
            vlogd($(ok));
        }
        {
            bool ok = xml.save_xlsx(file_xlsx);
            vlogd($(ok));
        }
        show_xml_ts(&xml.get_data());
    }
    {
        QString file = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.xlsx";
        QString file_ts = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_xlsx_ts.ts";
        QString file_xlsx = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_xlsx_xlsx.xlsx";
        Txml_tr xml;
        {
            bool ok = xml.open_xlsx(file);
            vlogd($(ok));
        }
        {
            bool ok = xml.save_ts(file_ts);
            vlogd($(ok));
        }
        {
            bool ok = xml.save_xlsx(file_xlsx);
            vlogd($(ok));
        }
        show_xml_ts(&xml.get_data());
    }

}




int run_main_app(int argc, char *argv[])
{
    QApplication a(argc,argv);

    QTranslator *trp = new QTranslator(qApp);
    bool ok = trp->load("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/tr_qm/cn.qm");
    if(ok)
    {
        qApp->installTranslator(trp);
    }
    vlogd($(ok));

    main_window w;
    w.resize(500,500);
    w.show();

    return a.exec();
}

int exit_main_app(int run_value)
{
    cout<<"exit run value : "<<run_value<<endl;
    return run_value;
}

int perse_arg(int argc, char *argv[])
{
    cout<<"perse_arg : "<<argc<<endl;
    for(int i=0;i<argc;i++)
    {
        cout<<"arg: "<<string(argv[i])<<endl;
    }
    return argc;
}

int main(int argc, char *argv[])
{
#if 1
    cout<<"== begin =="<<endl;
    test_1();
    cout<<"== end =="<<endl;
    return 0;
#endif

    perse_arg(argc,argv);

    int run_value = run_main_app(argc,argv);

    return exit_main_app(run_value);
}