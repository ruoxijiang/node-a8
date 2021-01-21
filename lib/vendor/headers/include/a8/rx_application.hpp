//
// Created by Dalio on 2020/2/14.
//

#ifndef A8_RX_APPLICATION_HPP
#define A8_RX_APPLICATION_HPP

#include <spdlog/spdlog.h>
#include "./model/dbhelper.hpp"

namespace a8 {

    enum Environment {
        EnvProd = 0,
        EnvStag
    };

    class RXApplication {

    public:
        static void Init(const std::string &workDirectory, Environment env = EnvProd);

        static std::shared_ptr<RXApplication> Instance();

        void Log(int level, const std::string &log);

        std::shared_ptr<spdlog::logger> Logger();

        void Event(const std::string &event, const std::string &params);

        std::shared_ptr<DBhelper> GetDBHelper();

        std::string GetWorkDirectory();

        RXApplication();

        bool IsGoogleDisabled();

        void DisableGoogle();

        std::string GetUserAgent();

        ~RXApplication();

        void SetEnvironment(Environment env);

        Environment GetEnvironment() const;

    private:
        bool InitLog();

    private:
        std::shared_ptr<DBhelper> dbHelper;
        std::shared_ptr<spdlog::logger> logger;
        std::string workDirectory;
        static std::shared_ptr<RXApplication> instance;
        time_t googleCodeTime = 0;
        Environment env = EnvProd;
    };
}


#endif //A8_RX_APPLICATION_HPP
