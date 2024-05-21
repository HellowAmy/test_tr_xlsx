
#ifndef TCONFIG_H
#define TCONFIG_H

#include <iostream>
#include <string>

#include <QString>

#include "Tvlog.h"

namespace Tconf {

typedef const std::string & cstr;
typedef std::string str;

static std::string qstos(const QString &qstr)
{
    return qstr.toStdString();
}

static QString stoqs(cstr s)
{
    return QString::fromStdString(s);
}

} // conf



#endif // TCONFIG_H
