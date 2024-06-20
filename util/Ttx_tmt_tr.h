
#ifndef TTX_TMT_TR_H
#define TTX_TMT_TR_H


#include <tencentcloud/core/TencentCloud.h>
#include <tencentcloud/core/profile/HttpProfile.h>
#include <tencentcloud/core/profile/ClientProfile.h>
#include <tencentcloud/core/Credential.h>
#include <tencentcloud/core/NetworkProxy.h>
#include <tencentcloud/core/AsyncCallerContext.h>
#include <tencentcloud/tmt/v20180321/model/TextTranslateRequest.h>
#include <tencentcloud/tmt/v20180321/TmtClient.h>

#include <iostream>

#include <QFile>

#include "Tvlog.h"

using namespace TencentCloud;
using namespace TencentCloud::Tmt;
using namespace TencentCloud::Tmt::V20180321;
using namespace TencentCloud::Tmt::V20180321::Model;

typedef Outcome<Core::Error, Model::TextTranslateBatchResponse> TextTranslateBatchOutcome;
typedef Outcome<Core::Error, Model::TextTranslateResponse> TextTranslateOutcome;


class Ttx_tmt_tr
{
public:
    Ttx_tmt_tr() {}

    ~Ttx_tmt_tr() 
    {
        if(_handle != nullptr) delete _handle;
    }

    bool init_handle(QString path_key)
    {
        std::string secretId;
        std::string secretKey;
        const std::string region = "ap-guangzhou";

        QFile file(path_key);
        if(file.open(QIODevice::ReadOnly))
        {
            QString str = file.readAll();
            QStringList ls = str.split("#",Qt::SkipEmptyParts);
            if(ls.size() >= 2)
            {
                secretId = ls[0].toStdString();
                secretKey = ls[1].toStdString();
                _handle = new TmtClient({secretId,secretKey},region);
            }
            file.close();
        }
        return _handle != nullptr;
    }

    std::vector<std::string> get_tmt_tr(std::vector<std::string> ls_tr,std::string source = "en",std::string target = "zh")
    {
        TextTranslateBatchRequest trct;
        trct.SetSourceTextList(ls_tr);
        trct.SetSource(source);
        trct.SetTarget(target);
        trct.SetProjectId(0);

        auto ret = _handle->TextTranslateBatch(trct);
        if(ret.IsSuccess()) return ret.GetResult().GetTargetTextList();
        else return {};
    }

protected:

private:
    TmtClient *_handle = nullptr;
};

static Ttx_tmt_tr *_sp_tmt_tr_ = Tsingle_d<Ttx_tmt_tr>::get();


#endif // TTX_TMT_TR_H
