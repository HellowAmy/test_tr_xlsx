#include <QApplication>
#include <QWidget>

#include <iostream>

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
#include "Ttinyxml_ts.h"

using namespace QXlsx;
using namespace std;
using namespace tinyxml2;

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



void test_xlsx()
{
    Txlsx xlsx;
    QString path = "./build/Test.xlsx";
    int row = 1; int col = 1;
    QXlsx::Document xlsxW;
    QVariant writeValue = QString("Hello Qt!");
    xlsxW.write(row, col, writeValue);
    xlsxW.saveAs(path); 

    Document xlsxR(path); 
    if (xlsxR.load()) 
    { 
        Cell* cell = xlsxR.cellAt(row, col);
        if ( cell != NULL )
        {
            QVariant var = cell->readValue(); 
            vlogd($Q(var.toString()));
        }
    }
}


void test_tiny_ts()
{
    QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.ts";
    QString s2 = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window2.ts";
    QString s3 = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.xlsx";
    Ttinyxml_ts txl;
    bool ok = txl.open_ts(s);
    if(ok)
    {
        auto p = txl.get_xml_data();
        show_xml_ts(&p);
    }

    bool ok2 = txl.write_ts(s2);
    if(ok2)
    {
        vlogd($("write succeed"));
    }

    bool ok3 = txl.write_xlsx(s3);
    vlogd($(ok3));

}

void test_xlsx_to_write()
{
    Ttinyxml_ts txl;
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/windowt.ts";
        bool ok = txl.open_ts(s);
        vlogd($(ok));
        if(ok)
        {
            auto p = txl.get_xml_data();
            show_xml_ts(&p);
        }
    }
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_xlsx.xlsx";
        {
            bool ok = txl.write_xlsx(s);
            vlogd($(ok));
        }
    }
    // return ;
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_xlsx.xlsx";
        {
            bool ok = txl.open_xlsx(s);
            vlogd($(ok));
            auto p = txl.get_xml_data();
            show_xml_ts(&p);
        }  
    }
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_xlsx_ts.ts";
        {
            bool ok = txl.write_ts(s);
            vlogd($(ok));
        }
    }
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_xlsx_xlsx.xlsx";
        {
            bool ok = txl.write_xlsx(s);
            vlogd($(ok));
        }
    }
}

void test_xml_to_write()
{
    Ttinyxml_ts txl;
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.ts";
        bool ok = txl.open_ts(s);
        vlogd($(ok));
        if(ok)
        {
            auto p = txl.get_xml_data();
            show_xml_ts(&p);
        }
    }
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_ts.ts";
        {
            bool ok = txl.write_ts(s);
            vlogd($(ok));
        }
    }
    {
        QString s = "/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window_ts_xlsx.xlsx";
        {
            bool ok = txl.write_xlsx(s);
            vlogd($(ok));
        }
    }
}

void test_tiny()
{
    Ttinyxml_ts ww;
    ct_xml_ts ts_xml;
    Ttinyxml *xml = new Ttinyxml;
    bool ok = xml->open_xml("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.ts");
    if(ok)
    {
        str version = Ttinyxml::to_str(xml->get_root_ele()->Attribute("version"));
        str language = Ttinyxml::to_str(xml->get_root_ele()->Attribute("language"));

        ts_xml.ts_version = version;
        ts_xml.ts_language = language;

        xml->for_ele(xml->get_root_ele(),"context",[&](XMLElement *ele_sub){
            ct_xml_ts::ct_context ts_context;

            str name = xml->get_ele_text(ele_sub,"name");
            vlogd($(name));

            ts_context.name = name;

            xml->for_ele(ele_sub,"message",[&](XMLElement *ele_sub){
                ct_xml_ts::ct_context::ct_message ts_message;

                str source = xml->get_ele_text(ele_sub,"source");
                str comment = xml->get_ele_text(ele_sub,"comment");
                str translation = xml->get_ele_text(ele_sub,"translation");

                str location_filename = xml->get_ele_attr(ele_sub,"location","filename");
                str location_line = xml->get_ele_attr(ele_sub,"location","line");
                str translation_type = xml->get_ele_attr(ele_sub,"translation","type");
                vlogd($(source)$(comment)$(location_filename)$(location_line)$(translation_type)$(translation));

                ts_message.source = source;
                ts_message.comment = comment;
                ts_message.location_filename = location_filename;
                ts_message.location_line = location_line;
                ts_message.translation_type = translation_type;
                ts_message.translation = translation;

                ts_context.message.push_back(ts_message);
            });

            ts_xml.context.push_back(ts_context);
        });
    }

    vlogd($(ok));

    show_xml_ts(&ts_xml);



    delete xml;
}


void test_xml()
{
    XMLDocument doc;
    XMLError ret = doc.LoadFile("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/window.ts");
    vlogd($(ret));
    if(ret == XMLError::XML_SUCCESS)
    {
        XMLElement *root = doc.RootElement();
        if(root)
        {
            // int icc = root->ChildElementCount();
            // vlogd($(icc));
            XMLElement *econtext = root->FirstChildElement("context");
            int icc2 = econtext->ChildElementCount();
            vlogd($("cc: ")$(icc2));
            while(econtext)
            {
                XMLElement *emessage = econtext->FirstChildElement("message");
                int icc2 = emessage->ChildElementCount();
                vlogd($("cc11: ")$(icc2));
                XMLElement *ename = econtext->FirstChildElement("name");
                while(ename)
                {
                    auto sename = ename->GetText();
                    if(sename != nullptr) vlogd($(sename));
                    ename = ename->NextSiblingElement();
                }
                
                while(emessage)
                {
                    {
                        XMLElement *source = emessage->FirstChildElement("source");
                        if(source)
                        {
                            auto s = source->GetText();
                            if(s != nullptr) vlogd($(s));
                            auto filename = source->Attribute("location","filename");
                            if(filename != nullptr) vlogd($(filename));

                        }
                    }
                    {
                        XMLElement *source = emessage->FirstChildElement("comment");
                        if(source)
                        {
                            auto s = source->GetText();
                            if(s != nullptr) vlogd($(s));
                        }
                    }
                    {
                        XMLElement *source = emessage->FirstChildElement("location");
                        if(source)
                        {
                            auto s = source->Attribute("filename");
                            if(s != nullptr) vlogd($(s));
                            {
                                auto s = source->Attribute("line");
                                vlogd($(s));
                            }
                        }
                    }
                    {
                        XMLElement *source = emessage->FirstChildElement("translation");
                        if(source)
                        {
                            auto s = source->Attribute("type");
                            if(s != nullptr) vlogd($(s));
                        }
                    }

                    emessage = emessage->NextSiblingElement();
                }
                econtext = econtext->NextSiblingElement();
            }

            
            auto s = root->GetText();
            if(s == nullptr)
            {
                vlogd($("========="));
            }
        }
    }
}


int run_main_app(int argc, char *argv[])
{
    QApplication a(argc,argv);

    QTranslator *trp = new QTranslator(qApp);
    bool ok = trp->load("/home/cong/open/test_qt/test_tr_xlsx/config/language/cn/cn.qm");
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
    cout<<"== begin =="<<endl;

    // test_xlsx();
    // test_xml();
    // test_tiny();
    // test_tiny_ts();
    // test_xlsx_to_ts();
    // test_xlsx_to_write();
    // test_xlsx();
    test_ts_read_write();


    cout<<"== end =="<<endl;
    return 0;


    perse_arg(argc,argv);

    int run_value = run_main_app(argc,argv);

    return exit_main_app(run_value);
}