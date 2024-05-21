
#ifndef TTINYXML_TS_H
#define TTINYXML_TS_H

#include <iostream>

#include <QFile>

#include "Tconfig.h"
#include "Ttinyxml.h"
#include "Txlsx.h"
#include "Tvlog.h"

#define PRINT_FAILED(ok) if(ok == false) { vlogd($(ok)); }

class Ttinyxml_ts : public Ttinyxml
{
public:
    Ttinyxml_ts() 
    {
    }
    ~Ttinyxml_ts() {}

    bool open_ts(QString filename)
    {
        return load_data_ts(Tconf::qstos(filename));
    }

    bool write_ts(QString filename)
    {
        XMLDeclaration* decl = _doc->NewDeclaration();
        _doc->InsertFirstChild(decl);

        XMLUnknown* nuk = _doc->NewUnknown("DOCTYPE TS");
        _doc->InsertEndChild(nuk);

        XMLElement* ts = _doc->NewElement("TS");
        ts->SetAttribute("version",_ts_data.ts_version.c_str());
        ts->SetAttribute("language",_ts_data.ts_language.c_str());
        _doc->InsertEndChild(ts);

        for(auto it = _ts_data.context.begin();it!=_ts_data.context.end();it++)
        {
            XMLElement* context = _doc->NewElement("context");
            XMLElement* name = _doc->NewElement("name");
            context->InsertFirstChild(name);

            for(auto itm = it->message.begin();itm!=it->message.end();itm++)
            {
                XMLElement* message = _doc->NewElement("message");
                XMLElement* location = _doc->NewElement("location");
                XMLElement* source = _doc->NewElement("source");
                XMLElement* comment = _doc->NewElement("comment");
                XMLElement* translation = _doc->NewElement("translation");

                location->SetAttribute("filename",itm->location_filename.c_str());
                location->SetAttribute("line",itm->location_line.c_str());
                source->SetText(itm->source.c_str());
                comment->SetText(itm->comment.c_str());
                translation->SetText(itm->translation.c_str());
                translation->SetAttribute("type",itm->translation_type.c_str());

                message->InsertEndChild(location);
                message->InsertEndChild(source);
                message->InsertEndChild(comment);
                message->InsertEndChild(translation);
                context->InsertEndChild(message);
            }
            ts->InsertEndChild(context);
        }
        return _doc->SaveFile(Tconf::qstos(filename).c_str()) == XML_SUCCESS;
    }

    bool open_xlsx(QString filename)
    {
        bool ok = _xlex.open_xlsx(filename);
        PRINT_FAILED(ok)
        if(ok == false) return false;

        int line_row = 2;
        std::vector<QString> vec_title;
        {
            bool ok = _xlex.read_row(vec_title,line_row++);
            PRINT_FAILED(ok)
        }
        _ts_data.ts_version = qstos(vec_title[0]);
        _ts_data.ts_language = qstos(vec_title[1]);

        while (true)
        {
            ct_xml_ts::ct_context context;
            std::vector<QString> vec_context;

            bool ok = _xlex.read_row(vec_context,line_row++);
            if(ok == false)
            {
                if(context.message.size() > 0)
                {
                    _ts_data.context.push_back(context);
                }
                break;
            }

            if(vec_context[0] == "context")
            {
                context.name = qstos(vec_context[2]);

                while (true)
                {
                    std::vector<QString> vec_message;
                    bool ok = _xlex.read_row(vec_message,line_row++);
                    if(ok == false) 
                    {
                        line_row--;
                        break;
                    }

                    if(vec_message[0] == "message")
                    {
                        ct_xml_ts::ct_context::ct_message message;
                        message.source = qstos(vec_message[1]);
                        message.translation = qstos(vec_message[2]);
                        message.comment = qstos(vec_message[3]);
                        message.translation_type = qstos(vec_message[4]);
                        message.location_filename = qstos(vec_message[5]);
                        message.location_line = qstos(vec_message[6]);
                        context.message.push_back(message);
                    }
                }
                _ts_data.context.push_back(context);
            }
        }

        return true;
    }

    bool write_xlsx(QString filename)
    {
        bool ok = _xlex.open_xlsx();
        PRINT_FAILED(ok)
        if(ok == false) return false;

        std::vector<QString> vec_title {
            "xml root",
            "source",
            "translation",
            "comment",
            "translation type",
            "location filename",
            "location line"
        };
        int line_row = 1;
        {
            bool ok = _xlex.write_row(vec_title,line_row++);
            PRINT_FAILED(ok)
        }

        std::vector<QString> vec_version;
        vec_version.push_back(stoqs(_ts_data.ts_version));
        vec_version.push_back(stoqs(_ts_data.ts_language));
        {
            bool ok = _xlex.write_row(vec_version,line_row++);
            PRINT_FAILED(ok)
        }

        for(auto it = _ts_data.context.begin();it!=_ts_data.context.end();it++)
        {
            std::vector<QString> vec_context;
            vec_context.push_back("context");
            vec_context.push_back("name");
            vec_context.push_back(stoqs(it->name));
            bool ok = _xlex.write_row(vec_context,line_row++);
            PRINT_FAILED(ok)

            for(auto itm = it->message.begin();itm!=it->message.end();itm++)
            {
                std::vector<QString> vec_message;
                vec_message.push_back("message");
                vec_message.push_back(stoqs(itm->source));
                vec_message.push_back(stoqs(itm->translation));
                vec_message.push_back(stoqs(itm->comment));
                vec_message.push_back(stoqs(itm->translation_type));
                vec_message.push_back(stoqs(itm->location_filename));
                vec_message.push_back(stoqs(itm->location_line));
                bool ok = _xlex.write_row(vec_message,line_row++);
                PRINT_FAILED(ok)
            }
        }

        return _xlex.get_xlsx()->saveAs(filename);
    }

    ct_xml_ts& get_xml_data()
    {
        return _ts_data;
    }

    bool ts_to_xlsx(QString file_ts,QString file_xlsx)
    {
        return false;
    }

    bool xlsx_to_ts(QString file_xlsx,QString file_ts)
    {
        return false;
    }

protected:
    bool load_data_ts(cstr filename)
    {
        bool ok = this->open_xml(filename);
        if(ok)
        {
            str version = Ttinyxml::to_str(this->get_root_ele()->Attribute("version"));
            str language = Ttinyxml::to_str(this->get_root_ele()->Attribute("language"));
            _ts_data.ts_version = version;
            _ts_data.ts_language = language;

            this->for_ele(this->get_root_ele(),"context",[&](XMLElement *ele_sub){
                ct_xml_ts::ct_context ts_context;
                str name = this->get_ele_text(ele_sub,"name");
                ts_context.name = name;

                this->for_ele(ele_sub,"message",[&](XMLElement *ele_sub){
                    ct_xml_ts::ct_context::ct_message ts_message;

                    str source = this->get_ele_text(ele_sub,"source");
                    str comment = this->get_ele_text(ele_sub,"comment");
                    str translation = this->get_ele_text(ele_sub,"translation");
                    str location_filename = this->get_ele_attr(ele_sub,"location","filename");
                    str location_line = this->get_ele_attr(ele_sub,"location","line");
                    str translation_type = this->get_ele_attr(ele_sub,"translation","type");
                    ts_message.source = source;
                    ts_message.comment = comment;
                    ts_message.location_filename = location_filename;
                    ts_message.location_line = location_line;
                    ts_message.translation_type = translation_type;
                    ts_message.translation = translation;
                    ts_context.message.push_back(ts_message);
                });
                _ts_data.context.push_back(ts_context);
            });
        }
        return ok;
    }

protected:
    ct_xml_ts _ts_data;

    Txlsx _xlex;
};
#endif // TTINYXML_TS_H
