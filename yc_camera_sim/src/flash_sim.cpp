#include <cstring>
#include <flash_sim.h>
#include <fstream>
#include <iostream>

static const std::string flash_sim_path = "./flash_sim.bin";

void createFlashSimFile() {
    // 创建一个二进制文件 flash_sim.bin 保存flash仿真的读写
    std::ofstream ofs(flash_sim_path.c_str(), std::ios::binary);
    if (!ofs) {
        std::cerr << "创建flash_sim.bin文件失败" << std::endl;
    }
    ofs.seekp(static_cast<std::streamoff>(0), std::ios::beg);
    if (!ofs) {
        std::cerr << "创建时seekp失败" << std::endl;
    }

    char data[4096];
    memset(data, 0, 4096);
    ofs.write(data, 4096);
    ofs.flush();
    ofs.close();
    std::cout << "文件flash_sim.bin创建成功" << std::endl;
}

void flashRead(int offset, char *data, int len) {
    // 打开flash_sim.bin文件
    std::ifstream ifs(flash_sim_path.c_str(), std::ios::binary);

    if (!ifs) {
        std::cerr << "读取时打开文件错误, 开始创建文件" << std::endl;
        ifs.close();
        createFlashSimFile();
        ifs.open(flash_sim_path.c_str(), std::ios::binary);
    }

    ifs.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
    if (!ifs) {
        std::cerr << "读取时seekg失败" << std::endl;
    }

    ifs.read(reinterpret_cast<char *>(data), len);
    ifs.close();
}

void flashWrite(int offset, char *data, int len) {
    // 写入flash_sim.bin文件
    std::ofstream ofs(flash_sim_path.c_str(), std::ios::binary);
    if (!ofs) {
        std::cerr << "写入时文件不存在, 开始创建文件" << std::endl;
        ofs.close();
        createFlashSimFile();
        ofs.open(flash_sim_path.c_str(), std::ios::binary);
    }

    ofs.seekp(static_cast<std::streamoff>(offset), std::ios::beg);
    if (!ofs) {
        std::cerr << "写入时seekp失败" << std::endl;
    }
    ofs.write(reinterpret_cast<char *>(data), len);
    ofs.close();
}
