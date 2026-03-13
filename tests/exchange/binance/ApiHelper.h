#include <QDir>
#include <QFile>

class ApiHelper{
public:
    ApiHelper() = default;
    ~ApiHelper() = default;

    static std::pair<QString, QString> getApiKeys()
    {
        QFile file("apiKeys/binanceAPI.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return {"", ""};
        }

        QTextStream in(&file);
        QString apiKey = in.readLine().trimmed();
        QString apiSecret = in.readLine().trimmed();
        file.close();
        return {apiKey, apiSecret};
    }
};
