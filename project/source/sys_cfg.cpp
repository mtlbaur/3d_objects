#include "sys_cfg.h"

namespace D3::Sys {
    void CFG::reset() { *this = CFG(); }

    void CFG::save(const std::string& path, const std::string& name, const std::string& extension) {
        try {
            if (name.empty()) return;
            if (!boost::filesystem::exists(path)) boost::filesystem::create_directories(path);

            std::string   fullPath = path + name + extension;
            std::ofstream ofs(fullPath, std::ofstream::out);

            if (ofs.fail()) return;

            boost::archive::text_oarchive oa(ofs);

            oa << *this;

            ofs.close();
        } catch (std::exception& e) {
            std::cerr << "EXCEPTION: CFG::save(): " << e.what() << '\n';
            reset();
        }
    }

    void CFG::load(const std::string& path, const std::string& name, const std::string& extension) {
        try {
            if (name.empty()) return;

            std::string   fullPath = path + name + extension;
            std::ifstream ifs(fullPath, std::ifstream::in);

            if (ifs.fail()) return;

            boost::archive::text_iarchive ia(ifs);

            ia >> *this;

            ifs.close();
        } catch (std::exception& e) {
            std::cerr << "EXCEPTION: CFG::load(): " << e.what() << '\n';
            reset();
        }
    }
} // namespace D3::Sys