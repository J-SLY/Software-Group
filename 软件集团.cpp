#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <map>


extern std::ifstream Lan_in;
extern std::ifstream ConFig_in;



namespace fs = std::filesystem;

class language {
private:

public:
    std::map<std::string, std::string> Lan_data;
    void read(std::ifstream& Lan_in) {

        std::string Lan_in_string;
        int Lan_in_line = 0;
        if (!Lan_in.is_open()) {
            system("clear||cls");
            throw std::runtime_error("语言文件打开失败");
        }
        while (std::getline(Lan_in, Lan_in_string)) {
            Lan_data["Line_" + std::to_string(Lan_in_line++)] = Lan_in_string;
        }
    }
};


void Self_Check() {// 自检函数
        // 检查文件夹
        if (!fs::exists("ConfigurationFile")) {// 检查配置文件夹
            throw std::runtime_error("自检失败: 配置文件夹不存在");
        }
        if (!fs::is_directory("ConfigurationFile")) {// 检查是否为文件夹
            throw std::runtime_error("自检失败: ConfigurationFile 不是一个文件夹");
        }
        if (!fs::exists("Language")) {// 检查语言文件夹
            throw std::runtime_error("自检失败: 语言文件夹不存在");
        }
        if (!fs::is_directory("Language")) {// 检查是否为文件夹
            throw std::runtime_error("自检失败: Language 不是一个文件夹");
        }

        // 检查文件夹内的必要文件
        if (!fs::exists("ConfigurationFile/ConFig_data")) {// 检查配置文件
            throw std::runtime_error("自检失败: 配置文件 ConFig_data 不存在");
        }
        if (!fs::exists("Language/Lan.txt")) {// 检查语言文件
            throw std::runtime_error("自检失败: 语言文件 Lan.txt 不存在");
        }

        std::cout << "自检通过: 必要文件和文件夹都存在" << std::endl;
        Sleep(1000);
		system("clear||cls");
}
int main(){
	try {// 主程序入口
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
        
        std::cout << lan.Lan_data["Line_0"] << std::endl << std::endl;
		std::cout << lan.Lan_data["Line_1"] << std::endl << std::endl;
        
        char choice = _getch();  // 获取单个字符输入，不显示在屏幕上
        switch (choice) {
            case 27: {
                std::cout << "正在退出..." << std::endl << std::endl;
                break;
            };
            case 13: {
                
            }
            case 83: {
                system("clear||cls");
                std::cout << "" << std::endl << std::endl ;
            }
        }
        










	}
	catch (const std::runtime_error& e) {// 捕获自检失败的异常
        std::cerr << e.what() << std::endl <<std::endl;
        std::cerr << "程序启动失败，请检查必要文件夹是否存在" << std::endl << std::endl;
        std::cerr << "请使用数据修复程序" << std::endl << std::endl;
        std::cout << "按回车键退出..." << std::endl;
        std::cin.get();
        return 1;
	}
	catch (const std::exception& e) {// 捕获其他标准异常
        std::cerr << "未知错误: " << e.what() << std::endl << std::endl;
        std::cout << "按回车键退出..." << std::endl;
        std::cin.get();
        return 1;
    }
    return 0;
}
