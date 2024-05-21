
#ifndef TTINYXML_H
#define TTINYXML_H

#include <iostream>
#include <list>
#include <functional>


#include "Tconfig.h"
#include "tinyxml2.h"


using namespace tinyxml2;
using namespace Tconf;

class Ttinyxml
{
public:
    Ttinyxml() 
    {
        _doc = new XMLDocument;
    }
    ~Ttinyxml() 
    {
        _doc->Clear();
        delete _doc;
    }

    bool open_xml(cstr file)
    {
        XMLError ret = _doc->LoadFile(file.c_str());
        bool success = (ret == XMLError::XML_SUCCESS);
        if(success) 
        {
            _root = _doc->RootElement();
            if(_root == nullptr) success = false;
        }
        return success;
    }

    static str to_str(const char *s)
    {
        if(s == nullptr) return "";
        return s;
    }

    static str get_ele_text(XMLElement *ele,cstr name)
    {
        if(ele != nullptr)
        {
            XMLElement *en = ele->FirstChildElement(name.c_str());
            if(en != nullptr)
            {
                return to_str(en->GetText());
            }
        }
        return "";
    }

    static str get_ele_attr(XMLElement *ele,cstr name,cstr index)
    {
        if(ele != nullptr)
        {
            XMLElement *en = ele->FirstChildElement(name.c_str());
            if(en != nullptr)
            {
                return to_str(en->Attribute(index.c_str()));
            }
        }
        return "";
    }

    static void for_ele(XMLElement *ele,cstr name,std::function<void(XMLElement *)> fn_ele_cb)
    {
        if(ele == nullptr) return;

        XMLElement *en = ele->FirstChildElement(name.c_str());
        while(en)
        {
            if(fn_ele_cb)
            {
                fn_ele_cb(en);
            }
            en = en->NextSiblingElement();
        }
    }

    XMLElement* get_root_ele()
    {
        return _root;
    }

    XMLDocument* get_doc()
    {
        return _doc;
    }

protected:
    XMLDocument *_doc = nullptr;
    XMLElement *_root = nullptr;
};

#endif // TTINYXML_H
