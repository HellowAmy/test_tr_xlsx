
#ifndef TXML_TR_H
#define TXML_TR_H

#include <iostream>
#include <list>

#include "Txlsx.h"
#include "Tconfig.h"
#include "Ttinyxml.h"

using namespace Tconf;

struct ct_xml_ts
{
    struct ct_context
    {
        struct ct_message
        {
            str location_filename;
            str location_line;
            str source;
            str comment;
            str translation;
            str translation_type;
        };
        
        str name;
        std::list<ct_message> message;
    };

    str ts_version;
    str ts_language;
    std::list<ct_context> context;
};

class Txml_tr
{
public:
    Txml_tr() {}
    ~Txml_tr() {}

    bool open_xlsx(QString filename)
    {
        return read_xlsx(filename,_ts_data);
    }

    bool open_ts(QString filename)
    {
        return read_ts(filename,_ts_data);
    }

    bool save_xlsx(QString filename)
    {
        return write_xlsx(filename,_ts_data);
    }

    bool save_ts(QString filename)
    {
        return write_ts(filename,_ts_data);
    }

    static bool read_xlsx(QString filename,ct_xml_ts &xml_data)
    {
        Txlsx xlex;
        bool ok = xlex.open_xlsx(filename);
        if(ok == false) return false;

        int line_row = 2;
        std::vector<QString> vec_title;
        {
            bool ok = xlex.read_row(vec_title,line_row++);
            if(ok == false) return false;
        }
        xml_data.ts_version = qstos(vec_title[0]);
        xml_data.ts_language = qstos(vec_title[1]);

        while (true)
        {
            ct_xml_ts::ct_context context;
            std::vector<QString> vec_context;

            bool ok = xlex.read_row(vec_context,line_row++);
            if(ok == false)
            {
                if(context.message.size() > 0)
                {
                    xml_data.context.push_back(context);
                }
                break;
            }

            if(vec_context[0] == "context")
            {
                context.name = qstos(vec_context[2]);

                while (true)
                {
                    std::vector<QString> vec_message;
                    bool ok = xlex.read_row(vec_message,line_row++);
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
                    else
                    {
                        line_row--;
                        break;
                    }
                }
                xml_data.context.push_back(context);
            }
        }
        return true;
    }

    static bool read_ts(QString filename,ct_xml_ts &xml_data)
    {
        Ttinyxml xml;
        bool ok = xml.open_xml(qstos(filename));
        if(ok)
        {
            str version = Ttinyxml::to_str(xml.get_root_ele()->Attribute("version"));
            str language = Ttinyxml::to_str(xml.get_root_ele()->Attribute("language"));
            xml_data.ts_version = version;
            xml_data.ts_language = language;

            xml.for_ele(xml.get_root_ele(),"context",[&](XMLElement *ele_sub){
                ct_xml_ts::ct_context ts_context;
                str name = xml.get_ele_text(ele_sub,"name");
                ts_context.name = name;

                xml.for_ele(ele_sub,"message",[&](XMLElement *ele_sub){
                    ct_xml_ts::ct_context::ct_message ts_message;

                    str source = xml.get_ele_text(ele_sub,"source");
                    str comment = xml.get_ele_text(ele_sub,"comment");
                    str translation = xml.get_ele_text(ele_sub,"translation");
                    str location_filename = xml.get_ele_attr(ele_sub,"location","filename");
                    str location_line = xml.get_ele_attr(ele_sub,"location","line");
                    str translation_type = xml.get_ele_attr(ele_sub,"translation","type");
                    ts_message.source = source;
                    ts_message.comment = comment;
                    ts_message.location_filename = location_filename;
                    ts_message.location_line = location_line;
                    ts_message.translation_type = translation_type;
                    ts_message.translation = translation;
                    ts_context.message.push_back(ts_message);
                });
                xml_data.context.push_back(ts_context);
            });
        }
        return ok;
    }

    static bool write_xlsx(QString filename,const ct_xml_ts &xml_data)
    {
        Txlsx xlex;
        bool ok = xlex.open_xlsx();
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
            bool ok = xlex.write_row(vec_title,line_row++);
            if(ok == false) return false;
        }

        std::vector<QString> vec_version;
        vec_version.push_back(stoqs(xml_data.ts_version));
        vec_version.push_back(stoqs(xml_data.ts_language));
        {
            bool ok = xlex.write_row(vec_version,line_row++);
            if(ok == false) return false;
        }

        for(auto it = xml_data.context.begin();it!=xml_data.context.end();it++)
        {
            std::vector<QString> vec_context;
            vec_context.push_back("context");
            vec_context.push_back("name");
            vec_context.push_back(stoqs(it->name));
            bool ok = xlex.write_row(vec_context,line_row++);
            if(ok == false) return false;
            

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
                bool ok = xlex.write_row(vec_message,line_row++);
                if(ok == false) return false;
            }
        }
        return xlex.get_xlsx()->saveAs(filename);
    }

    static bool write_ts(QString filename,const ct_xml_ts &xml_data)
    {
        Ttinyxml xml;
        XMLDocument *doc = xml.get_doc();
        XMLDeclaration* decl = doc->NewDeclaration();
        doc->InsertFirstChild(decl);

        XMLUnknown* nuk = doc->NewUnknown("DOCTYPE TS");
        doc->InsertEndChild(nuk);

        XMLElement* ts = doc->NewElement("TS");
        ts->SetAttribute("version",xml_data.ts_version.c_str());
        ts->SetAttribute("language",xml_data.ts_language.c_str());
        doc->InsertEndChild(ts);

        for(auto it = xml_data.context.begin();it!=xml_data.context.end();it++)
        {
            XMLElement* context = doc->NewElement("context");
            XMLElement* name = doc->NewElement("name");
            name->SetText(it->name.c_str());
            context->InsertFirstChild(name);

            for(auto itm = it->message.begin();itm!=it->message.end();itm++)
            {
                XMLElement* message = doc->NewElement("message");
                XMLElement* location = doc->NewElement("location");
                XMLElement* source = doc->NewElement("source");
                XMLElement* comment = doc->NewElement("comment");
                XMLElement* translation = doc->NewElement("translation");

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
        return doc->SaveFile(Tconf::qstos(filename).c_str()) == XML_SUCCESS;
    }

    ct_xml_ts& get_data()
    {
        return _ts_data;
    }

protected:
    ct_xml_ts _ts_data;

};
#endif // TXML_TR_H
