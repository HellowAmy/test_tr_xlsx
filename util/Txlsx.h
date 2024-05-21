
#ifndef TXLEX_H
#define TXLEX_H

#include <iostream>
#include <vector>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include "Tconfig.h"

using namespace QXlsx;
using namespace Tconf;

class Txlsx
{
public:
    Txlsx() { }
    ~Txlsx() 
    {
        if(_xlsx != nullptr) delete _xlsx;
    }

    bool open_xlsx(QString filename = "")
    {
        if(_xlsx != nullptr) delete _xlsx;

        if(filename == "") 
        {
            _xlsx = new Document;
            return true;
        }
        else 
        {
            _xlsx = new Document(filename);
            return _xlsx->load();
        }
    }

    bool write_row(const std::vector<QString> &data,int row = 1,int col = 1)
    {
        for(const auto &a:data)
        {
            bool ok = _xlsx->write(row,col++,a);
            if(ok == false) return false;
        }
        return true;
    }

    bool read_row(std::vector<QString> &data,int row = 1,int col = 1)
    {
        while (true)
        {
            Cell* cell = _xlsx->cellAt(row, col++);
            if(cell == nullptr) break;
            data.push_back(cell->readValue().toString());
        }
        return data.size() > 0;
    }

    Document* get_xlsx()
    {
        return _xlsx;
    }

protected:
    Document *_xlsx = nullptr;

};
#endif // TXLEX_H
