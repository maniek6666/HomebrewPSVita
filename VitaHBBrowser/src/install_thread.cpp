#include "install_thread.h"

#include <activity.h>
#include <Views/ProgressView/progressView.h>
#include <network.h>
#include <vitaPackage.h>
#include <psp2/io/fcntl.h>
#include "zip.h"


int install_thread(SceSize args_size, InstallArguments *installArgs) {
    
    InfoProgress progressTotal;
	Homebrew targetHb = installArgs->hb;
    auto progressView = std::make_shared<ProgressView>(progressTotal, targetHb);

    InfoProgress progress;

    try {
        Activity::get_instance()->AddView(progressView);

        if (!installArgs->hb.data.empty()) {
            progress = progressTotal.Range(0, 50);

            progress.message("Downloading the data...");
            Network::get_instance()->Download(installArgs->hb.data, std::string("ux0:/temp/data.zip"), progress.Range(0, 50));

            Zipfile zip = Zipfile("ux0:/temp/data.zip");
            zip.Unzip("ux0:/data/", progress.Range(50, 100));

            progress = progressTotal.Range(50, 100);
        } else {
            progress = progressTotal;
        }

        progress.message("Downloading the vpk...");

        Network::get_instance()->Download(installArgs->hb.url, std::string("ux0:/temp/download.vpk"), progress.Range(0, 40));

        VitaPackage pkg = VitaPackage(std::string("ux0:/temp/download.vpk"));
        pkg.Install(progress.Range(40, 100));

        YAML::Emitter info;
        info << YAML::BeginMap;
        info << YAML::Key << "name";
        info << YAML::Value << installArgs->hb.name;
        info << YAML::Key << "version";
        info << YAML::Value << installArgs->hb.version;
        info << YAML::Key << "date";
        info << YAML::Value << installArgs->hb.date.str;
        info << YAML::EndMap;

      	int fd = sceIoOpen((std::string("ux0:app/") + installArgs->hb.titleid + "/vitadb_info.yml").c_str(), SCE_O_WRONLY|SCE_O_CREAT, 0777);
		sceIoWrite(fd, info.c_str(), strlen(info.c_str()));
		sceIoClose(fd);

        progress.percent(100);
        progress.message("Finished");
        progressView->Finish(2000);

    } catch (const std::exception &ex) {
        progress.message(ex.what());
        progressView->Finish(4000);
        log_printf(DBG_ERROR, "%s", ex.what());
    }

    sceKernelExitDeleteThread(0);
    return 0;
}
