#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <map>
#include <ctime>

using namespace std;
namespace fs = std::filesystem;

void Copyright() {
    system("cls");
    std::cout << "& 2025 JSLY. 保留所有权利" << std::endl<<std::endl;
}






class language {
private:

public:
    std::map<std::string, std::string> Lan_data;
    void read(std::ifstream& Lan_in) {

        std::string Lan_in_string;
        int Lan_in_line = 0;
        if (!Lan_in.is_open()) {
            Copyright();
            throw std::runtime_error("语言文件打开失败");
        }
        while (std::getline(Lan_in, Lan_in_string)) {
            Lan_data["Line_" + std::to_string(Lan_in_line++)] = Lan_in_string;
        }
    }
};
class save {
private:
public:
    std::vector<std::string> save_name_list;

    void read() {
        save_name_list.clear();

        if (!fs::exists("save") || !fs::is_directory("save")) {
            return; // 没有save目录，直接返回空列表
        }

        for (const auto& entry : fs::directory_iterator("save\\")) {
            if (entry.is_directory()) {
                // 获取文件夹内的第一个文件
                std::string firstFileName = get_first_file_in_directory(entry.path().string());
                if (!firstFileName.empty()) {
                    save_name_list.push_back(firstFileName);
                }
            }
        }
    }

private:
    std::string get_first_file_in_directory(const std::string& directoryPath) {
        for (const auto& fileEntry : fs::directory_iterator(directoryPath)) {
            if (fileEntry.is_regular_file()) {
                // 返回文件名（不含路径和扩展名）
                std::string filename = fileEntry.path().filename().string();
                // 移除扩展名
                size_t dotPos = filename.find_last_of('.');
                if (dotPos != std::string::npos) {
                    filename = filename.substr(0, dotPos);
                }
                return filename;
            }
        }
        return ""; // 文件夹为空
    }

public:
    void list() {
        if (save_name_list.empty()) {
            std::cout << "没有找到存档" << std::endl;
            return;
        }

        std::cout << "可用的存档：" << std::endl << std::endl;
        for (int i = 0; i < save_name_list.size(); i++) {
            std::cout << i + 1 << ". " << save_name_list[i] << std::endl << std::endl;
        }
    }

    void find_save_directory() {
        if (!fs::exists("save")) {
            if (!fs::create_directory("save")) {
                throw std::runtime_error("创建save文件夹失败");
            }
        }
    }

    void create_save_directory(std::string folderName) {
        if (!fs::create_directory(folderName)) {
            throw std::runtime_error("创建公司存档文件夹失败: " + folderName);
        }
    }

    void create_save_file(std::string folderName, int save_back, std::string name) {
        std::ofstream Save_out(folderName + "\\" + name + ".sav");
        if (!Save_out.is_open()) {
            throw std::runtime_error("创建存档文件失败");
        }
        Save_out << save_back << std::endl;
        Save_out.close();
    }

    bool is_save_empty() {
        return !fs::exists("save") ||
            !fs::is_directory("save") ||
            fs::is_empty("save");
    }
};

void Self_Check() {
    // 检查文件夹
    if (!fs::exists("ConfigurationFile")) {
        throw std::runtime_error("自检失败: 配置文件夹不存在");
    }
    if (!fs::is_directory("ConfigurationFile")) {
        throw std::runtime_error("自检失败: ConfigurationFile 不是一个文件夹");
    }
    if (!fs::exists("Language")) {
        throw std::runtime_error("自检失败: 语言文件夹不存在");
    }
    if (!fs::is_directory("Language")) {
        throw std::runtime_error("自检失败: Language 不是一个文件夹");
    }

    // 检查文件夹内的必要文件
    if (!fs::exists("ConfigurationFile/ConFig_data")) {
        throw std::runtime_error("自检失败: 配置文件 ConFig_data 不存在");
    }
    if (!fs::exists("Language/Lan.txt")) {
        throw std::runtime_error("自检失败: 语言文件 Lan.txt 不存在");
    }

    std::cout << "自检通过: 必要文件和文件夹都存在" << std::endl;
    Sleep(1000);
    Copyright();
}
/*
void save_find_list() {
    for (const auto& entry : fs::directory_iterator("save\\")) {
        std::cout << entry.path().filename() << std::endl;
    }
}
*/

int name_back(std::string name) {
    long long back = 1;
    for (int i = 0; i < name.size(); i++) {
        back *= name[i];
    }
    return back + time(nullptr);
}

std::string name;

int main() {

    try {
        Self_Check();

        std::ifstream Lan_in("Language/Lan.txt");
        std::ifstream ConFig_in("ConfigurationFile/ConFig_data");

        if (!Lan_in.is_open()) {
            throw std::runtime_error("无法打开语言文件 Lan.txt");
        }
        if (!ConFig_in.is_open()) {
            throw std::runtime_error("无法打开配置文件 ConFig_data");
        }

        language lan;
        lan.read(Lan_in);
        save sav;

        std::cout << lan.Lan_data["Line_0"] << std::endl << std::endl;
        std::cout << lan.Lan_data["Line_1"] << std::endl << std::endl;

        char choice = _getch();
        Copyright();

        switch (choice) {
        case 27: {
            std::cout << lan.Lan_data["Line_2"] << std::endl << std::endl;
            break;
        }
        case 13: {
            std::cout << lan.Lan_data["Line_3"] << std::endl << std::endl;
            std::cout << lan.Lan_data["Line_4"] << std::endl << std::endl;
            choice = _getch();
            switch (choice) {
                case 'N': case 'n': {
                    Copyright();
                    std::cout << lan.Lan_data["Line_5"] << std::endl;

                    sav.find_save_directory();

                    Sleep(1000);
                    Copyright();

                    std::cout << lan.Lan_data["Line_6"] << std::endl << std::endl;

                    std::getline(std::cin, name);

                    name.erase(0, name.find_first_not_of(" \t\n\r\f\v"));
                    name.erase(name.find_last_not_of(" \t\n\r\f\v") + 1);

                    if (name.empty()) {
                        //std::cout << "公司名不能为空!" << std::endl;
                        throw std::exception("公司名不能为空!");
                    }

                    int save_back = name_back(name);
                    string folderName = "save\\" + name + "_" + std::to_string(save_back);

                    sav.create_save_directory(folderName);

                    sav.create_save_file(folderName, save_back,name);

                    std::cout << lan.Lan_data["Line_7"] << folderName << std::endl;
                    break;
                }
                case 'C': case 'c': {
                    sav.read();  // 读取存档列表（现在读取的是内层第一个文件名）

                    if (sav.save_name_list.empty()) {
                        throw std::exception("没有找到存档，请先创建新存档");
                    }
                    Copyright();
                    // 显示存档列表
                    std::cout << "选择存档：" << std::endl;
                    sav.list();

                    // 用户选择存档
                    std::cout << "请输入存档编号: ";
                    int choice;
                    std::cin >> choice;

                    if (choice > 0 && choice <= sav.save_name_list.size()) {
                        std::string selectedSave = sav.save_name_list[choice - 1];
                        std::cout << "已选择存档: " << selectedSave << std::endl;
                        // 这里可以添加加载存档的逻辑
                    }
                    else {
                        throw std::exception("无效的存档编号");
                    }

                    _getch();
                    break;
                }
            }
            break;
        }
        case 'S':case 's':{
            Copyright();
            std::cout << "" << std::endl << std::endl;
            break;
        }
        }
    }
    catch (const std::runtime_error& e) {
        Copyright();
        std::cerr << e.what() << std::endl << std::endl;
        std::cerr << "程序启动失败，请检查必要文件夹是否存在" << std::endl << std::endl;
        std::cerr << "请使用数据修复程序" << std::endl << std::endl;
        std::cout << "按任意键退出..." << std::endl;
        std::cin.get();
        return 1;
    }
    catch (const std::exception& e) {
        Copyright();
        std::cerr << "未知错误: " << e.what() << std::endl << std::endl;
        std::cout << "按任意键退出..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}