#include <iostream>
#include <fstream>
#include <filesystem>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <map>


std::ifstream Lan_in("Language/Lan.txt");
std::ifstream ConFig_in("ConfigurationFile/ConFig_data");

namespace fs = std::filesystem;

std::string Language;

class language {
private:
    std::map<std::string, std::string> data;
public:
    void read() {

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
    
}
int main(){
	try {// 主程序入口
        Self_Check();
        ConFig_in >> Language;
		/*
        std::cout << "欢迎使用 软件集团 游戏" << std::endl << std::endl;
		std::cout << "按回车键开始游戏，按ESC键退出..." << std::endl;
        char choice = _getch();  // 获取单个字符输入，不显示在屏幕上

        if (choice == 27) {  // ESC键的ASCII码是27
            std::cout << "程序退出！\n";
        }
        else if (choice == 13) {  // 回车键的ASCII码是13
            std::cout << "继续执行...\n\n";

        }
        */
        std::cout << Language;
        char choice = _getch();












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
