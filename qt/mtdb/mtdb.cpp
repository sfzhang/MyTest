#include <QApplication>
#include <log/log.h>
#include "mainwindow.h"

using namespace std;
using namespace hifu;
using namespace hifu::log;

int main(int argc, char *argv[])
{
    /* Application name */
    std::string app_name = basename(argv[0]);

    /* Get log config file */
    if (!getenv(ENV_HIFU_ROOT)) {
        ETRACE("environment[%s] not set", ENV_HIFU_ROOT);
        return -1;
    }
    std::string logfile = std::string(getenv(ENV_HIFU_ROOT)) + "/log/" + app_name + ".log";

    std::string loglevel("DEBUG");
    if (getenv(ENV_HIFU_LOG_LEVEL)) {
        loglevel = getenv(ENV_HIFU_LOG_LEVEL);
    }

    /* Initialize log4cplus */
    if (!log::initialize(app_name, std::string())) {
        ETRACE("log::initialize() failed");
        return -1;
    }

    if (!log::setupLogger(app_name, loglevel, logfile)) {
        ETRACE("setupLogger() failed: app_name[%s], logfile[%s]", app_name.c_str(), logfile.c_str());
        return -1;
    }
    DLOG("%s started...", app_name.c_str());

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
} 
